#pragma once

#include <S31/Nomenclature/Public/Validators.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifierSemantic.h>
#include <Framework/Utils/Public/EnumClass.h>

#include <boost/optional/optional.hpp>

#include <functional>
#include <memory>
#include <set>

namespace S31::Sdc
{

class S31_CORE_EXPIMP InstanceIdentifiersUtil
{
    public:

        /**
         * @brief Combine two lists of \ref DFL::Mdib::InstanceIdentifier using InstanceIdentifier::operator== for comparison.
         * @return A combined list of InstanceIdentifiers.
         * @ingroup S31SdcCommon
         */
        static DFL::Mdib::InstanceIdentifiers combine(const DFL::Mdib::InstanceIdentifiers& lhs, const DFL::Mdib::InstanceIdentifiers& rhs);

        /**
         * @brief Add a single \ref DFL::Mdib::InstanceIdentifier to a list of InstanceIdentifiers using InstanceIdentifier::operator== for comparison.
         * @return A combined list of InstanceIdentifiers.
         * @ingroup S31SdcCommon
         */
        static DFL::Mdib::InstanceIdentifiers combine(const DFL::Mdib::InstanceIdentifiers& listOfInstances, const DFL::Mdib::InstanceIdentifier& singleInstance);
};

}
