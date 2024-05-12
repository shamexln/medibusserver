#pragma once

#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/XsdSimpleType.h>

#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @details Argument description for an \ref ActivateOperationDescriptor.
 * @ingroup Mdib
 */
class ActivateArgument
{
    public:
        /**
         * @brief Constructor with all members.
         */
        ActivateArgument(const CodedValue& name, XsdSimpleType dataType);

        /**
         * @brief CodedValue that describes this argument.
         */
        const CodedValue& name() const;

        /**
         * @brief XSD simple data type of the argument.
         */
        XsdSimpleType dataType() const;

    private:
        CodedValue m_name;
        XsdSimpleType m_dataType;
};

/**
 * @brief Sequence of \ref ActivateArgument.
 * @ingroup Mdib
 */
using ActivateArguments = std::vector<ActivateArgument>;

/**
 * @brief Comparator for \ref ActivateArgument.
 * @ingroup Mdib
 */
bool operator==(const ActivateArgument& lhs, const ActivateArgument& rhs);

/**
 * @brief Comparator for \ref ActivateArgument.
 * @ingroup Mdib
 */
bool operator!=(const ActivateArgument& lhs, const ActivateArgument& rhs);


inline ActivateArgument::ActivateArgument(const CodedValue& name, // NOLINT(modernize-pass-by-value)
                                          XsdSimpleType dataType):
        m_name(name),
        m_dataType(dataType)
{
}

inline const CodedValue& ActivateArgument::name() const
{
    return m_name;
}

inline XsdSimpleType ActivateArgument::dataType() const
{
    return m_dataType;
}

inline bool operator ==(const ActivateArgument& lhs, const ActivateArgument& rhs)
{
    return (lhs.name() == rhs.name()) && (lhs.dataType() == rhs.dataType());
}

inline bool operator !=(const ActivateArgument& lhs, const ActivateArgument& rhs)
{
    return !(lhs == rhs);
}

} /* namespace Mdib */
} /* namespace DFL */
