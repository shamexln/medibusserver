#pragma once

namespace S31
{
class CoreConfiguration;
class CommandLineOptions;
namespace Test
{

class ConfigurationConverter
{
    public:
        static void setCommandLineOptions(CoreConfiguration& destination, const CommandLineOptions& source);
};

}
}
