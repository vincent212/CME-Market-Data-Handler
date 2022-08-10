/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _MKTDATA_INSTATTRIBVALUE_H_
#define _MKTDATA_INSTATTRIBVALUE_H_

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

class InstAttribValue
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

    InstAttribValue() = default;

    InstAttribValue(
        char *buffer,
        const std::uint64_t offset,
        const std::uint64_t bufferLength,
        const std::uint64_t actingVersion) :
        m_buffer(buffer),
        m_bufferLength(bufferLength),
        m_offset(offset),
        m_actingVersion(actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((m_offset + 4) > m_bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }
    }

    InstAttribValue(
        char *buffer,
        const std::uint64_t bufferLength,
        const std::uint64_t actingVersion) :
        InstAttribValue(buffer, 0, bufferLength, actingVersion)
    {
    }

    InstAttribValue(
        char *buffer,
        const std::uint64_t bufferLength) :
        InstAttribValue(buffer, 0, bufferLength, sbeSchemaVersion())
    {
    }

    InstAttribValue &wrap(
        char *buffer,
        const std::uint64_t offset,
        const std::uint64_t actingVersion,
        const std::uint64_t bufferLength)
    {
        return *this = InstAttribValue(buffer, offset, bufferLength, actingVersion);
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t encodedLength() SBE_NOEXCEPT
    {
        return 4;
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

    InstAttribValue &clear()
    {
        std::uint32_t zero = 0;
        std::memcpy(m_buffer + m_offset, &zero, sizeof(std::uint32_t));
        return *this;
    }

    SBE_NODISCARD bool isEmpty() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return 0 == val;
    }

    SBE_NODISCARD std::uint32_t rawValue() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return val;
    }

    InstAttribValue &rawValue(std::uint32_t value)
    {
        std::memcpy(m_buffer + m_offset, &value, sizeof(std::uint32_t));
        return *this;
    }

    static bool electronicMatchEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 0u)) != 0;
    }

    static std::uint32_t electronicMatchEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 0u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 0u));
    }

    SBE_NODISCARD bool electronicMatchEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 0u)) != 0;
    }

    InstAttribValue &electronicMatchEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 0u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 0u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool orderCrossEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 1u)) != 0;
    }

    static std::uint32_t orderCrossEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 1u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 1u));
    }

    SBE_NODISCARD bool orderCrossEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 1u)) != 0;
    }

    InstAttribValue &orderCrossEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 1u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 1u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool blockTradeEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 2u)) != 0;
    }

    static std::uint32_t blockTradeEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 2u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 2u));
    }

    SBE_NODISCARD bool blockTradeEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 2u)) != 0;
    }

    InstAttribValue &blockTradeEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 2u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 2u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool eFPEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 3u)) != 0;
    }

    static std::uint32_t eFPEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 3u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 3u));
    }

    SBE_NODISCARD bool eFPEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 3u)) != 0;
    }

    InstAttribValue &eFPEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 3u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 3u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool eBFEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 4u)) != 0;
    }

    static std::uint32_t eBFEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 4u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 4u));
    }

    SBE_NODISCARD bool eBFEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 4u)) != 0;
    }

    InstAttribValue &eBFEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 4u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 4u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool eFSEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 5u)) != 0;
    }

    static std::uint32_t eFSEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 5u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 5u));
    }

    SBE_NODISCARD bool eFSEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 5u)) != 0;
    }

    InstAttribValue &eFSEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 5u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 5u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool eFREligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 6u)) != 0;
    }

    static std::uint32_t eFREligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 6u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 6u));
    }

    SBE_NODISCARD bool eFREligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 6u)) != 0;
    }

    InstAttribValue &eFREligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 6u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 6u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool oTCEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 7u)) != 0;
    }

    static std::uint32_t oTCEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 7u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 7u));
    }

    SBE_NODISCARD bool oTCEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 7u)) != 0;
    }

    InstAttribValue &oTCEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 7u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 7u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool iLinkIndicativeMassQuotingEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 8u)) != 0;
    }

    static std::uint32_t iLinkIndicativeMassQuotingEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 8u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 8u));
    }

    SBE_NODISCARD bool iLinkIndicativeMassQuotingEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 8u)) != 0;
    }

    InstAttribValue &iLinkIndicativeMassQuotingEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 8u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 8u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool negativeStrikeEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 9u)) != 0;
    }

    static std::uint32_t negativeStrikeEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 9u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 9u));
    }

    SBE_NODISCARD bool negativeStrikeEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 9u)) != 0;
    }

    InstAttribValue &negativeStrikeEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 9u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 9u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool negativePriceOutrightEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 10u)) != 0;
    }

    static std::uint32_t negativePriceOutrightEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 10u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 10u));
    }

    SBE_NODISCARD bool negativePriceOutrightEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 10u)) != 0;
    }

    InstAttribValue &negativePriceOutrightEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 10u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 10u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool isFractional(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 11u)) != 0;
    }

    static std::uint32_t isFractional(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 11u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 11u));
    }

    SBE_NODISCARD bool isFractional() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 11u)) != 0;
    }

    InstAttribValue &isFractional(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 11u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 11u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool volatilityQuotedOption(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 12u)) != 0;
    }

    static std::uint32_t volatilityQuotedOption(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 12u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 12u));
    }

    SBE_NODISCARD bool volatilityQuotedOption() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 12u)) != 0;
    }

    InstAttribValue &volatilityQuotedOption(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 12u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 12u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool rFQCrossEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 13u)) != 0;
    }

    static std::uint32_t rFQCrossEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 13u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 13u));
    }

    SBE_NODISCARD bool rFQCrossEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 13u)) != 0;
    }

    InstAttribValue &rFQCrossEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 13u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 13u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool zeroPriceOutrightEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 14u)) != 0;
    }

    static std::uint32_t zeroPriceOutrightEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 14u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 14u));
    }

    SBE_NODISCARD bool zeroPriceOutrightEligible() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 14u)) != 0;
    }

    InstAttribValue &zeroPriceOutrightEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 14u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 14u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool decayingProductEligibility(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 15u)) != 0;
    }

    static std::uint32_t decayingProductEligibility(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 15u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 15u));
    }

    SBE_NODISCARD bool decayingProductEligibility() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 15u)) != 0;
    }

    InstAttribValue &decayingProductEligibility(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 15u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 15u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool variableProductEligibility(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 16u)) != 0;
    }

    static std::uint32_t variableProductEligibility(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 16u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 16u));
    }

    SBE_NODISCARD bool variableProductEligibility() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 16u)) != 0;
    }

    InstAttribValue &variableProductEligibility(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 16u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 16u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool dailyProductEligibility(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 17u)) != 0;
    }

    static std::uint32_t dailyProductEligibility(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 17u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 17u));
    }

    SBE_NODISCARD bool dailyProductEligibility() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 17u)) != 0;
    }

    InstAttribValue &dailyProductEligibility(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 17u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 17u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool gTOrdersEligibility(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 18u)) != 0;
    }

    static std::uint32_t gTOrdersEligibility(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 18u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 18u));
    }

    SBE_NODISCARD bool gTOrdersEligibility() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 18u)) != 0;
    }

    InstAttribValue &gTOrdersEligibility(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 18u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 18u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool impliedMatchingEligibility(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 19u)) != 0;
    }

    static std::uint32_t impliedMatchingEligibility(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 19u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 19u));
    }

    SBE_NODISCARD bool impliedMatchingEligibility() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 19u)) != 0;
    }

    InstAttribValue &impliedMatchingEligibility(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 19u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 19u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool triangulationEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 20u)) != 0;
    }

    static std::uint32_t triangulationEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 20u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 20u));
    }

    SBE_NODISCARD bool triangulationEligible() const
    {
        if (m_actingVersion < 9)
        {
            return false;
        }

        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 20u)) != 0;
    }

    InstAttribValue &triangulationEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 20u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 20u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    static bool variableCabEligible(const std::uint32_t bits)
    {
        return (bits & (UINT32_C(0x1) << 21u)) != 0;
    }

    static std::uint32_t variableCabEligible(const std::uint32_t bits, const bool value)
    {
        return value ? static_cast<std::uint32_t>(bits | (UINT32_C(0x1) << 21u)) : static_cast<std::uint32_t>(bits & ~(UINT32_C(0x1) << 21u));
    }

    SBE_NODISCARD bool variableCabEligible() const
    {
        if (m_actingVersion < 9)
        {
            return false;
        }

        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
        return (SBE_LITTLE_ENDIAN_ENCODE_32(val) & (UINT32_C(0x1) << 21u)) != 0;
    }

    InstAttribValue &variableCabEligible(const bool value)
    {
        std::uint32_t bits;
        std::memcpy(&bits, m_buffer + m_offset, sizeof(std::uint32_t));
        bits = SBE_LITTLE_ENDIAN_ENCODE_32(value ? static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) | (UINT32_C(0x1) << 21u)) : static_cast<std::uint32_t>(SBE_LITTLE_ENDIAN_ENCODE_32(bits) & ~(UINT32_C(0x1) << 21u)));
        std::memcpy(m_buffer + m_offset, &bits, sizeof(std::uint32_t));
        return *this;
    }

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator << (
        std::basic_ostream<CharT, Traits> &builder, InstAttribValue writer)
    {
        builder << '[';
        bool atLeastOne = false;
        if (writer.electronicMatchEligible())
        {
            builder << R"("electronicMatchEligible")";
            atLeastOne = true;
        }
        if (writer.orderCrossEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("orderCrossEligible")";
            atLeastOne = true;
        }
        if (writer.blockTradeEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("blockTradeEligible")";
            atLeastOne = true;
        }
        if (writer.eFPEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("eFPEligible")";
            atLeastOne = true;
        }
        if (writer.eBFEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("eBFEligible")";
            atLeastOne = true;
        }
        if (writer.eFSEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("eFSEligible")";
            atLeastOne = true;
        }
        if (writer.eFREligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("eFREligible")";
            atLeastOne = true;
        }
        if (writer.oTCEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("oTCEligible")";
            atLeastOne = true;
        }
        if (writer.iLinkIndicativeMassQuotingEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("iLinkIndicativeMassQuotingEligible")";
            atLeastOne = true;
        }
        if (writer.negativeStrikeEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("negativeStrikeEligible")";
            atLeastOne = true;
        }
        if (writer.negativePriceOutrightEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("negativePriceOutrightEligible")";
            atLeastOne = true;
        }
        if (writer.isFractional())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("isFractional")";
            atLeastOne = true;
        }
        if (writer.volatilityQuotedOption())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("volatilityQuotedOption")";
            atLeastOne = true;
        }
        if (writer.rFQCrossEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("rFQCrossEligible")";
            atLeastOne = true;
        }
        if (writer.zeroPriceOutrightEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("zeroPriceOutrightEligible")";
            atLeastOne = true;
        }
        if (writer.decayingProductEligibility())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("decayingProductEligibility")";
            atLeastOne = true;
        }
        if (writer.variableProductEligibility())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("variableProductEligibility")";
            atLeastOne = true;
        }
        if (writer.dailyProductEligibility())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("dailyProductEligibility")";
            atLeastOne = true;
        }
        if (writer.gTOrdersEligibility())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("gTOrdersEligibility")";
            atLeastOne = true;
        }
        if (writer.impliedMatchingEligibility())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("impliedMatchingEligibility")";
            atLeastOne = true;
        }
        if (writer.triangulationEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("triangulationEligible")";
            atLeastOne = true;
        }
        if (writer.variableCabEligible())
        {
            if (atLeastOne)
            {
                builder << ",";
            }
            builder << R"("variableCabEligible")";
        }
        builder << ']';
        return builder;
    }
};
}
#endif
