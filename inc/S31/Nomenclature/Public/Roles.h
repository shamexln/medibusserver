#pragma once

#include <Framework/Utils/Public/Oid.h>
#include <Framework/Mdib/Public/Roles.h>

namespace S31::Nomenclature
{
/**
 * \brief The \ref DFL::Oid representing TLS Web server authentication.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid TlsWebServerAuthentication = DFL::Oid(DFL::Oid::DotNotation("1.3.6.1.5.5.7.3.1"));
/**
 * \brief The \ref DFL::Oid representing TLS Web client authentication.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid TlsWebClientAuthentication = DFL::Oid(DFL::Oid::DotNotation("1.3.6.1.5.5.7.3.2"));
/**
 * \brief The \ref DFL::Oid representing Draeger Sdc Service Provider role.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid SdcServiceProvider = DFL::Oid(DFL::Oid::DotNotation("1.2.840.10004.20701.1.1"));

/**
 * \brief The \ref DFL::Oid representing Draeger Sdc Service Consumer role.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid SdcServiceConsumer = DFL::Oid(DFL::Oid::DotNotation("1.2.840.10004.20701.1.2"));

/**
 * \brief The \ref DFL::Oid representing Draeger SDC Metric Provider role.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid SdcMetricProvider = DFL::Mdib::MetricProvider.get();

/**
 * \brief The \ref DFL::Oid representing Draeger SDC Metric Consumer role.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid SdcMetricConsumer = DFL::Mdib::MetricConsumer.get();

/**
 * \brief The \ref DFL::Oid representing Draeger SDC Alert Provider role.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid SdcAlertProvider = DFL::Mdib::AlertProvider.get();

/**
 * \brief The \ref DFL::Oid representing Draeger SDC Alert Consumer role.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid SdcAlertConsumer = DFL::Mdib::AlertConsumer.get();

/**
 * \brief The \ref DFL::Oid representing Draeger SDC Operation Provider role.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid SdcOperationProvider = DFL::Mdib::OperationProvider.get();

/**
 * \brief The \ref DFL::Oid representing Draeger SDC Operation Consumer role.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid SdcOperationConsumer = DFL::Mdib::OperationConsumer.get();

/**
 * \brief The \ref DFL::Oid representing Draeger SDC Alert Consumer role intended for use in a distributed alarm system.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Oid SdcDistributedAlarmSystemConsumer = DFL::Mdib::DistributedAlarmSystemConsumer.get();

/**
 * \brief The \ref DFL::Oid representing Dräger-specific SDC Consumer role.
 * \details The functionality corresponds to the (not yet standardized) Base Consumer PKP OID. (See S31TSR_3648)
 * \ingroup S31Nomenclature
 */
static const DFL::Oid DraegerSpecificSdcConsumer = DFL::Oid(DFL::Oid::DotNotation("1.3.6.1.4.1.3592.2.23.9.1"));

/**
 * \brief The \ref DFL::Oid representing Dräger-specific SDC Provider role (as listed in DOORS Common Draeger OIDs).
 * \details The functionality corresponds to the (not yet standardized) Base Provider PKP OID.
 * \ingroup S31Nomenclature
 */
static const DFL::Oid DraegerSpecificSdcProvider = DFL::Oid(DFL::Oid::DotNotation("1.3.6.1.4.1.3592.2.23.8.1"));

}
