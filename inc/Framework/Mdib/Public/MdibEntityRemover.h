#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Component/Channel.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Component/Sco.h>
#include <Framework/Mdib/Public/Model/Component/SystemContext.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextIndicator.h>

#include <Framework/Utils/Public/NotNull.h>

namespace DFL
{
namespace Mdib
{
/**
 * @brief Adds remove entries for the entity and add child to the given MdibChangeSet.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP MdibEntityRemover
{
    public:
        /**
         * @brief Adds the given \ref Mds and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const MdsHandle& handle, MdibChangeSet& mdibChangeSet);
        /**
         * @brief Adds the given \ref Mds and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const Mdib& mdib, const MdsHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref Vmd and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const VmdHandle& handle, MdibChangeSet& mdibChangeSet);
        /**
         * @brief Adds the given \ref Vmd and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const Mdib& mdib, const VmdHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref Channel and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const ChannelHandle& handle, MdibChangeSet& mdibChangeSet);
        /**
         * @brief Adds the given \ref Channel and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const Mdib& mdib, const ChannelHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref VmdAlertSystem and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const VmdAlertSystemHandle& handle, MdibChangeSet& mdibChangeSet);
        /**
         * @brief Adds the given \ref VmdAlertSystem and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const Mdib& mdib, const VmdAlertSystemHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref MdsAlertSystem and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const MdsAlertSystemHandle& handle, MdibChangeSet& mdibChangeSet);
        /**
         * @brief Adds the given \ref MdsAlertSystem and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const Mdib& mdib, const MdsAlertSystemHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref VmdSco and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const VmdScoHandle& handle, MdibChangeSet& mdibChangeSet);
        /**
         * @brief Adds the given \ref VmdSco and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const Mdib& mdib, const VmdScoHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref MdsSco and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const MdsScoHandle& handle, MdibChangeSet& mdibChangeSet);
        /**
         * @brief Adds the given \ref MdsSco and all sub tree entities as removed entities to an \ref MdibChangeSet.
         */
        static void remove(const Mdib& mdib, const MdsScoHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref SystemContext and all sub tree entities as removed entities to an \ref MdibChangeSet.
         *
         * @deprecated
         * This function does not make sense since it violates biceps:R0106:
         * > Any context descriptor SHALL NOT be removed from or added to the
         * > MDIB during runtime, except if the hosting MDS is removed or added
         * > to the MDIB.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const SystemContextHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref PatientContextIndicator and all sub tree entities as removed entities to an \ref MdibChangeSet.
         *
         * @deprecated
         * This function does not make sense since it violates biceps:R0106:
         * > Any context descriptor SHALL NOT be removed from or added to the
         * > MDIB during runtime, except if the hosting MDS is removed or added
         * > to the MDIB.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const PatientContextIndicatorHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref LocationContextIndicator and all sub tree entities as removed entities to an \ref MdibChangeSet.
         *
         * @deprecated
         * This function does not make sense since it violates biceps:R0106:
         * > Any context descriptor SHALL NOT be removed from or added to the
         * > MDIB during runtime, except if the hosting MDS is removed or added
         * > to the MDIB.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const LocationContextIndicatorHandle& handle, MdibChangeSet& mdibChangeSet);

        /**
         * @brief Adds the given \ref EnsembleContextIndicator and all sub tree entities as removed entities to an \ref MdibChangeSet.
         *
         * @deprecated
         * This function does not make sense since it violates biceps:R0106:
         * > Any context descriptor SHALL NOT be removed from or added to the
         * > MDIB during runtime, except if the hosting MDS is removed or added
         * > to the MDIB.
         */
        static void remove(const NotNull<MdibSharedPtr>& mdib, const EnsembleContextIndicatorHandle& handle, MdibChangeSet& mdibChangeSet);

    private:

        template<class T_Entity1, class T_Entity2>
        static void removeEntitySubTree(const Mdib& mdib, const BasicHandle<T_Entity1>& handle, MdibChangeSet& mdibChangeSet);

        template<class T_Entity1, class T_Entity2, class T_Entity3>
        static void removeEntitySubTree(const Mdib& mdib, const BasicHandle<T_Entity1>& handle, MdibChangeSet& mdibChangeSet);

        template<class T_Entity1, class T_Entity2, class T_Entity3, class T_Entity4>
        static void removeEntitySubTree(const Mdib& mdib, const BasicHandle<T_Entity1>& handle, MdibChangeSet& mdibChangeSet);

        template<class T_Entity1, class T_Entity2, class T_Entity3, class T_Entity4, class T_Entity5>
        static void removeEntitySubTree(const Mdib& mdib, const BasicHandle<T_Entity1>& handle, MdibChangeSet& mdibChangeSet);
};

}
}
