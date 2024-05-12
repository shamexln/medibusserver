#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Mdib/Public/MdibObserver.h>

#include <memory>
#include <string>

/// Things from here shall not end up in production code.
namespace S31::Sdc::Experimental
{

/**
 * @brief Stores all Mdib changes as (boost serialized) reports in the given directory.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP MdibChangesSerializeStorer
{
    public:
        /// @brief Constructor
        MdibChangesSerializeStorer(std::string path, DFL::Mdib::MdibAccess& mdibAccess);

    private:
        DFL::NotNull<std::shared_ptr<DFL::Mdib::MdibObserver>> m_mdibObserver;
};

}
