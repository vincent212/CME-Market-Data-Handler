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

#include <iostream>
#include <chrono>
#include "mktdata/MDIncrementalRefreshBook46.h"
#include "mktdata/MDIncrementalRefreshSessionStatistics51.h"
#include "mktdata/MDInstrumentDefinitionFuture54.h"
#include "mktdata/MDIncrementalRefreshTradeSummary48.h"
#include "mktdata/MDIncrementalRefreshOrderBook47.h"
#include "mktdata/SnapshotFullRefreshOrderBook53.h"
#include "mktdata/ChannelReset4.h"
#include "mktdata/MDIncrementalRefreshLimitsBanding50.h"
#include "mktdata/MDIncrementalRefreshVolume37.h"
#include "mktdata/MDIncrementalRefreshDailyStatistics49.h"
#include "mktdata/SecurityStatus30.h"
#include "mktdata/QuoteRequest39.h"
#include "mktdata/AdminHeartbeat12.h"
#include "CallBackIF.hpp"

namespace m2tech::mdp3
{

    /**
     * @brief This class transforms binary data into SBE data structures.
     * 
     */
    struct DataDecoder
    {

        /**
         * @brief Repeating group type
         * 
         */
        typedef struct
        {
            int32_t secid;
            int64_t px_mantissa;
            int8_t px_exponent;
            uint32_t seq;
            uint8_t side;
            uint32_t sz;
            int32_t numorders;
            uint8_t pxlevel;
        } repg1_t;

        std::vector<repg1_t> g1;
        CallBackIF *cb;
        bool debug = false;

        /**
         * @brief Construct a new Data Decoder object
         * 
         * @param _cb callback object that implements message processing logic
         * @param _debug turn on debugging
         */
        DataDecoder(CallBackIF *_cb, bool _debug) : cb(_cb), debug(_debug)
        {
            g1.reserve(1024);
        }

        /**
         * @brief Transform binary data into a SBE data structure
         * 
         * @param databuf binary data
         * @param len length
         * @param ts timestamp
         */
        void mbo_data(char *databuf, size_t len, uint64_t ts)
        {
            auto data_start = databuf;

            constexpr size_t sbe_message_header_size = 10;

            auto MsgSeqNum = *(uint32_t *)(databuf);
            databuf += sizeof(MsgSeqNum);
            auto SendingTime = *(uint64_t *)(databuf);
            databuf += sizeof(SendingTime);

            if (debug)
            {
                std::cout << "DECODING SEQ: " << MsgSeqNum << " len: " << len << std::endl;
            }

            while (size_t(databuf - data_start) < len)
            {

                auto MsgSize = *(uint16_t *)(databuf);
                databuf += sizeof(MsgSize);
                auto BlockLength = *(uint16_t *)(databuf);
                databuf += sizeof(BlockLength);
                auto tempalate_id = *(uint16_t *)(databuf);
                databuf += sizeof(tempalate_id);
                auto SchemaID = *(uint16_t *)(databuf);
                databuf += sizeof(SchemaID);
                auto Version = *(uint16_t *)(databuf);
                databuf += sizeof(Version);

                databuf -= sbe_message_header_size;

                if (debug)
                {
                    std::cout << "-----------------------------------------------------------------------------\n";
                    std::cout << "MsgSize: " << MsgSize << " tempalate_id: " << tempalate_id << " SchemaID: " << SchemaID << " Version: " << Version << "\n";
                }

                switch (tempalate_id)
                {
                case 46:
                {
                    mktdata::MDIncrementalRefreshBook46 incr;
                    incr.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << incr << std::endl;
                    }

                    auto txtim = incr.transactTime();
                    auto matchevent = incr.matchEventIndicator();
                    auto noMDEntries = incr.noMDEntries();

                    g1.clear();
                    while (noMDEntries.hasNext())
                    {
                        noMDEntries.next();
                        repg1_t g;
                        g.secid = noMDEntries.securityID();
                        g.px_mantissa = noMDEntries.mDEntryPx().mantissa();
                        g.px_exponent = noMDEntries.mDEntryPx().exponent();
                        g.seq = noMDEntries.rptSeq();
                        g.side = noMDEntries.mDEntryType();
                        g.sz = noMDEntries.mDEntrySize();
                        g.numorders = noMDEntries.numberOfOrders();
                        g.pxlevel = noMDEntries.mDPriceLevel();
                        g1.push_back(g);
                        cb->MDIncrementalRefreshBook(
                            ts,
                            MsgSeqNum,
                            txtim,
                            SendingTime,
                            g.secid,
                            g.px_mantissa,
                            g.px_exponent,
                            g.side,
                            g.sz,
                            g.numorders,
                            g.pxlevel,
                            matchevent.endOfEvent(),
                            matchevent.recoveryMsg()
                        );
                    }
                    auto oidentries = incr.noOrderIDEntries();

                    while (oidentries.hasNext())
                    {
                        oidentries.next();
                        auto dispq = oidentries.mDDisplayQty();
                        auto oid = oidentries.orderID();
                        auto act = oidentries.orderUpdateAction();
                        auto prio = oidentries.mDOrderPriority();
                        auto idx = oidentries.referenceID();
                        cb->MDIncrementalRefreshBook(
                            ts,
                            MsgSeqNum,
                            txtim,
                            SendingTime,
                            g1[idx - 1].secid,
                            g1[idx - 1].px_mantissa,
                            g1[idx - 1].px_exponent,
                            g1[idx - 1].side,
                            dispq,
                            oid,
                            act,
                            prio,
                            matchevent.endOfEvent(),
                            matchevent.recoveryMsg());
                    }
                    break;
                }
                case 48:
                {
                    mktdata::MDIncrementalRefreshTradeSummary48 trade;
                    trade.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << trade << std::endl;
                    }

                    auto txtim = trade.transactTime();
                    auto matchevent = trade.matchEventIndicator();
                    auto noMDEntries = trade.noMDEntries();
                    int32_t securityId = 0;
                    while (noMDEntries.hasNext())
                    {
                        noMDEntries.next();
                        securityId = noMDEntries.securityID();
                        auto px_mant = noMDEntries.mDEntryPx().mantissa();
                        auto px_exp = noMDEntries.mDEntryPx().exponent();
                        auto side = noMDEntries.mDEntryType();
                        auto aggr_side = noMDEntries.aggressorSide();
                        auto sz = noMDEntries.mDEntrySize();
                        auto numorders = noMDEntries.numberOfOrders();
                        cb->MDIncrementalRefreshTradeSummary(
                            ts,
                            MsgSeqNum,
                            txtim,
                            SendingTime,
                            securityId,
                            px_mant,
                            px_exp,
                            *side,
                            aggr_side,
                            sz,
                            numorders,
                            matchevent.lastTradeMsg(),
                            matchevent.endOfEvent()
                        );
                    }

                    auto oidentries = trade.noOrderIDEntries();

                    while (oidentries.hasNext())
                    {
                        oidentries.next();
                        auto last = oidentries.lastQty();
                        auto oid = oidentries.orderID();
                        cb->MDIncrementalRefreshTradeSummary(
                            ts,
                            MsgSeqNum,
                            txtim,
                            SendingTime,
                            last,
                            oid,
                            matchevent.lastTradeMsg(),
                            matchevent.endOfEvent());
                    }
                    break;
                }
                case 51:
                {
                    mktdata::MDIncrementalRefreshSessionStatistics51 stats;
                    stats.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << stats << std::endl;
                    }

                    auto txtim = stats.transactTime();
                    auto mdentries = stats.noMDEntries();

                    while (mdentries.hasNext())
                    {
                        mdentries.next();
                        auto secid = mdentries.securityID();
                        auto ocsflag = mdentries.openCloseSettlFlag();
                        auto px_mantissa = mdentries.mDEntryPx().mantissa();
                        auto px_exponent = mdentries.mDEntryPx().mantissa();
                        auto update_act = mdentries.mDUpdateAction();
                        auto entry_typ = mdentries.mDEntryType();

                        cb->MDIncrementalRefreshSessionStatistics(
                            MsgSeqNum,
                            txtim,
                            SendingTime,
                            secid,
                            ocsflag,
                            px_mantissa,
                            px_exponent,
                            update_act,
                            entry_typ);
                    }
                    break;
                }
                case 54:
                {
                    mktdata::MDInstrumentDefinitionFuture54 def;
                    def.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << def << std::endl;
                    }

                    auto sym = def.symbol();
                    auto asset = def.asset();
                    auto cfiCode = def.cFICode();
                    auto high_limit_px_mantissa = def.highLimitPrice().mantissa();
                    auto high_limit_px_exponent = def.highLimitPrice().exponent();
                    auto low_limit_px_mantissa = def.lowLimitPrice().mantissa();
                    auto low_limit_px_exponent = def.lowLimitPrice().exponent();
                    auto pxvar_mantissa = def.maxPriceVariation().mantissa();
                    auto pxvar_exponent = def.maxPriceVariation().exponent();
                    auto sec_id = def.securityID();
                    auto sec_update_action = def.securityUpdateAction();
                    auto trading_status = def.mDSecurityTradingStatus();
                    auto sec_group = def.securityGroup();
                    auto mkt_seg = def.marketSegmentID();

                    uint64_t activation = 0, expiration = 0;
                    auto events = def.noEvents();
                    while (events.hasNext())
                    {
                        events.next();
                        auto evtime = events.eventTime();
                        auto evid = events.eventType();
                        if (evid == 5)
                        {
                            activation = evtime;
                        }
                        else if (evid == 7)
                        {
                            expiration = evtime;
                        }
                        else
                            abort();
                    }

                    cb->MDInstrumentDefinitionFuture(
                        MsgSeqNum,
                        SendingTime,
                        sym,
                        asset,
                        cfiCode,
                        high_limit_px_mantissa,
                        high_limit_px_exponent,
                        low_limit_px_mantissa,
                        low_limit_px_exponent,
                        pxvar_mantissa,
                        pxvar_exponent,
                        sec_id,
                        sec_update_action,
                        trading_status,
                        activation,
                        expiration,
                        sec_group,
                        mkt_seg);

                    break;
                }
                case 4:
                {
                    mktdata::ChannelReset4 reset;
                    reset.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << reset << std::endl;
                    }

                    auto txtim = reset.transactTime();
                    auto mdentries = reset.noMDEntries();
                    while (mdentries.hasNext())
                    {
                        mdentries.next();
                        auto entry_type = mdentries.mDEntryType();
                        cb->ChannelReset(
                            MsgSeqNum,
                            txtim,
                            SendingTime,
                            entry_type);
                    }
                    break;
                }
                case 50:
                {
                    mktdata::MDIncrementalRefreshLimitsBanding50 limits;
                    limits.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << limits << std::endl;
                    }

                    auto txtim = limits.transactTime();
                    auto mdentries = limits.noMDEntries();
                    while (mdentries.hasNext())
                    {
                        mdentries.next();
                        auto secid = mdentries.securityID();
                        auto pxh_mantissa = mdentries.highLimitPrice().mantissa();
                        auto pxh_exponent = mdentries.highLimitPrice().exponent();
                        auto pxl_mantissa = mdentries.lowLimitPrice().mantissa();
                        auto pxl_exponent = mdentries.lowLimitPrice().exponent();
                        auto pxvar_mantissa = mdentries.maxPriceVariation().mantissa();
                        auto pxvar_exponent = mdentries.maxPriceVariation().exponent();
                        auto entry_type = mdentries.mDEntryType();
                        cb->MDIncrementalRefreshLimitsBanding(
                            MsgSeqNum,
                            txtim,
                            SendingTime,
                            secid,
                            pxh_mantissa,
                            pxh_exponent,
                            pxl_mantissa,
                            pxl_exponent,
                            pxvar_mantissa,
                            pxvar_exponent,
                            entry_type);
                    }
                    break;
                }
                case 30:
                {
                    mktdata::SecurityStatus30 status;
                    status.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << status << std::endl;
                    }

                    auto txtim = status.transactTime();
                    auto secid = status.securityID();
                    auto haltreason = status.haltReason();
                    auto tradingstaus = status.securityTradingStatus();
                    auto tradingevent = status.securityTradingEvent();

                    cb->SecurityStatus(
                        MsgSeqNum,
                        txtim,
                        SendingTime,
                        secid,
                        haltreason,
                        tradingstaus,
                        tradingevent);
                    break;
                }
                case 47:
                {
                    mktdata::MDIncrementalRefreshOrderBook47 incr;
                    incr.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << incr << std::endl;
                    }

                    auto txtim = incr.transactTime();
                    auto matchevent = incr.matchEventIndicator();

                    auto noMdEntries = incr.noMDEntries();

                    while (noMdEntries.hasNext())
                    {
                        noMdEntries.next();
                        auto dispq = noMdEntries.mDDisplayQty();
                        auto oid = noMdEntries.orderID();
                        auto act = noMdEntries.mDUpdateAction();
                        auto side = noMdEntries.mDEntryType();
                        auto prio = noMdEntries.mDOrderPriority();
                        auto px_mantissa = noMdEntries.mDEntryPx().mantissa();
                        auto px_exponent = noMdEntries.mDEntryPx().exponent();
                        auto secid = noMdEntries.securityID();

                        cb->MDIncrementalRefreshBook(
                            ts,
                            MsgSeqNum,
                            txtim,
                            SendingTime,
                            secid,
                            px_mantissa,
                            px_exponent,
                            side,
                            dispq,
                            oid,
                            act,
                            prio,
                            matchevent.endOfEvent(),
                            matchevent.recoveryMsg());
                    }

                    break;
                }
                case 37:
                {
                    mktdata::MDIncrementalRefreshVolume37 vol;
                    vol.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << vol << std::endl;
                    }

                    auto txtim = vol.transactTime();

                    auto noMdEntries = vol.noMDEntries();

                    while (noMdEntries.hasNext())
                    {
                        noMdEntries.next();
                        auto vol = noMdEntries.mDEntrySize();
                        auto secid = noMdEntries.securityID();
                        auto typ = noMdEntries.mDEntryType();
                        auto act = noMdEntries.mDUpdateAction();

                        cb->MDIncrementalRefreshVolume(
                            MsgSeqNum,
                            txtim,
                            SendingTime,
                            secid, 
                            vol, 
                            *typ, 
                            act);
                    }

                    break;
                }
                case 12:
                {
                    // mktdata::AdminHeartbeat12 beat;
                    break;
                }
                case 39:
                {
                    mktdata::QuoteRequest39 rfq;
                    rfq.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);

                    if (debug)
                    {
                        std::cout << rfq << std::endl;
                    }

                    break;
                }
                case 49:
                {
                    mktdata::MDIncrementalRefreshDailyStatistics49 stats;
                    stats.wrapForDecode(databuf, sbe_message_header_size, BlockLength, Version, MsgSize);
                    if (debug)
                    {
                        std::cout << stats << std::endl;
                    }
                }
                default:
                {
                    if (debug)
                        std::cout << "UNKNONWN MESSAGE " << tempalate_id << std::endl;
                    break;
                }
                }

                databuf += MsgSize;
            }
        }

        /**
         * @brief Called from MessageProcessor to clear order books after a gap.
         * 
         */
        void clear()
        {
            cb->Clear();
        }
    };
}
