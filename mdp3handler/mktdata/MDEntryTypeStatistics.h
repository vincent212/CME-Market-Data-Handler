/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_MDENTRYTYPESTATISTICS_H_
#define _MKTDATA_MDENTRYTYPESTATISTICS_H_

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

class MDEntryTypeStatistics
{
public:
    enum Value
    {
        OpenPrice = static_cast<char>(52),
        HighTrade = static_cast<char>(55),
        LowTrade = static_cast<char>(56),
        HighestBid = static_cast<char>(78),
        LowestOffer = static_cast<char>(79),
        NULL_VALUE = static_cast<char>(0)
    };

    static MDEntryTypeStatistics::Value get(const char value)
    {
        switch (value)
        {
            case static_cast<char>(52): return OpenPrice;
            case static_cast<char>(55): return HighTrade;
            case static_cast<char>(56): return LowTrade;
            case static_cast<char>(78): return HighestBid;
            case static_cast<char>(79): return LowestOffer;
            case static_cast<char>(0): return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum MDEntryTypeStatistics [E103]");
    }

    static const char *c_str(const MDEntryTypeStatistics::Value value)
    {
        switch (value)
        {
            case OpenPrice: return "OpenPrice";
            case HighTrade: return "HighTrade";
            case LowTrade: return "LowTrade";
            case HighestBid: return "HighestBid";
            case LowestOffer: return "LowestOffer";
            case NULL_VALUE: return "NULL_VALUE";
        }

        throw std::runtime_error("unknown value for enum MDEntryTypeStatistics [E103]:");
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &os, MDEntryTypeStatistics::Value m)
    {
        return os << MDEntryTypeStatistics::c_str(m);
    }
};

}

#endif
