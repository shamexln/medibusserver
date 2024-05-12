#pragma once

#include <S31/Sdc/Private/Common/Endpoint/EndpointUrl.h>
#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Sdc/Public/Common/AssuredForwardingClass.h>
#include <S31/S31CoreExImp.h>

#include <memory>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Configuration of quality of service for network sockets
 * @ingroup S31SdcCommonSocket
 */
class S31_CORE_EXPIMP QualityOfService
{
    public:
#ifdef WIN32
        /// @brief Default constuctor
        QualityOfService();

        /// @brief destructor
        ~QualityOfService();

        /// @brief Allow moving
        QualityOfService(QualityOfService&&);
        QualityOfService& operator=(QualityOfService&&);
#endif

        /// @brief Set the \ref AssuredForwardingClass that will be used to configure a socket
        void prepare(bool isEnabled, AssuredForwardingClass codePoint);

        /// @brief Configures quality of service according to previously prepared \ref AssuredForwardingClass
        /// @note When running on %Windows, this method requires the application to be a member of the %Administrators
        /// or the %Network %Configuration %Operators group
        void configureSocket(SOAP_SOCKET sockfd);

        /// @brief Perform any platform specific cleanup operations when a socket closes
        void socketClosing(SOAP_SOCKET sockfd);

    private:
        bool m_qosEnabled = false;
        AssuredForwardingClass m_dscp = AssuredForwardingClass::None;
#ifdef WIN32
        class QualityOfServiceWin32Impl;
        std::unique_ptr<QualityOfServiceWin32Impl> m_impl;
#endif
};

inline void QualityOfService::prepare(bool isEnabled, AssuredForwardingClass codePoint)
{
    m_qosEnabled = isEnabled;
    m_dscp = codePoint;
}

}
