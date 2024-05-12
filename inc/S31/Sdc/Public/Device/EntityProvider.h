#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Component/Sco.h>
#include <Framework/Mdib/Public/Model/Component/SystemContext.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextIndicator.h>

namespace S31::Sdc
{
/**
 * @brief Convenience functions to provide specific handles of entities that are created on demand.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP EntityProvider
{
    public:

        /**
         * @brief Takes a mdibChangeSet and adds a system context on demand.
         * @return - Returns a valid handle of the system context that is either existing in the given MDIB or added to the change set.
         *         - Returns an invalid handle if there is no parent MDS
         */
        static DFL::Mdib::SystemContextHandle provideSystemContext(DFL::Mdib::MdibChangeSet& mdibChangeSet,
                                                                   const DFL::Mdib::Mdib& mdib,
                                                                   const DFL::Mdib::MdsHandle& parentHandle);

        /**
         * @brief Takes a mdibChangeSet and adds a system context and location context indicator on demand.
         * @return - Returns a valid handle of the location context indicator that is either existing in the given MDIB or added to the change set.
         *         - Returns an invalid handle if there is no parent MDS
         */
        static DFL::Mdib::PatientContextIndicatorHandle providePatientContextIndicator(DFL::Mdib::MdibChangeSet& mdibChangeSet,
                                                                                       const DFL::Mdib::Mdib& mdib,
                                                                                       const DFL::Mdib::MdsHandle& mdsHandle);

        static DFL::Mdib::LocationContextIndicatorHandle provideLocationContextIndicator(DFL::Mdib::MdibChangeSet& mdibChangeSet,
                                                                                         const DFL::Mdib::Mdib& mdib,
                                                                                         const DFL::Mdib::MdsHandle& mdsHandle);

        /**
         * @brief Takes a mdibChangeSet and adds a mds sco on demand.
         * @return - Returns a valid handle of the mds sco that is either existing in the given MDIB or added to the change set.
         *         - Returns an invalid handle if there is no parent MDS
         */
        static DFL::Mdib::MdsScoHandle provideMdsSco(DFL::Mdib::MdibChangeSet& mdibChangeSet,
                                                     const DFL::Mdib::Mdib& mdib,
                                                     const DFL::Mdib::MdsHandle& parentHandle);

        /**
         * @brief Takes a mdibChangeSet and adds an mds alert system on demand.
         * @return - Returns a valid handle of the mds alert system that is either existing in the given MDIB or added to the change set.
         *         - Returns an invalid handle if there is no parent MDS
         */
        static DFL::Mdib::MdsAlertSystemHandle provideMdsAlertSystem(DFL::Mdib::MdibChangeSet& mdibChangeSet,
                                                                     const DFL::Mdib::Mdib& mdib,
                                                                     const DFL::Mdib::MdsHandle& mdsHandle);


        /**
         * @return The system context handle for a given mds.
         */
        static DFL::Mdib::SystemContextHandle createSystemContextHandle(const DFL::Mdib::MdsHandle& mdsHandle);

        /**
         * @return The location context indicator handle for a given mds.
         */
        static DFL::Mdib::LocationContextIndicatorHandle createLocationContextIndicatorHandle(const DFL::Mdib::MdsHandle& mdsHandle);

        /**
         * @return The patient context indicator handle for a given mds.
         */
        static DFL::Mdib::PatientContextIndicatorHandle createPatientContextIndicatorHandle(const DFL::Mdib::MdsHandle& mdsHandle);

        /**
         * @return The mds sco handle for a given mds.
         */
        static DFL::Mdib::MdsScoHandle createMdsScoHandle(const DFL::Mdib::MdsHandle& mdsHandle);

        /**
         * @return The alert system handle for a given mds.
         */
        static DFL::Mdib::MdsAlertSystemHandle createMdsAlertSystemHandle(const DFL::Mdib::MdsHandle& mdsHandle);

    private:

        template<class T_ContextIndicator> DFL::Mdib::BasicHandle<T_ContextIndicator>
        static provideContextIndicator(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::Mdib& mdib, const DFL::Mdib::MdsHandle& mdsHandle);
};

}
