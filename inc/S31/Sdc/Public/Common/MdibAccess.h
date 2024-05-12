#pragma once

#include <S31/Sdc/Public/Common/Mdib.h>
#include <S31/Sdc/Public/Common/MdibAccessSmartPtrTypes.h>

#include <Framework/Mdib/Public/MdibAccess.h>

namespace S31::Sdc
{

/**
 * @brief Reflects a decorated \ref DFL::Mdib::MdibAccess that supports transport specific SDC functionality.
 * @ingroup S31SdcCommon
 */
class MdibAccess : public virtual DFL::Mdib::MdibAccess
{
    public:
        /**
         * @brief Returns the SDC specific \ref S31::Sdc::Mdib to access transport specific SDC functionality.
         */
        virtual DFL::NotNull<MdibSharedPtr> latestSdcMdib() const = 0;
};

}
