/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_ORDERUPDATEACTION_H_
#define _MKTDATA_ORDERUPDATEACTION_H_

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

class OrderUpdateAction
{
public:
    enum Value
    {
        New = static_cast<std::uint8_t>(0),
        Update = static_cast<std::uint8_t>(1),
        Delete = static_cast<std::uint8_t>(2),
        NULL_VALUE = static_cast<std::uint8_t>(255)
    };

    static OrderUpdateAction::Value get(const std::uint8_t value)
    {
        switch (value)
        {
            case static_cast<std::uint8_t>(0): return New;
            case static_cast<std::uint8_t>(1): return Update;
            case static_cast<std::uint8_t>(2): return Delete;
            case static_cast<std::uint8_t>(255): return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum OrderUpdateAction [E103]");
    }

    static const char *c_str(const OrderUpdateAction::Value value)
    {
        switch (value)
        {
            case New: return "New";
            case Update: return "Update";
            case Delete: return "Delete";
            case NULL_VALUE: return "NULL_VALUE";
        }

        throw std::runtime_error("unknown value for enum OrderUpdateAction [E103]:");
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &os, OrderUpdateAction::Value m)
    {
        return os << OrderUpdateAction::c_str(m);
    }
};

}

#endif
