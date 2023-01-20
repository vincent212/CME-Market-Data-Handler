/*

THIS SOFTWARE IS OPEN SOURCE UNDER THE MIT LICENSE

Copyright 2022 Vincent Maciejewski, Quant Enterprises & M2 Tech
Contact:
v@m2te.ch
mayeski@gmail.com
https://www.linkedin.com/in/vmayeski/
http://m2te.ch/


Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

https://opensource.org/licenses/MIT

*/

#pragma once

#include "udp_socket.hpp"
#include <map>
#include <chrono>
#include "message_buffer.hpp"
#include "DataDecoder.hpp"
#include "RecoveryProcessor.hpp"
#include "CallBackIF.hpp"

namespace m2tech::mdp3
{

    /**
     * @brief Process messages from CME
     * 
     */
    struct MessageProcessor
    {

        RecoveryProcessor<MessageProcessor> *recovery_processor;
        DataDecoder decoder;
        std::map<uint32_t, message_buffer *> msg_q;
        in_port_t port_a, port_b;
        int sock_a, sock_b;
        struct sockaddr_in addr_a;
        struct sockaddr_in addr_b;
        size_t addrlen_a, addrlen_b;
        std::string group_a, group_b, interface;
        bool dorecovery = false;
        bool in_recovery = false;
        bool have_instruments = false;
        bool recoveryonstart = false;
        uint32_t qseq_num = 0;
        volatile bool shutdown = false;

        /**
         * @brief Read from channel A
         * 
         * @param seq_num 
         * @return message_buffer* 
         */
        [[nodiscard]]
        message_buffer *read_a(uint32_t &seq_num) const noexcept
        {
            auto m = new message_buffer();
            auto nrec = m2tech::mcast::receive(sock_a, &m->message[0], m2tech::mdp3::msgsz, addr_a, addrlen_a);
            if (nrec == 0)
            {
                delete m;
                return 0;
            }
            m->len = nrec;
            seq_num = *(unsigned int *)(&m->message[0]);
            m->seqnum = seq_num;
            return m;
        }

        /**
         * @brief Read from channel B
         * 
         * @param seq_num 
         * @return message_buffer* 
         */
        [[nodiscard]]
        message_buffer *read_b(uint32_t &seq_num) const noexcept
        {
            auto m = new message_buffer();
            auto nrec = m2tech::mcast::receive(sock_b, &m->message[0], m2tech::mdp3::msgsz, addr_b, addrlen_b);
            if (nrec == 0)
            {
                delete m;
                return 0;
            }
            m->len = nrec;
            seq_num = *(unsigned int *)(&m->message[0]);
            m->seqnum = seq_num;
            return m;
        }

        /**
         * @brief Construct a new Message Processor object
         * 
         * @param _cb application object that implements call back behavior
         * @param _port_a 
         * @param _port_b 
         * @param _groupa 
         * @param _groupb 
         * @param _interface interface handler is listening on
         * @param _dorecovery whether to do data recover on gaps
         * @param _recoveryonstart whether to trigger recover on join
         * @param _debug 
         */
        MessageProcessor(
            CallBackIF *_cb,
            in_port_t _port_a,
            in_port_t _port_b,
            const char *_groupa,
            const char *_groupb,
            const char *_interface,
            bool _dorecovery,
            bool _recoveryonstart,
            bool _debug)
            : decoder(_cb, _debug),
              port_a(_port_a),
              port_b(_port_b),
              group_a(_groupa),
              group_b(_groupb),
              interface(_interface),
              dorecovery(_dorecovery),
              recoveryonstart(_recoveryonstart)
        {
        }

        /**
         * @brief Set the recovery processor object
         * 
         * @param rec 
         */
        void set_recovery_processor(m2tech::mdp3::RecoveryProcessor<MessageProcessor> *rec)
        {
            recovery_processor = rec;
        }

        /**
         * @brief Join multicast A and B
         * 
         */
        void connect() noexcept
        {
            // port a and b are mc ports
            // group a and b are mc groups
            m2tech::mcast::create_udp_socket(port_a, sock_a, addr_a, addrlen_a);
            m2tech::mcast::create_udp_socket(port_b, sock_b, addr_b, addrlen_b);
            m2tech::mcast::join_group(sock_a, group_a.c_str(), interface.c_str());
            m2tech::mcast::join_group(sock_b, group_b.c_str(), interface.c_str());
            shutdown = false;
        }

        /**
         * @brief Thread
         * 
         */
        void operator()()
        {
            while (!shutdown)
                read_sockets();
        }

        /**
         * @brief Read multicast data from channels A and B
         * Messagges are added to message queue then a call to processq() is made
         * @see processq()
         */
        void read_sockets() noexcept
        {

            message_buffer *msg;
            uint32_t seq;
            bool have_msg = false;

            //
            // TODO: Reading A then B is not ideal but may be ok.
            // I took this approach for clarity.
            //

            //
            // TODO: message buffers should be memory pooled
            //

            while (true)
            {
                msg = read_a(seq);
                if (msg)
                {
                    auto p = msg_q.find(seq);
                    if (p == msg_q.end())
                    {
                        msg_q[seq] = msg;
                        have_msg = true;
                    }
                    else
                        delete msg;
                }
                else
                    break;
            }

            if (have_msg)
            {
                auto recv_ts = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                processq(recv_ts);
                have_msg = false;
            }

            while (true)
            {
                msg = read_b(seq);
                if (msg)
                {
                    auto p = msg_q.find(seq);
                    if (p == msg_q.end())
                    {
                        msg_q[seq] = msg;
                        have_msg = true;
                    }
                    else
                        delete msg;
                }
                else
                    break;
            }

            if (have_msg)
            {
                auto recv_ts = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                processq(recv_ts);
            }
        }

        /**
         * @brief Process binary message queue from channels A and B
         * 
         * @param ts receive time stamp
         */
        void processq(uint64_t ts) noexcept
        {

            if (in_recovery)
                return;

            auto p = msg_q.begin();
            if (p == msg_q.end())
                return;

            while (p != msg_q.end())
            {

                auto sn = p->first;
                auto msg = p->second;

                if (sn <= qseq_num)
                {
                    delete msg;
                    msg_q.erase(p);
                    p = msg_q.begin();
                }
                else if (
                    (sn == qseq_num + 1) ||
                    (!dorecovery && qseq_num != 0) ||
                    (!recoveryonstart && qseq_num == 0))
                {
                    if (sn != qseq_num + 1)
                    {
                        std::cout << "READ: *** GAP DETECTED but not recovering sn: " << sn << " expected " << qseq_num + 1 << std::endl;
                    }
                    // process message
                    decoder.mbo_data(&msg->message[0], msg->len, ts);
                    delete msg;
                    msg_q.erase(p);
                    p = msg_q.begin();
                    qseq_num = sn;
                }
                else
                {
                    // we have a gap
                    std::cout << "READ: RECOVERING FROM GAP sn: " << sn << " expected " << qseq_num + 1 << std::endl;
                    in_recovery = true;
                    decoder.clear();
                    if (!have_instruments)
                    {
                        recovery_processor->do_recovery(true);
                        have_instruments = true;
                    }
                    else
                        recovery_processor->do_recovery(false);
                    break;
                }
            }
        }

        /**
         * @brief Signal that recovery is complete.
         * @see RecoveryProcessor()
         * 
         * @param last_seq 
         */
        void datarecoveryend(uint32_t last_seq) noexcept
        {
            std::cout << "RECOVERY DONE\n";
            // TODO: make sure order book reconstruction code
            // ignores updates that have transaction time <=
            // last recovery update 
            qseq_num = last_seq;
            in_recovery = false;
        }

        /**
         * @brief Stop the thread
         * 
         */
        void
        end() noexcept
        {
            shutdown = true;
            close(sock_a);
            close(sock_b);
        }
    };

}
