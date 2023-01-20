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

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>
#include <strings.h>
#include <errno.h>
#include <stdlib.h>

namespace m2tech::mcast
{

   /**
    * @brief Create a multicast socket
    * Note the bind will fail in cases where more than one multicast group is joined
    * on the same port. Add appropritate setsock opt to fix this.
    * 
    * @param port multicast port
    * @param sock 
    * @param addr 
    * @param addrlen 
    */
   static void create_udp_socket(
       in_port_t port,
       int &sock,
       struct sockaddr_in &addr,
       size_t &addrlen)
   {
      sock = socket(AF_INET, SOCK_DGRAM, 0);
      if (sock < 0)
      {
         perror("socket");
         abort();
      }
      bzero((char *)&addr, sizeof(addr));
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
      addr.sin_port = htons(port);
      addrlen = sizeof(addr);

      if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
      {
         perror("bind");
         abort();
      }
   }

   /**
    * @brief join multicast group
    * 
    * @param sock 
    * @param group 
    * @param inf pass the interface where mcast packets are received
    */
   static void join_group(
       int sock,
       const char *group,
       const char *inf = 0)
   {

      struct ip_mreq mreq;
      mreq.imr_multiaddr.s_addr = inet_addr(group);
      if (inf)
         mreq.imr_interface.s_addr = inet_addr(inf);
      else
         mreq.imr_interface.s_addr = htonl(INADDR_ANY);
      if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                     &mreq, sizeof(mreq)) < 0)
      {
         perror("setsockopt IP_ADD_MEMBERSHIP");
         abort();
      }
   }

   /**
    * @brief Receive multicast message
    * note: datagrams are always received completely
    * @param sock 
    * @param message 
    * @param len 
    * @param addr 
    * @param addrlen 
    * @param block if true will block when no data is read
    * @return ssize_t number of bytes read
    */
   static ssize_t receive(
       int sock,
       const char *message,
       size_t len,
       const struct sockaddr_in &addr,
       socklen_t addrlen,
       bool block = false)
   {

      // todo: change this to fcntl no O_NONBLOCK ?

      int flags = 0;
      if (!block)
      {
         flags = MSG_DONTWAIT;
      }

      auto cnt = recvfrom(sock, (void *)message, len, flags,
                          (struct sockaddr *)&addr, &addrlen);

      if (cnt < 0)
      {
         if (errno == EAGAIN || errno == EWOULDBLOCK)
            return 0;
         perror("recvfrom");
         abort();
      }

      return cnt;
   }

}
