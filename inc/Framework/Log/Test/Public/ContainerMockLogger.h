#pragma once

#include <Framework/Log/Public/ContainerLogger.h>
#include <Framework/Log/Public/Logger.h>

#include <functional>

namespace DFL
{
namespace Log
{
namespace Test
{
/**
 * @brief Provides a logger which can be injected into a ctor or function
 * and stores all logged messages in a container which can be querried.
 *
 * @snippet Log/Test/UnitTest/TestContainerMockLogger.cpp SetUp
 * @snippet Log/Test/UnitTest/TestContainerMockLogger.cpp Inject
 *
 * @ingroup Log
 */
class ContainerMockLogger : public Logger
{
public:
    /**
     * @brief Binds the messages object as sink to the logger instance to be
     * injected.
     */
    ContainerMockLogger();
    /**
     * @brief Contains all messages being send to the logger.
     */
    const ContainerLogger& messages() const noexcept;

private:
    ContainerLogger m_messages{};
};

inline ContainerMockLogger::ContainerMockLogger()
    : Logger{"ContainerMockLogger"}
{
    this->pushBack(std::ref(m_messages));
}

inline const ContainerLogger& ContainerMockLogger::messages() const noexcept
{
    return m_messages;
}
}
}
}
