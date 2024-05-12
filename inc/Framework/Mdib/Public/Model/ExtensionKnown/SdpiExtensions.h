#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/ExtensionType.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{
namespace Ext
{

class CodedAttributes;
class CodedStringAttribute;

/**
 * @brief Helper functions for the SDPi extensions.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP SdpiExtensions
{
public:
    /**
     * @brief Converts known extension to MDIB extension type.
     * @details due to Requirements in the BICEPS model extension documentation, only parts of the sdpi:MdcAttribute will be mapped to the ExtensionType
     *
     *  R0001: An SDC SERVICE PROVIDER shall set sdpi:MdcAttribute/Code to any code from the first partition of the IEEE 11073-10101 nomenclature in the range of 67841 (1::2305) to 68609 (1::3073).
     *  R0002: An SDC SERVICE PROVIDER shall not add pm:Translation elements to sdpi:MdcAttribute elements.
     *  R0003: An SDC SERVICE PROVIDER shall not add pm:CodingSystemName elements to sdpi:MdcAttribute elements.
     *  R0004: An SDC SERVICE PROVIDER shall not add pm:ConceptDescription elements to sdpi:MdcAttribute elements.
     *  R0005: An SDC SERVICE PROVIDER shall not add ext:Extension elements to sdpi:MdcAttribute elements.
     *
     *  R0001 is enforced via Mdib checker.
     *
     *  Furthermore, coding system 11073-10101-2004 is the implied value and will thus not be mapped into the extension type if detected.
     */
    static ExtensionType toExtension(const CodedAttributes& codedAttribute);

    /**
     * @brief Gets requested known extension from generic type (if matches).
     * @details
     * In case the generic extension represents the known extension (passed as
     * template type), it is returned. Otherwise, \c boost::none will be
     * returned.
     */
    template <class ExtensionType_T>
    static boost::optional<ExtensionType_T> get(const ExtensionType& extension);

    /**
     * @brief Searches for the requested known extension in a sequence of
     * generic extension.
     * @details
     * In case exactly one of the generic extension match the requested known
     * extension, it will be returned. Otherwise \c boost::none is returned.
     */
    template <class ExtensionType_T>
    static boost::optional<ExtensionType_T> get(const ExtensionTypes& extensions);
};

}
}
}
