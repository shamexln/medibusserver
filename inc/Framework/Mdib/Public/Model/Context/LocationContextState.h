#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Context/AbstractContextState.h>
#include <Framework/Mdib/Public/Model/Context/ContextAssociation.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

namespace DFL::Mdib
{

/**
 * @brief Dynamic part of a \ref LocationContext.
 * @ingroup Mdib
 */
class LocationContextState: public AbstractContextState
{
    DFL_MDIB_IMMUTABLE(LocationContextState)

    public:
        /**
         * @brief Applies \ref LocationContextState::locationDetail() "location details" to none
         * @details \note Also applies defaults from \ref AbstractContextState.
         */
        LocationContextState();

        /**
         * @brief Full constructor.
         */
        LocationContextState(const boost::optional<CodedValue>& category,
                             ContextAssociation contextAssociation,
                             const boost::optional<VersionCounter>& bindingMdibVersion,
                             const boost::optional<VersionCounter>& unbindingMdibVersion,
                             const boost::optional<Timestamp>& bindingStartTime,
                             const boost::optional<Timestamp>& bindingEndTime,
                             const InstanceIdentifiers& validators,
                             const InstanceIdentifiers& identifications,
                             const boost::optional<LocationDetail>& locationDetail,
                             ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Provides human-readable detailed location information.
         * @details LocationDetail should not be used to form location-based logical systems of devices.
         * @return Location information or \c boost::none if undeclared.
         */
        const boost::optional<LocationDetail>& locationDetail() const;

    private:
        boost::optional<LocationDetail> m_locationDetail;

};

inline LocationContextState::LocationContextState() :
        AbstractContextState(),
        m_locationDetail(boost::none)
{
}

inline LocationContextState::LocationContextState(const boost::optional<CodedValue>& category,
                                                  ContextAssociation contextAssociation,
                                                  const boost::optional<VersionCounter>& bindingMdibVersion,
                                                  const boost::optional<VersionCounter>& unbindingMdibVersion,
                                                  const boost::optional<Timestamp>& bindingStartTime,
                                                  const boost::optional<Timestamp>& bindingEndTime,
                                                  const InstanceIdentifiers& validators,
                                                  const InstanceIdentifiers& identifications,
                                                  const boost::optional<LocationDetail>& locationDetail, // NOLINT(modernize-pass-by-value)
                                                  ExtensionTypes extensions) :
        AbstractContextState(category,
                             contextAssociation,
                             bindingMdibVersion,
                             unbindingMdibVersion,
                             bindingStartTime,
                             bindingEndTime,
                             validators,
                             identifications,
                             std::move(extensions)),
        m_locationDetail(locationDetail)
{
}

inline const boost::optional<LocationDetail>& LocationContextState::locationDetail() const
{
    return m_locationDetail;
}

/**
 * @brief Definition of shared pointer type \ref LocationContextStateSharedPtr for state \ref LocationContextState.
 * @ingroup Mdib
 */
using LocationContextStateSharedPtr = SharedPtr<LocationContextState>;


}
