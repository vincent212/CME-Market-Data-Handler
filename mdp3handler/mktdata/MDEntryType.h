/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_MDENTRYTYPE_H_
#define _MKTDATA_MDENTRYTYPE_H_

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

class MDEntryType
{
public:
    enum Value
    {
        Bid = static_cast<char>(48),
        Offer = static_cast<char>(49),
        Trade = static_cast<char>(50),
        OpenPrice = static_cast<char>(52),
        SettlementPrice = static_cast<char>(54),
        TradingSessionHighPrice = static_cast<char>(55),
        TradingSessionLowPrice = static_cast<char>(56),
        ClearedVolume = static_cast<char>(66),
        OpenInterest = static_cast<char>(67),
        ImpliedBid = static_cast<char>(69),
        ImpliedOffer = static_cast<char>(70),
        BookReset = static_cast<char>(74),
        SessionHighBid = static_cast<char>(78),
        SessionLowOffer = static_cast<char>(79),
        FixingPrice = static_cast<char>(87),
        ElectronicVolume = static_cast<char>(101),
        ThresholdLimitsandPriceBandVariation = static_cast<char>(103),
        NULL_VALUE = static_cast<char>(0)
    };

    static MDEntryType::Value get(const char value)
    {
        switch (value)
        {
            case static_cast<char>(48): return Bid;
            case static_cast<char>(49): return Offer;
            case static_cast<char>(50): return Trade;
            case static_cast<char>(52): return OpenPrice;
            case static_cast<char>(54): return SettlementPrice;
            case static_cast<char>(55): return TradingSessionHighPrice;
            case static_cast<char>(56): return TradingSessionLowPrice;
            case static_cast<char>(66): return ClearedVolume;
            case static_cast<char>(67): return OpenInterest;
            case static_cast<char>(69): return ImpliedBid;
            case static_cast<char>(70): return ImpliedOffer;
            case static_cast<char>(74): return BookReset;
            case static_cast<char>(78): return SessionHighBid;
            case static_cast<char>(79): return SessionLowOffer;
            case static_cast<char>(87): return FixingPrice;
            case static_cast<char>(101): return ElectronicVolume;
            case static_cast<char>(103): return ThresholdLimitsandPriceBandVariation;
            case static_cast<char>(0): return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum MDEntryType [E103]");
    }

    static const char *c_str(const MDEntryType::Value value)
    {
        switch (value)
        {
            case Bid: return "Bid";
            case Offer: return "Offer";
            case Trade: return "Trade";
            case OpenPrice: return "OpenPrice";
            case SettlementPrice: return "SettlementPrice";
            case TradingSessionHighPrice: return "TradingSessionHighPrice";
            case TradingSessionLowPrice: return "TradingSessionLowPrice";
            case ClearedVolume: return "ClearedVolume";
            case OpenInterest: return "OpenInterest";
            case ImpliedBid: return "ImpliedBid";
            case ImpliedOffer: return "ImpliedOffer";
            case BookReset: return "BookReset";
            case SessionHighBid: return "SessionHighBid";
            case SessionLowOffer: return "SessionLowOffer";
            case FixingPrice: return "FixingPrice";
            case ElectronicVolume: return "ElectronicVolume";
            case ThresholdLimitsandPriceBandVariation: return "ThresholdLimitsandPriceBandVariation";
            case NULL_VALUE: return "NULL_VALUE";
        }

        throw std::runtime_error("unknown value for enum MDEntryType [E103]:");
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &os, MDEntryType::Value m)
    {
        return os << MDEntryType::c_str(m);
    }
};

}

#endif
