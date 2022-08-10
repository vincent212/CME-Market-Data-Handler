/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_SECURITYTRADINGEVENT_H_
#define _MKTDATA_SECURITYTRADINGEVENT_H_

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

class SecurityTradingEvent
{
public:
    enum Value
    {
        NoEvent = static_cast<std::uint8_t>(0),
        NoCancel = static_cast<std::uint8_t>(1),
        ResetStatistics = static_cast<std::uint8_t>(4),
        ImpliedMatchingON = static_cast<std::uint8_t>(5),
        ImpliedMatchingOFF = static_cast<std::uint8_t>(6),
        NULL_VALUE = static_cast<std::uint8_t>(255)
    };

    static SecurityTradingEvent::Value get(const std::uint8_t value)
    {
        switch (value)
        {
            case static_cast<std::uint8_t>(0): return NoEvent;
            case static_cast<std::uint8_t>(1): return NoCancel;
            case static_cast<std::uint8_t>(4): return ResetStatistics;
            case static_cast<std::uint8_t>(5): return ImpliedMatchingON;
            case static_cast<std::uint8_t>(6): return ImpliedMatchingOFF;
            case static_cast<std::uint8_t>(255): return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum SecurityTradingEvent [E103]");
    }

    static const char *c_str(const SecurityTradingEvent::Value value)
    {
        switch (value)
        {
            case NoEvent: return "NoEvent";
            case NoCancel: return "NoCancel";
            case ResetStatistics: return "ResetStatistics";
            case ImpliedMatchingON: return "ImpliedMatchingON";
            case ImpliedMatchingOFF: return "ImpliedMatchingOFF";
            case NULL_VALUE: return "NULL_VALUE";
        }

        throw std::runtime_error("unknown value for enum SecurityTradingEvent [E103]:");
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &os, SecurityTradingEvent::Value m)
    {
        return os << SecurityTradingEvent::c_str(m);
    }
};

}

#endif
