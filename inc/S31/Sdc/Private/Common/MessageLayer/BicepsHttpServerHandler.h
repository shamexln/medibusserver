#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/Http/HttpServerHandler.h>

#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{
class ISoapContextPool;
class LocalDeviceRegistry;
class HttpSessionContext;

/**
 * @brief Implementation of @ref S31::Sdc::Impl::HttpServerHandler interface for SDC functionality.
 * @details Http GET requests (for the WSDL file) are handled directly. Http POST messages are dispatched and the
 * requests are forwarded to specific implementations with help of the @ref S31::Sdc::Impl::LocalDeviceRegistry. Soap
 * handles are obtained from the provided @ref S31::Sdc::Impl::ISoapContextPool.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP BicepsHttpServerHandler : public HttpServerHandler
{
public:
    BicepsHttpServerHandler(
            const DFL::NotNull<std::shared_ptr<ISoapContextPool>>&    soapPool,
            const DFL::NotNull<std::shared_ptr<LocalDeviceRegistry>>& deviceRegistry);

    void registerForDirectory(std::string_view dirname, const DFL::NotNull<std::shared_ptr<HttpPostHandler>>& callback);

    HttpServerResponse handleHttpGet(
            HttpPathView                                            targetPath,
            HttpAcceptEncodingView                                  acceptEncoding,
            DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext) override;

    HttpServerResponse handleHttpPost(
            HttpPathView                                            targetPath,
            HttpAcceptEncodingView                                  acceptEncoding,
            std::string_view                                        body,
            HttpContentTypeView                                     contentType,
            HttpContentEncodingView                                 contentEncoding,
            DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext) override;

    void handleError(
            HttpPathView                                            targetPath,
            const Utils::Error&                                     error,
            DFL::NotNull<std::shared_ptr<const HttpSessionContext>> sessionContext) override;

private:
    std::weak_ptr<ISoapContextPool>    m_soapPool;
    std::weak_ptr<LocalDeviceRegistry> m_deviceRegistry;

    std::map<std::string, std::weak_ptr<HttpPostHandler>> m_registeredDispatcher;
    std::mutex                                        m_mutex;
};
}  // namespace S31::Sdc::Impl
