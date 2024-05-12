#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Receives UDP datagrams with recvmsg instead of recvfrom (the \ref gSOAP default).
 * @details
 * This is required to get the interface index the UDP datagram is received.
 * This index is required to figure out for example the IP addresses for a ResolveMatches.
 */
int recvfrom_wrapper(struct soap* soapHandle, SOAP_SOCKET sock, char* buf, SOAP_WINSOCKINT buflen, int flags, struct sockaddr* src_addr, SOAP_SOCKLEN_T* addrlen);

/**
 * @brief Wrapper to configure quality of service before connect.
 */
int connect_wrapper(struct soap* soapHandle, SOAP_SOCKET sockfd, struct sockaddr *addr, SOAP_SOCKLEN_T addrlen);

/**
 * @brief Wrapper to inject semaphore locking into SSL_connect() from openSSL.
 */
int SSL_connect_wrapper(struct soap* soapHandle, SSL* ssl);

/**
 * @brief Wrapper to inject application data into ssl context.
 */
void SSL_set_bio_wrapper(struct soap* soap, SSL* ssl, BIO* rbio, BIO* wbio);

/**
 * Forward function to \ref gSOAP private (file static) \c tcp_connect method used as default \c fopen callback.
 */
SOAP_SOCKET default_fopen(struct soap* soapHandle, const char* endpoint, const char* host, int port);

/**
 * Forward function to \ref gSOAP private (file static) \c tcp_closesocket method used as default \c closesocket callback.
 */
int default_fclosesocket(struct soap *soapHandle, SOAP_SOCKET sock);

/**
 * Initialize soap context for after setting of server or client context.
 */
int default_ssl_auth_init(struct soap *soap);

/**
 * Callback for \ref gSOAP to override fault string messages before an error is transmitted.
 */
void custom_seterror(struct soap *soapHandle, const char **errorCode, const char **errorString);

}
