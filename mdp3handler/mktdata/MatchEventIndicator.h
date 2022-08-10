/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_MATCHEVENTINDICATOR_H_
#define _MKTDATA_MATCHEVENTINDICATOR_H_

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

class MatchEventIndicator
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

    MatchEventIndicator() = default;

    MatchEventIndicator(
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

    MatchEventIndicator(
        char *buffer,
        const std::uint64_t bufferLength,
        const std::uint64_t actingVersion) :
        MatchEventIndicator(buffer, 0, bufferLength, actingVersion)
    {
    }

    MatchEventIndicator(
        char *buffer,
        const std::uint64_t bufferLength) :
        MatchEventIndicator(buffer, 0, bufferLength, sbeSchemaVersion())
    {
    }

    MatchEventIndicator &wrap(
        char *buffer,
        const std::uint64_t offset,
        const std::uint64_t actingVersion,
        const std::uint64_t bufferLength)
    {
        return *this = MatchEventIndicator(buffer, offset, bufferLength, actingVersion);
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

    MatchEventIndicator &clear()
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

    MatchEventIndicator &rawValue(std::uint8_t value)
    {
        std::memcpy(m_buffer + m_offset, &value, sizeof(std::uint8_t));
        return *this;
    }

    static bool lastTradeMsg(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 0u)) != 0;
    }

    static std::uint8_t lastTradeMsg(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 0u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 0u));
    }

    SBE_NODISCARD bool lastTradeMsg() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 0u)) != 0;
    }

    MatchEventIndicator &lastTradeMsg(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 0u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 0u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool lastVolumeMsg(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 1u)) != 0;
    }

    static std::uint8_t lastVolumeMsg(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 1u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 1u));
    }

    SBE_NODISCARD bool lastVolumeMsg() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 1u)) != 0;
    }

    MatchEventIndicator &lastVolumeMsg(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 1u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 1u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool lastQuoteMsg(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 2u)) != 0;
    }

    static std::uint8_t lastQuoteMsg(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 2u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 2u));
    }

    SBE_NODISCARD bool lastQuoteMsg() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 2u)) != 0;
    }

    MatchEventIndicator &lastQuoteMsg(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 2u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 2u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool lastStatsMsg(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 3u)) != 0;
    }

    static std::uint8_t lastStatsMsg(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 3u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 3u));
    }

    SBE_NODISCARD bool lastStatsMsg() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 3u)) != 0;
    }

    MatchEventIndicator &lastStatsMsg(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 3u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 3u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool lastImpliedMsg(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 4u)) != 0;
    }

    static std::uint8_t lastImpliedMsg(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 4u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 4u));
    }

    SBE_NODISCARD bool lastImpliedMsg() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 4u)) != 0;
    }

    MatchEventIndicator &lastImpliedMsg(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 4u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 4u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool recoveryMsg(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 5u)) != 0;
    }

    static std::uint8_t recoveryMsg(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 5u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 5u));
    }

    SBE_NODISCARD bool recoveryMsg() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 5u)) != 0;
    }

    MatchEventIndicator &recoveryMsg(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 5u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 5u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool reserved(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 6u)) != 0;
    }

    static std::uint8_t reserved(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 6u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 6u));
    }

    SBE_NODISCARD bool reserved() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 6u)) != 0;
    }

    MatchEventIndicator &reserved(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 6u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 6u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    static bool endOfEvent(const std::uint8_t bits)
    {
        return (bits & (static_cast<std::uint8_t>(1) << 7u)) != 0;
    }

    static std::uint8_t endOfEvent(const std::uint8_t bits, const bool value)
    {
        return value ? static_cast<std::uint8_t>(bits | (static_cast<std::uint8_t>(1) << 7u)) : static_cast<std::uint8_t>(bits & ~(static_cast<std::uint8_t>(1) << 7u));
    }

    SBE_NODISCARD bool endOfEvent() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint8_t));
        return ((val) & (static_cast<std::uint8_t>(1) << 7u)) != 0;
    }

    MatchEventIndicator &endOfEvent(const bool value)
    {
        std::uint8_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint8_t));
        bits = (value ? static_cast<std::uint8_t>((bits) | (static_cast<std::uint8_t>(1) << 7u)) : static_cast<std::uint8_t>((bits) & ~(static_cast<std::uint8_t>(1) << 7u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint8_t));
        return *this;
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &builder, MatchEventIndicator writer)
    {
        builder << '[';
        bool atLeastOne = false;
        if (writer.lastTradeMsg())
        {
            builder << R"("lastTradeMsg")";
            atLeastOne = true;
        }
        if (writer.lastVolumeMsg())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("lastVolumeMsg")";
            atLeastOne = true;
        }
        if (writer.lastQuoteMsg())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("lastQuoteMsg")";
            atLeastOne = true;
        }
        if (writer.lastStatsMsg())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("lastStatsMsg")";
            atLeastOne = true;
        }
        if (writer.lastImpliedMsg())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("lastImpliedMsg")";
            atLeastOne = true;
        }
        if (writer.recoveryMsg())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("recoveryMsg")";
            atLeastOne = true;
        }
        if (writer.reserved())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("reserved")";
            atLeastOne = true;
        }
        if (writer.endOfEvent())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("endOfEvent")";
        }
        builder << ']';
        return builder;
    }
};
}
#endif
