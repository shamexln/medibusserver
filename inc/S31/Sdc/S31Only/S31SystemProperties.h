#pragma once

#include <S31/Base/S31Only/NtStringView.h>

/**
 * \brief S31 system properties.
 *
 * \ingroup S31SdcCommon
 */
namespace S31::S31SystemProperties
{
/// Value to disable a S31 system property.
static constexpr NtStringView Disabled{"0"};

/// Value to enable a S31 system property.
static constexpr NtStringView Enabled{"1"};

/// Allowed network interface for DSOAP.
static constexpr NtStringView S31DsoapAllowInterface{"S31.DsoapAllowInterface"};

/// Maximum of concurrent incoming running HTTP requests.
static constexpr NtStringView S31MaxConcurrentIncomingHttpRequests{"S31.MaxConcurrentIncomingHttpRequests"};

/// Maximum of concurrent outgoing running HTTP requests.
static constexpr NtStringView S31MaxConcurrentOutgoingHttpRequests{"S31.MaxConcurrentOutgoingHttpRequests"};

/// Maximum of concurrent SSL handshakes
static constexpr NtStringView S31MaxConcurrentSslHandshakes{"S31.MaxConcurrentSslHandshakes"};

/// Maximum number of idle keep-alive outgoing connections.
static constexpr NtStringView S31MaxIdleOutgoingConnections{"S31.MaxIdleOutgoingConnections"};

/// Maximum number of idle keep-alive incoming connections.
static constexpr NtStringView S31MaxIdleIncomingConnections{"S31.MaxIdleIncomingConnections"};

///  Maximum number of concurrently running subscriptions on a device.
static constexpr NtStringView S31MaxConcurrentSubscriptionsOnDevice{"S31.MaxConcurrentSubscriptionsOnDevice"};

/// Timeout duration for idle keep-alive connections.
static constexpr NtStringView S31IdleTimeout{"S31.IdleTimeout"};

/// Enables or disables the filter for Loopback Interfaces from the list of multicast interfaces {default: 0}.
static constexpr NtStringView S31DisableLoopbackInterfaceFilter{"S31.DisableLoopbackInterfaceFilter"};

/// Allow any port number for the http and udp connections.
static constexpr NtStringView S31UseAnyPort{"S31.UseAnyPort"};

/// Compression level of for DSOAP messages {default: 0}.
static constexpr NtStringView S31CompressionLevel{"S31.CompressionLevel"};

/// Disable SSL usage {default: 0}.
static constexpr NtStringView S31DisableSslUsage{"S31.DisableSslUsage"};

}
