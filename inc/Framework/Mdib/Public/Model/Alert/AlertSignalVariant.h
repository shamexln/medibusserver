#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalStateBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>

#include <variant>

namespace DFL::Mdib
{
class AlertSignalVariant;

/**
 * @brief Types handle for \ref AlertSignalVariant.
 * @ingroup Mdib
 */
using AlertSignalVariantHandle = BasicHandle<AlertSignalVariant>;

/**
 * @brief Variant type to contain \ref DFL::Mdib::MdsAlertSignal
 * "MdsAlertSignal" or \ref DFL::Mdib::VmdAlertSignal "VmdAlertSignal" data.
 *
 * @details
 * VmdAlertCondition might have signal in the MdsAlertSystem as well as in the
 * VmdAlertSystem. Thus, the is no specific signal type to provide when
 * searching for alert signals belonging to a VMD alert condition.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP AlertSignalVariant
    : public Impl::MdibEntity<AlertSignalVariant,
                              AlertSignalDescriptorBuilder,
                              AlertSignalStateBuilder,
                              MdsAlertSystem>
{
public:
    /**
     * @brief Variant type internally hold.
     */
    enum class VariantType
    {
        None,
        Mds,
        Vmd
    };

    /**
     * @brief Shared std:variant type.
     */
    using SharedVariant =
        std::variant<DFL_MDIB_SHARED_PTR<DFL::Mdib::MdsAlertSignal>,
                     DFL_MDIB_SHARED_PTR<DFL::Mdib::VmdAlertSignal>>;

    /**
     * @brief [Internal] Constructor required to create invalid entities.
     * @details
     * This ctor is required to satisfy the template implementation for the
     * iteration over entities.
     */
    AlertSignalVariant(
        const BasicHandle<AlertSignalVariant>& handle,
        const NotNull<AlertSignalDescriptorSharedPtr>& descriptor,
        VersionCounter descriptorVersion,
        const NotNull<AlertSignalStateSharedPtr>& state,
        VersionCounter stateVersion,
        const Handle& parent,
        VariantType = VariantType::None);

    /**
     * @brief Constructor using a \ref DFL::Mdib::MdsAlertSignal
     * "MdsAlertSignal" variant input.
     */
    explicit AlertSignalVariant(
        const NotNull<DFL_MDIB_SHARED_PTR<MdsAlertSignal>>& signal);

    /**
     * @brief Constructor using a \ref DFL::Mdib::VmdAlertSignal
     * "VmdAlertSignal" variant input.
     */
    explicit AlertSignalVariant(
        const NotNull<DFL_MDIB_SHARED_PTR<VmdAlertSignal>>& signal);

    /**
     * @brief Provide type information.
     */
    [[nodiscard]] VariantType type() const noexcept;

    /**
     * @brief Conversion to \c std::variant of shared pointers.
     */
    [[nodiscard]] SharedVariant sharedVariant() const;

    /**
     * @brief Implicit conversion to \c std::variant of shared pointers.
     */
    /* implicit */ operator SharedVariant() const;

private:
    const VariantType m_type;
};

}
