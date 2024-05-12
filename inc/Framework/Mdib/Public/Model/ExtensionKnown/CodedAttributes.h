#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/CodedStringAttribute.h>

namespace DFL
{
namespace Mdib
{
namespace Ext
{

/**
 * @brief Container of different CodedAttribute extension types.
 * @details For use with the different CodedAttribute types described in the SDPi BICEPS extension.
 *
 * TODO: Currently only \ref DFL::Mdib::Ext::CodedStringAttribute is implemented. This container should also hold sequences of
 * CodedIntegerAttribute and CodedDecimalAttribute as well.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP CodedAttributes
{
    public:
        /**
         * @brief Constructor for collection of CodedAttribute types.
         * @param stringAttributes List of CodedAttributes which contain a string value. Default to empty.
         */
        CodedAttributes(const CodedStringAttributes& stringAttributes = {});

        /**
         * @brief Returns all CodedAttributes with string data type
         */
        const CodedStringAttributes& stringAttributes() const;

    private:
        CodedStringAttributes m_stringAttributes;
};

}
}
}
