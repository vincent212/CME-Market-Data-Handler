/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_SETTLPRICETYPE_H_
#define _MKTDATA_SETTLPRICETYPE_H_

#if defined(SBE_HAVE_CMATH)
/* cmath needed for std::numeric_limits<double>::quiet_NaN() */
#  include <cmath>
#  define SBE_FLOAT_NAN std::numeric_limits<float>::quiet_NaN()
#  define SBE_DOUBLE_NAN std::numeric_limits<double>::quiet_NaN()
#else
/* math.h needed for NAN */
#  include <math.h>
#  define SBE_FLOAT_NAN NAN
#  define SBE_DOUBLE_NAN NAN
#endif

#if __cplusplus >= 201103L
#  define SBE_CONSTEXPR constexpr
#  define SBE_NOEXCEPT noexcept
#else
#  define SBE_CONSTEXPR
#  define SBE_NOEXCEPT
#endif

#if __cplusplus >= 201703L
#  include <string_view>
#  define SBE_NODISCARD [[nodiscard]]
#else
#  define SBE_NODISCARD
#endif

#if !defined(__STDC_LIMIT_MACROS)
#  define __STDC_LIMIT_MACROS 1
#endif

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

#if defined(WIN32) || defined(_WIN32)
#  define SBE_BIG_ENDIAN_ENCODE_16(v) _byteswap_ushort(v)
#  define SBE_BIG_ENDIAN_ENCODE_32(v) _byteswap_ulong(v)
#  define SBE_BIG_ENDIAN_ENCODE_64(v) _byteswap_uint64(v)
#  define SBE_LITTLE_ENDIAN_ENCODE_16(v) (v)
#  define SBE_LITTLE_ENDIAN_ENCODE_32(v) (v)
#  define SBE_LITTLE_ENDIAN_ENCODE_64(v) (v)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define SBE_BIG_ENDIAN_ENCODE_16(v) __builtin_bswap16(v)
#  define SBE_BIG_ENDIAN_ENCODE_32(v) __builtin_bswap32(v)
#  define SBE_BIG_ENDIAN_ENCODE_64(v) __builtin_bswap64(v)
#  define SBE_LITTLE_ENDIAN_ENCODE_16(v) (v)
#  define SBE_LITTLE_ENDIAN_ENCODE_32(v) (v)
#  define SBE_LITTLE_ENDIAN_ENCODE_64(v) (v)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define SBE_LITTLE_ENDIAN_ENCODE_16(v) __builtin_bswap16(v)
#  define SBE_LITTLE_ENDIAN_ENCODE_32(v) __builtin_bswap32(v)
#  define SBE_LITTLE_ENDIAN_ENCODE_64(v) __builtin_bswap64(v)
#  define SBE_BIG_ENDIAN_ENCODE_16(v) (v)
#  define SBE_BIG_ENDIAN_ENCODE_32(v) (v)
#  define SBE_BIG_ENDIAN_ENCODE_64(v) (v)
#else
#  error "Byte Ordering of platform not determined. Set __BYTE_ORDER__ manually before including this file."
#endif

#if defined(SBE_NO_BOUNDS_CHECK)
#  define SBE_BOUNDS_CHECK_EXPECT(exp, c) (false)
#elif defined(_MSC_VER)
#  define SBE_BOUNDS_CHECK_EXPECT(exp, c) (exp)
#else
#  define SBE_BOUNDS_CHECK_EXPECT(exp, c) (__builtin_expect(exp, c))
#endif

#define SBE_NULLVALUE_INT8 (std::numeric_limits<std::int8_t>::min)()
#define SBE_NULLVALUE_INT16 (std::numeric_limits<std::int16_t>::min)()
#define SBE_NULLVALUE_INT32 (std::numeric_limits<std::int32_t>::min)()
#define SBE_NULLVALUE_INT64 (std::numeric_limits<std::int64_t>::min)()
#define SBE_NULLVALUE_UINT8 (std::numeric_limits<std::uint8_t>::max)()
#define SBE_NULLVALUE_UINT16 (std::numeric_limits<std::uint16_t>::max)()
#define SBE_NULLVALUE_UINT32 (std::numeric_limits<std::uint32_t>::max)()
#define SBE_NULLVALUE_UINT64 (std::numeric_limits<std::uint64_t>::max)()


namespace mktdata {

class SettlPriceType
{
private:
    char *m_buffer = nullptr;
    std::uint64_t m_bufferLength = 0;
    std::uint64_t m_offset = 0;
    std::uint64_t m_actingVersion = 0;

public:
    enum MetaAttribute
    {
        EPOCH, TIME_UNIT, SEMANTIC_TYPE, PRESENCE
    };

    union sbe_float_as_uint_u
    {
        float fp_value;
        std::uint32_t uint_value;
    };

    union sbe_double_as_uint_u
    {
        double fp_value;
        std::uint64_t uint_value;
    };

    SettlPriceType() = default;

    SettlPriceType(
        char *buffer,
        const std::uint64_t offset,
        const std::uint64_t bufferLength,
        const std::uint64_t actingVersion) :
        m_buffer(buffer),
        m_bufferLength(bufferLength),
        m_offset(offset),
        m_actingVersion(actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((m_offset + 1) > m_bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }
    }

    SettlPriceType(
        char *buffer,
        const std::uint64_t bufferLength,
        const std::uint64_t actingVersion) :
        SettlPriceType(buffer, 0, bufferLength, actingVersion)
    {
    }

    SettlPriceType(
        char *buffer,
        const std::uint64_t bufferLength) :
        SettlPriceType(buffer, 0, bufferLength, sbeSchemaVersion())
    {
    }

    SettlPriceType &wrap(
        char *buffer,
        const std::uint64_t offset,
        const std::uint64_t actingVersion,
        const std::uint64_t bufferLength)
    {
        return *this = SettlPriceType(buffer, offset, bufferLength, actingVersion);
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t encodedLength() SBE_NOEXCEPT
    {
        return 1;
    }

    SBE_NODISCARD std::uint64_t offset() const SBE_NOEXCEPT
    {
        return m_offset;
    }

    SBE_NODISCARD const char *buffer() const SBE_NOEXCEPT
    {
        return m_buffer;
    }

    SBE_NODISCARD char *buffer() SBE_NOEXCEPT
    {
        return m_buffer;
    }

    SBE_NODISCARD std::uint64_t bufferLength() const SBE_NOEXCEPT
    {
        return m_bufferLength;
    }

    SBE_NODISCARD std::uint64_t actingVersion() const SBE_NOEXCEPT
    {
        return m_actingVersion;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint16_t sbeSchemaId() SBE_NOEXCEPT
    {
        return static_cast<std::uint16_t>(1);
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint16_t sbeSchemaVersion() SBE_NOEXCEPT
    {
        return static_cast<std::uint16_t>(9);
    }

    SettlPriceType &clear()
    {
        std::uint8_t zero = 0;
        std::memcpy(m_buffer + m_offset, &zero, sizeof(std::uint8_t));
        return *this;
    }

    SBE_NODISCARD bool isEmpty() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return 0 == val;
    }

    SBE_NODISCARD std::uint8_t rawValue() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return val;
    }

    SettlPriceType &rawValue(std::uint8_t value)
    {
        std::memcpy(m_buffer + m_offset, &value, sizeof(std::uint8_t));
        return *this;
    }

    static bool finalDaily(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 0u)) != 0;
    }

    static std::uint8_t finalDaily(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 0u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 0u));
    }

    SBE_NODISCARD bool finalDaily() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 0u)) != 0;
    }

    SettlPriceType &finalDaily(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 0u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 0u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool actual(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 1u)) != 0;
    }

    static std::uint8_t actual(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 1u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 1u));
    }

    SBE_NODISCARD bool actual() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 1u)) != 0;
    }

    SettlPriceType &actual(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 1u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 1u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool rounded(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 2u)) != 0;
    }

    static std::uint8_t rounded(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 2u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 2u));
    }

    SBE_NODISCARD bool rounded() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 2u)) != 0;
    }

    SettlPriceType &rounded(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 2u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 2u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool intraday(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 3u)) != 0;
    }

    static std::uint8_t intraday(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 3u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 3u));
    }

    SBE_NODISCARD bool intraday() const
    {
        if (m_actingVersion < 4)
        {
            return false;
        }

        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 3u)) != 0;
    }

    SettlPriceType &intraday(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 3u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 3u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool reservedBits(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 4u)) != 0;
    }

    static std::uint8_t reservedBits(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 4u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 4u));
    }

    SBE_NODISCARD bool reservedBits() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 4u)) != 0;
    }

    SettlPriceType &reservedBits(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 4u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 4u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool nullValue(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 7u)) != 0;
    }

    static std::uint8_t nullValue(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 7u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 7u));
    }

    SBE_NODISCARD bool nullValue() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 7u)) != 0;
    }

    SettlPriceType &nullValue(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 7u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 7u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &builder, SettlPriceType writer)
    {
        builder << '[';
        bool atLeastOne = false;
        if (writer.finalDaily())
        {
            builder << R"("finalDaily")";
            atLeastOne = true;
        }
        if (writer.actual())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("actual")";
            atLeastOne = true;
        }
        if (writer.rounded())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("rounded")";
            atLeastOne = true;
        }
        if (writer.intraday())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("intraday")";
            atLeastOne = true;
        }
        if (writer.reservedBits())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("reservedBits")";
            atLeastOne = true;
        }
        if (writer.nullValue())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("nullValue")";
        }
        builder << ']';
        return builder;
    }
};
}
#endif
