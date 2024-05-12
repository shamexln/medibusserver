#pragma once

#include <memory>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

namespace S31
{
class CommandLineOptions;

class S31_CORE_IT_UTIL_EXPIMP IntegrationTestStartUpCode
{
    public:
        IntegrationTestStartUpCode();
        virtual ~IntegrationTestStartUpCode();

        static IntegrationTestStartUpCode* getInstance();
        static const CommandLineOptions& options();
        static bool isJenkinsMainBuild();

    private:
        static std::unique_ptr<IntegrationTestStartUpCode> m_instance;
        void addOptionFromProcessCommandLine();
        std::unique_ptr<CommandLineOptions> m_options;

};

} /* namespace S31 */
