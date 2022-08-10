/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_MDENTRYTYPEBOOK_H_
#define _MKTDATA_MDENTRYTYPEBOOK_H_

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

class MDEntryTypeBook
{
public:
    enum Value
    {
        Bid = static_cast<char>(48),
        Offer = static_cast<char>(49),
        ImpliedBid = static_cast<char>(69),
        ImpliedOffer = static_cast<char>(70),
        BookReset = static_cast<char>(74),
        NULL_VALUE = static_cast<char>(0)
    };

    static MDEntryTypeBook::Value get(const char value)
    {
        switch (value)
        {
            case static_cast<char>(48): return Bid;
            case static_cast<char>(49): return Offer;
            case static_cast<char>(69): return ImpliedBid;
            case static_cast<char>(70): return ImpliedOffer;
            case static_cast<char>(74): return BookReset;
            case static_cast<char>(0): return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum MDEntryTypeBook [E103]");
    }

    static const char *c_str(const MDEntryTypeBook::Value value)
    {
        switch (value)
        {
            case Bid: return "Bid";
            case Offer: return "Offer";
            case ImpliedBid: return "ImpliedBid";
            case ImpliedOffer: return "ImpliedOffer";
            case BookReset: return "BookReset";
            case NULL_VALUE: return "NULL_VALUE";
        }

        throw std::runtime_error("unknown value for enum MDEntryTypeBook [E103]:");
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &os, MDEntryTypeBook::Value m)
    {
        return os << MDEntryTypeBook::c_str(m);
    }
};

}

#endif
