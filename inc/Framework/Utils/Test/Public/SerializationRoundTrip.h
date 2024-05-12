#pragma once

#include <Framework/Utils/Test/Public/SerializationRoundTripImpl.h>
#include <string>

namespace DFL
{
namespace Utils
{
namespace Test
{
namespace SerializationRoundTrip
{
/**
 * @brief Serializes the passed object and de-serializes it back.
 * @details There is a different between classes with and without default constructor.
 * Thus two type of de-serialization are tested:
 * - reading into an existing instance and
 * - reading into a new created instance (e.g., required for container usage).
 * @param outRef Object to serialize to.
 * @param inRef Object to serialize and de-serialize.
 *
 * @ingroup Utils
 */
template<class S>
void convertAndAssert(S& outRef, const S& inRef);
/**
 * @brief Serializes the passed object and de-serializes it back with custom equal comparator.
 * @details There is a different between classes with and without default constructor.
 * Thus two type of de-serialization are tested:
 * - reading into an existing instance and
 * - reading into a new created instance (e.g., required for container usage).
 * @param outRef Object to serialize to.
 * @param inRef Object to serialize and de-serialize.
 * @param comp Equal comparator required to test equality for types that do not have an operator==().
 *
 * @ingroup Utils
 */
template<class S, class EqComp>
void convertAndAssert(S& outRef, const S& inRef, EqComp comp);
template<class S, class EqComp>
void convertAndAssertImmutable(const S& inRef, EqComp comp);
template<class S, class EqComp>
void convertAndAssertNotDefaultConstructable(S& outRef, const S& inRef, EqComp comp);
template<class S>
void convertAndAssertNotDefaultConstructable(S& outRef, const S& inRef);
/**
 * @brief Helper to test old serialized versions.
 * @param xmlArchiveString XML string containing an (old) version of the archive.
 * @param outRef Output instance that would be filled with archive data
 */
template<class S>
void fromXmlArchiveString(const std::string& xmlArchiveString, S& outRef);

template<class S>
inline void convertAndAssert(S& outRef, const S& inRef)
{
    convertAndAssert(outRef, inRef, [](const S& a, const S& b) { return a == b; });
}

template<class S, class EqComp>
inline void convertAndAssert(S& outRef, const S& inRef, EqComp comp)
{
    Impl::convertAndAssert(outRef, inRef, comp);
}

template<class S, class EqComp>
inline void convertAndAssertImmutable(const S& inRef, EqComp comp)
{
    Impl::convertAndAssertImmutable(inRef, comp);
}

template<class S, class EqComp>
inline void convertAndAssertNotDefaultConstructable(S& outRef, const S& inRef, EqComp comp)
{
    Impl::convertAndAssertNotDefaultConstructable(outRef, inRef, comp);
}

template<class S>
inline void convertAndAssertNotDefaultConstructable(S& outRef, const S& inRef)
{
    Impl::convertAndAssertNotDefaultConstructable(outRef, inRef, [](const S& a, const S& b) { return a == b; });
}
template<class S>
inline void fromXmlArchiveString(const std::string& xmlArchiveString, S& outRef)
{
    Impl::fromXmlArchiveString(xmlArchiveString, outRef);
}
}
}
}
}
