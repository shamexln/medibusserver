#pragma once

#include <S31/Sdc/Public/Common/CoreConfiguration.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief Checks the validity of the Role Authorization List defined by the given core configuration.
 *
 * @details Sets a global (RemoS) error code if the RAL is invalid.
 */
class RalChecker
{
    public:
        explicit RalChecker(const DFL::NotNull<std::shared_ptr<CoreConfiguration>>& configuration);
        void checkRalValidity() const;

    private:
        std::weak_ptr<CoreConfiguration> m_configuration;
};

}
