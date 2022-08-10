/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_HALTREASON_H_
#define _MKTDATA_HALTREASON_H_

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

class HaltReason
{
public:
    enum Value
    {
        GroupSchedule = static_cast<std::uint8_t>(0),
        SurveillanceIntervention = static_cast<std::uint8_t>(1),
        MarketEvent = static_cast<std::uint8_t>(2),
        InstrumentActivation = static_cast<std::uint8_t>(3),
        InstrumentExpiration = static_cast<std::uint8_t>(4),
        Unknown = static_cast<std::uint8_t>(5),
        RecoveryInProcess = static_cast<std::uint8_t>(6),
        NULL_VALUE = static_cast<std::uint8_t>(255)
    };

    static HaltReason::Value get(const std::uint8_t value)
    {
        switch (value)
        {
            case static_cast<std::uint8_t>(0): return GroupSchedule;
            case static_cast<std::uint8_t>(1): return SurveillanceIntervention;
            case static_cast<std::uint8_t>(2): return MarketEvent;
            case static_cast<std::uint8_t>(3): return InstrumentActivation;
            case static_cast<std::uint8_t>(4): return InstrumentExpiration;
            case static_cast<std::uint8_t>(5): return Unknown;
            case static_cast<std::uint8_t>(6): return RecoveryInProcess;
            case static_cast<std::uint8_t>(255): return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum HaltReason [E103]");
    }

    static const char *c_str(const HaltReason::Value value)
    {
        switch (value)
        {
            case GroupSchedule: return "GroupSchedule";
            case SurveillanceIntervention: return "SurveillanceIntervention";
            case MarketEvent: return "MarketEvent";
            case InstrumentActivation: return "InstrumentActivation";
            case InstrumentExpiration: return "InstrumentExpiration";
            case Unknown: return "Unknown";
            case RecoveryInProcess: return "RecoveryInProcess";
            case NULL_VALUE: return "NULL_VALUE";
        }

        throw std::runtime_error("unknown value for enum HaltReason [E103]:");
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &os, HaltReason::Value m)
    {
        return os << HaltReason::c_str(m);
    }
};

}

#endif
