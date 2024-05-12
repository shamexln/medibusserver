#pragma once

#include <Framework/Utils/Public/ScopeExit.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace DFL
{
namespace Utils
{
namespace Test
{
namespace Impl
{

template<class S>
inline std::string toXmlArchiveString(const S& inRef)
{
    std::ostringstream stream;
    // save data to archive
    {
        // NOLINTNEXTLINE(misc-const-correctness)
        boost::archive::xml_oarchive oa(stream);
        // write class instance to archive
        oa << boost::serialization::make_nvp("Data", inRef);
        // archive and stream closed when destructors are called
    }
    return stream.str();
}

template<class S>
inline void fromXmlArchiveString(const std::string& xmlArchiveString, S& outRef)
{
    std::istringstream istream(xmlArchiveString);
    {
        // NOLINTNEXTLINE(misc-const-correctness)
        boost::archive::xml_iarchive ia(istream);
        // read class state from archive
        ia >> boost::serialization::make_nvp("Reference", outRef);
        // archive and stream closed when destructors are called
    }
}

template <class S>
inline void createAssertMessage(const std::string& xml,
                                const S& outExpected,
                                const S& inActual,
                                const std::string& sourceName)
{
    std::ostringstream msg;
    msg << sourceName << " round trip failed for " << typeid(inActual).name();
    msg << "\nInput data:\n" << inActual;
    msg << "\nOutput data:\n" << outExpected;
    msg << "\nSerialized XML data:\n" << xml;
    msg << "\n";
    throw std::runtime_error(msg.str().c_str());
}

template <class S, class EqComp>
inline void checkRawPointer(const S& inRef, EqComp comp)
{
    const auto xml = toXmlArchiveString(&inRef);
    S* out = nullptr;
    ScopeExit const cleanup{[&]() {
        delete out;
        out = nullptr;
    }};

    fromXmlArchiveString(xml, out);

    if (!out)
    {
        throw std::runtime_error(
            "checkRawPointer() round trip failed, nullptr");
    }
    if (!comp(*out, inRef))
    {
        createAssertMessage(xml, *out, inRef, "checkRawPointer");
    }
}

template<class S, class EqComp>
inline void checkInPlace(S& outRef, const S& inRef, EqComp comp)
{
    const std::string xml = toXmlArchiveString(inRef);
    fromXmlArchiveString(xml, outRef);

    if (!comp(outRef, inRef))
    {
        createAssertMessage(xml, outRef, inRef, "checkInPlace");
    }
}

template <class S, class EqComp>
inline void checkVector(const S& inRef, EqComp comp)
{
    std::vector<S> in{inRef};
    std::vector<S> out{};

    const auto xml = toXmlArchiveString(in);
    fromXmlArchiveString(xml, out);

    if (out.empty())
    {
        throw std::runtime_error(
            "checkVector() round trip failed, vector empty");
    }
    if (!comp(out.front(), in.front()))
    {
        createAssertMessage(xml, out.front(), in.front(), "checkVector");
    }
}

template <class S, class EqComp>
inline void checkOptional(const S& inRef, EqComp comp)
{
    // boost::optional only works with
    // - mutable
    // - default constructible
    boost::optional<S> in{inRef};
    boost::optional<S> out{};

    const std::string xml = toXmlArchiveString(in);
    fromXmlArchiveString(xml, out);

    if (!out)
    {
        throw std::runtime_error(
            "checkOptional() round trip failed, optional empty");
    }
    if (!comp(*out, *in))
    {
        createAssertMessage(xml, *out, *in, "checkOptional");
    }
}

template<class S, class EqComp>
inline void convertAndAssertImmutable(const S& inRef, EqComp comp)
{
    checkRawPointer(inRef, comp);
    // checkInplace does not work for immutable, since the destination cannot be replaced
    // checkVector uses default ctor and thus does not work
    // checkOptional boost::optional requires assignment operator
}

template<class S, class EqComp>
inline void convertAndAssertNotDefaultConstructable(S& outRef, const S& inRef, EqComp comp)
{
    checkRawPointer(inRef, comp);
    checkInPlace(outRef, inRef, comp);
    checkVector(inRef, comp);
    // checkOptional is forbidden by boost::serialization for not default constructible types
}

template<class S, class EqComp>
inline void convertAndAssert(S& outRef, const S& inRef, EqComp comp)
{
    checkRawPointer(inRef, comp);
    checkInPlace(outRef, inRef, comp);
    checkVector(inRef, comp);
    checkOptional(inRef, comp);
}

}
}
}
}
