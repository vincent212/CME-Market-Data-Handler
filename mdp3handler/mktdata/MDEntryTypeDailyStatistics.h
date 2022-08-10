/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_MDENTRYTYPEDAILYSTATISTICS_H_
#define _MKTDATA_MDENTRYTYPEDAILYSTATISTICS_H_

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

class MDEntryTypeDailyStatistics
{
public:
    enum Value
    {
        SettlementPrice = static_cast<char>(54),
        ClearedVolume = static_cast<char>(66),
        OpenInterest = static_cast<char>(67),
        FixingPrice = static_cast<char>(87),
        NULL_VALUE = static_cast<char>(0)
    };

    static MDEntryTypeDailyStatistics::Value get(const char value)
    {
        switch (value)
        {
            case static_cast<char>(54): return SettlementPrice;
            case static_cast<char>(66): return ClearedVolume;
            case static_cast<char>(67): return OpenInterest;
            case static_cast<char>(87): return FixingPrice;
            case static_cast<char>(0): return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum MDEntryTypeDailyStatistics [E103]");
    }

    static const char *c_str(const MDEntryTypeDailyStatistics::Value value)
    {
        switch (value)
        {
            case SettlementPrice: return "SettlementPrice";
            case ClearedVolume: return "ClearedVolume";
            case OpenInterest: return "OpenInterest";
            case FixingPrice: return "FixingPrice";
            case NULL_VALUE: return "NULL_VALUE";
        }

        throw std::runtime_error("unknown value for enum MDEntryTypeDailyStatistics [E103]:");
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &os, MDEntryTypeDailyStatistics::Value m)
    {
        return os << MDEntryTypeDailyStatistics::c_str(m);
    }
};

}

#endif
