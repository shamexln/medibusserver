#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Config/Public/Attributes.h>
#include <Framework/Mdib/Public/Roles.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Constraints configuration for an MDIB.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP MdibConstraints
{
    public:
        /**
         * @brief Specify the roles the MDIB supports.
         */
        explicit MdibConstraints(Roles roles);

        /**
         * @brief Factory function to create with all constraints / consistency checks.
         * @attention Use this only for tests. For production environments use the ctor with
         * explicitly given roles.
         */
        static MdibConstraints allConstraints();

        /**
         * @brief Factory function to create without any constraints / consistency checks.
         * @details Calls internally @ref deactivateConsistencyChecks().
         * @attention Use this only for tests. For production environments use the ctor with
         * explicitly given roles.
         */
        static MdibConstraints noConstraints();

        /**
         * @brief Deactivate consistency checks to allow writing invalid data.
         * @details Typical use case: Use this call while adapting your code to a new or
         * changed %Mdib checker.
         * @attention Not for production environments.
         */
        void deactivateConsistencyChecks();

        /**
         * @brief Returns \c true in case the consistency shall be preserved (i.e.
         * if @ref deactivateConsistencyChecks() was not called before).
         */
        [[nodiscard]] bool consistencyChecks() const;

        /**
         * @brief Returns \c true in case MDIB consistency for Metric Provider shall be guaranteed.
         */
        [[nodiscard]] bool metricProvider() const;

        /**
         * @brief Returns \c true in case MDIB consistency for Alert Provider shall be guaranteed.
         */
        [[nodiscard]] bool alertProvider() const;

        /**
         * @brief Returns \c true in case MDIB consistency for Operation Provider shall be guaranteed.
         */
        [[nodiscard]] bool operationProvider() const;

        /**
         * @brief Returns \c true in case MDIB consistency for Localizing Provider shall be guaranteed.
         */
        [[nodiscard]] bool localizingProvider() const;

    private:
        Roles m_roles;
        bool m_checkConsistency = true;
};

}
}
