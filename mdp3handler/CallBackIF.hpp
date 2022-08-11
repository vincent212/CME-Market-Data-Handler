/*

THIS SOFTWARE IS OPEN SOURCE UNDER THE MIT LICENSE
SUPPORT IS AVAILABE FROM THE AUTHORS

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

#include <cstdint>
#include <math.h>
#include <string>
#include <map>
#include <chrono>

namespace m2tech::mdp3
{

    struct CallBackIF
    {

        virtual void MDIncrementalRefreshBook(
            uint64_t recv_time, 
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            uint32_t securityID,
            int64_t px_mantissa,
            int8_t px_exponent,
            char side, // 0 = buy, 1 = sell
            int32_t displayQty,
            uint64_t orderID,
            uint8_t orderUpdateAction,
            uint64_t priority,
            bool endOfEvent,
            bool recovery) noexcept = 0;

        virtual void MDIncrementalRefreshTradeSummary(
            uint64_t recv_time, 
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            int32_t lastQty,
            uint64_t orderID,
            int32_t securityID,
            bool lastTrade,
            bool endofEvent) noexcept = 0;

        virtual void MDIncrementalRefreshSessionStatistics(
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            uint32_t secid,
            uint8_t openCloseSettleFlag,
            int64_t px_mantissa,
            int64_t px_exponent,
            uint8_t updateAction,
            char entryType) noexcept = 0;

        virtual void MDInstrumentDefinitionFuture(
            uint32_t msgSeqNum,
            uint64_t sendingTime,
            char *sym,
            char *asset,
            char *cfiCode,
            int64_t high_limit_px_mantissa,
            int8_t high_limit_px_exponent,
            int64_t low_limit_px_mantissa,
            int8_t low_limit_px_exponent,
            int64_t pxvar_mantissa,
            int8_t pxvar_exponent,
            int32_t sec_id,
            char updateAction,
            uint8_t tradingStatus,
            uint64_t activation,
            uint64_t expiration,
            char *sec_group,
            uint8_t seg_id) noexcept = 0;

        virtual void ChannelReset(
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            const char *mdEntryType) noexcept = 0;

        virtual void SnapshotFullRefreshOrderBook(
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            uint32_t currentChunk,
            uint32_t numChunks,
            int32_t securityID,
            int32_t displayQty,
            int64_t px_mantissa,
            int64_t px_exponent,
            char side,
            uint64_t orderPriority,
            uint64_t orderID) noexcept = 0;

        virtual void MDIncrementalRefreshLimitsBanding(
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            int32_t securityID,
            int64_t pxh_mantissa,
            int8_t pxh_exponent,
            int64_t pxl_mantissa,
            int8_t pxl_exponent,
            int64_t pxvar_mantissa,
            int8_t pxvar_exponent,
            const char *entryType) noexcept = 0;

        virtual void SecurityStatus(
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            int32_t securityID,
            uint8_t haltReason,
            uint8_t tradingStatus,
            uint8_t tradingEvent) noexcept = 0;

        virtual void MDIncrementalRefreshVolume(
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            int32_t securityID,
            int32_t volume,
            char typ,
            uint8_t action
        ) noexcept = 0;

        virtual void Clear() noexcept = 0;

        double to_price(int64_t mantissa, int8_t exponent)
        {
            return double(mantissa) * std::pow(10., double(exponent));
        }
    };

}