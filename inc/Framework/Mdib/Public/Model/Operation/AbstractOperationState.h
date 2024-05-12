#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/Operation/OperatingMode.h>
#include <Framework/Mdib/Private/HasExtensions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief State of an operation that is exposed on the \ref Sco.
 * @ingroup Mdib
 */
class AbstractOperationState: public Impl::HasExtensions
{
    DFL_MDIB_IMMUTABLE(AbstractOperationState)

    public:
        /**
         * @brief Operating mode that defines if the operation is accessible.
         * @details See \ref OperatingMode.
         */
        OperatingMode operatingMode() const;

    protected:
        /**
         * @brief Constructor that defaults \ref AbstractOperationState::operatingMode() "Operation mode"
         * to \ref OperatingMode::NotAvailable "not available".
         */
        AbstractOperationState() = default;

        /**
         * @brief Full constructor.
         */
        AbstractOperationState(OperatingMode operatingMode,
                               ExtensionTypes&& extensions);

    private:
        OperatingMode m_operatingMode{OperatingMode::NotAvailable};
};

inline AbstractOperationState::AbstractOperationState(OperatingMode operatingMode,
                                                      ExtensionTypes&& extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_operatingMode(operatingMode)
{
}

inline OperatingMode AbstractOperationState::operatingMode() const
{
    return m_operatingMode;
}

} /* namespace Mdib */
} /* namespace DFL */
