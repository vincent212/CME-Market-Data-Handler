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

#include <cstdint>
#include <math.h>
#include <string>
#include <map>
#include <chrono>

namespace m2tech::mdp3
{

    /**
     * @brief Callback interface from handler to application.
     * 
     * The application must subclass this class and provide implementation for each callback.
     * For documentation of each message please the CME group website.
     * https://www.cmegroup.com/confluence/display/EPICSANDBOX/MDP+3.0+-+Market+Data+Incremental+Refresh
     */
    struct CallBackIF
    {

        /**
         * @brief for MBP
         * 
         * @param recv_time 
         * @param msgSeqNum 
         * @param transactTime 
         * @param sendingTime 
         * @param securityID 
         * @param px_mantissa 
         * @param px_exponent 
         * @param side 
         * @param sz 
         * @param numorders 
         * @param pxlevel 
         * @param endOfEvent 
         * @param recovery 
         */
        virtual void MDIncrementalRefreshBook(
            uint64_t recv_time, 
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            uint32_t securityID,
            int64_t px_mantissa,
            int8_t px_exponent,
            char side,
            int32_t sz,
            int32_t numorders,
            uint8_t pxlevel,
            bool endOfEvent,
            bool recovery) noexcept = 0;

        /**
         * @brief for MBO
         * Note that the order book reconstruction code must ignore updates
         * that have transaction time <= last recovery transaction time.
         * It can also optionaly ignore recovery updates if the last transaction
         * time is greater than recovery updates.
         * 
         * @param recv_time 
         * @param msgSeqNum 
         * @param transactTime 
         * @param sendingTime 
         * @param securityID 
         * @param px_mantissa 
         * @param px_exponent 
         * @param side 
         * @param displayQty 
         * @param orderID 
         * @param orderUpdateAction 
         * @param priority 
         * @param endOfEvent 
         * @param recovery 
         */
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

        /**
         * @brief for MBP
         * 
         * @param recv_time 
         * @param msgSeqNum 
         * @param transactTime 
         * @param sendingTime 
         * @param securityID 
         * @param px_mantissa 
         * @param px_exponent 
         * @param side 
         * @param aggressor_side 
         * @param sz 
         * @param numorders 
         * @param lastTrade 
         * @param endofEvent 
         */
        virtual void MDIncrementalRefreshTradeSummary(
            uint64_t recv_time, 
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            int32_t securityID,
            int64_t px_mantissa,
            int8_t px_exponent,
            char side,
            uint8_t aggressor_side,
            int32_t sz,
            int32_t numorders,
            bool lastTrade,
            bool endofEvent) noexcept = 0;

        /**
         * @brief for MBO
         * 
         * @param recv_time 
         * @param msgSeqNum 
         * @param transactTime 
         * @param sendingTime 
         * @param lastQty 
         * @param orderID 
         * @param lastTrade 
         * @param endofEvent 
         */
        virtual void MDIncrementalRefreshTradeSummary(
            uint64_t recv_time,
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            int32_t lastQty,
            uint64_t orderID,
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

        // MBP recovery is not implemented
        // use natural recovery instead
#ifdef NOTIMPLEMENTED
        virtual void SnapshotFullRefresh(
            uint32_t msgSeqNum,
            uint64_t transactTime,
            uint64_t sendingTime,
            int32_t securityID,
            int64_t px_mantissa,
            int64_t px_exponent,
            uint32_t sz,
            int8_t px_level,
            int32_t numorders,
            char side) noexcept = 0;
#endif

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
            uint8_t action) noexcept = 0;

        /**
         * @brief A call to this function indicates that a gap was detected
         * The book must be cleared. Updates with recovery = true flag
         * will follow.
         */
        virtual void Clear() noexcept = 0;

        /**
         * @brief Convert CME price to a double
         * 
         * @param mantissa 
         * @param exponent 
         * @return double 
         */
        double to_price(int64_t mantissa, int8_t exponent)
        {
            return double(mantissa) * std::pow(10., double(exponent));
        }
    };

}
