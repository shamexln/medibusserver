#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/OperatingMode.h>
#include <Framework/Mdib/Private/HasExtensions.h>

#include <utility>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines groups of operations in order to allow clinical grouping and prioritization of operations.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP OperationGroup: public Impl::HasExtensions
{
    public:
        /**
         * @brief Constructor.
         */
        OperationGroup(OperatingMode operatingMode,
                       Handles operations,
                       const CodedValue& type,
                       ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Defines the operating mode of the whole operation group.
         * @details See \ref OperatingMode.
         */
        OperatingMode operatingMode() const;

        /**
         * @brief Handle references to all operations enclosed by the operation group.
         */
        const Handles& operations() const;

        /**
         * @brief Semantically describes the operation group.
         */
        const CodedValue& type() const;

    private:
        OperatingMode m_operatingMode;
        Handles m_operations;
        CodedValue m_type;
};

/**
 * @brief A sequence of \ref OperationGroup objects.
 * @ingroup Mdib
 */
using OperationGroups = std::vector<OperationGroup>;

/**
 * @brief Comparison operator for \ref OperationGroup.
 * @ingroup Mdib
 */
bool operator==(const OperationGroup &lhs, const OperationGroup &rhs);

/**
 * @brief Comparison operator for \ref OperationGroup.
 * @ingroup Mdib
 */
bool operator!=(const OperationGroup &lhs, const OperationGroup &rhs);

inline OperationGroup::OperationGroup(OperatingMode operatingMode,
                               Handles operations,
                               const CodedValue& type, // NOLINT(modernize-pass-by-value)
                               ExtensionTypes extensions):
            Impl::HasExtensions(std::move(extensions)),
            m_operatingMode(operatingMode),
            m_operations(std::move(operations)),
            m_type(type)
{
}

inline OperatingMode OperationGroup::operatingMode() const
{
    return m_operatingMode;
}

inline const Handles& OperationGroup::operations() const
{
    return m_operations;
}

inline const CodedValue& OperationGroup::type() const
{
    return m_type;
}

inline bool operator==(const OperationGroup &lhs, const OperationGroup &rhs)
{
    if (&lhs == &rhs)
    {
        return true;
    }
    return lhs.operatingMode() == rhs.operatingMode()
            && lhs.operations() == rhs.operations()
            && lhs.type() == rhs.type()
            && lhs.extensions() == rhs.extensions();
}

inline bool operator!=(const OperationGroup &lhs, const OperationGroup &rhs)
{
    return !(lhs == rhs);
}

} /* namespace Mdib */
} /* namespace DFL */
