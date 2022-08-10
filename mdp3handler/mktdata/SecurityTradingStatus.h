/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_SECURITYTRADINGSTATUS_H_
#define _MKTDATA_SECURITYTRADINGSTATUS_H_

#if !defined(__STDC_LIMIT_MACROS)
#  define __STDC_LIMIT_MACROS 1
#endif

#include <cstdint>
#include <iomanip>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <sstream>
#include <string>

#define SBE_NULLVALUE_INT8 (std::numeric_limits<std::int8_t>::min)()
#define SBE_NULLVALUE_INT16 (std::numeric_limits<std::int16_t>::min)()
#define SBE_NULLVALUE_INT32 (std::numeric_limits<std::int32_t>::min)()
#define SBE_NULLVALUE_INT64 (std::numeric_limits<std::int64_t>::min)()
#define SBE_NULLVALUE_UINT8 (std::numeric_limits<std::uint8_t>::max)()
#define SBE_NULLVALUE_UINT16 (std::numeric_limits<std::uint16_t>::max)()
#define SBE_NULLVALUE_UINT32 (std::numeric_limits<std::uint32_t>::max)()
#define SBE_NULLVALUE_UINT64 (std::numeric_limits<std::uint64_t>::max)()

namespace mktdata {

class SecurityTradingStatus
{
public:
    enum Value
    {
        TradingHalt = static_cast<std::uint8_t>(2),
        Close = static_cast<std::uint8_t>(4),
        NewPriceIndication = static_cast<std::uint8_t>(15),
        ReadyToTrade = static_cast<std::uint8_t>(17),
        NotAvailableForTrading = static_cast<std::uint8_t>(18),
        UnknownorInvalid = static_cast<std::uint8_t>(20),
        PreOpen = static_cast<std::uint8_t>(21),
        PreCross = static_cast<std::uint8_t>(24),
        Cross = static_cast<std::uint8_t>(25),
        PostClose = static_cast<std::uint8_t>(26),
        NoChange = static_cast<std::uint8_t>(103),
        NULL_VALUE = static_cast<std::uint8_t>(255)
    };

    static SecurityTradingStatus::Value get(const std::uint8_t value)
    {
        switch (value)
        {
            case static_cast<std::uint8_t>(2): return TradingHalt;
            case static_cast<std::uint8_t>(4): return Close;
            case static_cast<std::uint8_t>(15): return NewPriceIndication;
            case static_cast<std::uint8_t>(17): return ReadyToTrade;
            case static_cast<std::uint8_t>(18): return NotAvailableForTrading;
            case static_cast<std::uint8_t>(20): return UnknownorInvalid;
            case static_cast<std::uint8_t>(21): return PreOpen;
            case static_cast<std::uint8_t>(24): return PreCross;
            case static_cast<std::uint8_t>(25): return Cross;
            case static_cast<std::uint8_t>(26): return PostClose;
            case static_cast<std::uint8_t>(103): return NoChange;
            case static_cast<std::uint8_t>(255): return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum SecurityTradingStatus [E103]");
    }

    static const char *c_str(const SecurityTradingStatus::Value value)
    {
        switch (value)
        {
            case TradingHalt: return "TradingHalt";
            case Close: return "Close";
            case NewPriceIndication: return "NewPriceIndication";
            case ReadyToTrade: return "ReadyToTrade";
            case NotAvailableForTrading: return "NotAvailableForTrading";
            case UnknownorInvalid: return "UnknownorInvalid";
            case PreOpen: return "PreOpen";
            case PreCross: return "PreCross";
            case Cross: return "Cross";
            case PostClose: return "PostClose";
            case NoChange: return "NoChange";
            case NULL_VALUE: return "NULL_VALUE";
        }

        throw std::runtime_error("unknown value for enum SecurityTradingStatus [E103]:");
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &os, SecurityTradingStatus::Value m)
    {
        return os << SecurityTradingStatus::c_str(m);
    }
};

}

#endif
