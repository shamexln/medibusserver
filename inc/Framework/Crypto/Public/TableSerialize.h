#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Store/Table.h>
#include <Framework/Crypto/Public/Table.h>
#include <Framework/Crypto/Public/TableItem.h>

#include <Framework/Utils/Public/Application/Identifier.h>
#include <Framework/Utils/Public/Application/IdentifierSerialize.h>

#include <boost/optional/optional.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

#include <string>
#include <utility>
#include <vector>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Crypto::Table)

BOOST_CLASS_VERSION(::DFL::Crypto::Table, 1)

// https://www.boost.org/doc/libs/1_68_0/libs/serialization/doc/traits.html#tracking
// The default tracking type would be track_selectively.
// This leads to different archive output depending on customers.
// Here explicitly the tracking is disabled, to enforce a save/store in all
// cases. It is not assumed, that this type should be saved/stored only once
// when used with multiple pointers.
BOOST_CLASS_TRACKING(::DFL::Crypto::Table, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
/**
 * @brief Saves given table in given archive.
 *
 * @snippet Crypto/Test/UnitTest/TestTable.cpp serialize
 *
 * @ingroup Crypto
 */
template <class Archive>
void save(Archive& ar,
          const ::DFL::Crypto::Table& table,
          const unsigned int /*version*/)
{
    ar& boost::serialization::make_nvp("ApplicationIdentifier",
                                       table.applicationIdentifier());

    const std::vector<::DFL::Crypto::TableItem> tableItems{table.cbegin(),
                                                           table.cend()};
    ar& boost::serialization::make_nvp("TableItems", tableItems);
}
/**
 * @brief Loads given table from given archive.
 *
 * @snippet Crypto/Test/UnitTest/TestTable.cpp serialize
 *
 * @ingroup Crypto
 */
template <class Archive>
void load(Archive& ar, ::DFL::Crypto::Table& table, const unsigned int version)
{
    ::DFL::Application::Identifier id{};

    if (version == 0)
    {
        boost::optional<std::string> materialNumber{};
        ar& boost::serialization::make_nvp("MaterialNumber", materialNumber);

        boost::optional<std::string> serialNumber{};
        ar& boost::serialization::make_nvp("SerialNumber", serialNumber);

        id = ::DFL::Application::Identifier{
            ::DFL::Application::MaterialNumber{materialNumber ? *materialNumber
                                                              : ""},
            ::DFL::Application::SerialNumber{serialNumber ? *serialNumber : ""},
            ::DFL::Application::SoftwareVersionNumber{}};
    }
    else
    {
        ar& boost::serialization::make_nvp("ApplicationIdentifier", id);
    }

    std::vector<::DFL::Crypto::TableItem> tableItems{};
    ar& boost::serialization::make_nvp("TableItems", tableItems);

    auto newTable{::DFL::Crypto::Table{}};
    ::DFL::Crypto::Impl::TableAccess{&newTable}.applicationIdentifier(id);
    for (const auto& item : tableItems)
    {
        ::DFL::Crypto::Impl::TableAccess{&newTable}.insert(item);
    }
    table.swap(newTable);
}
}
}
