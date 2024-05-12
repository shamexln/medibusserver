#pragma once

#include <Framework/Format/Public/StreamEach.h>
#include <Framework/Log/Public/ContainerLogger.h>
#include <Framework/Log/Public/Logger.h>
#include <Framework/Log/Public/LoggerStateSaver.h>
#include <Framework/Log/Public/MessageIo.h>

#include <boost/ref.hpp>

#include <ostream>

namespace DFL
{
namespace Log
{
namespace Test
{
/**
 * @brief Mocks a given Logger by redirecting all messages into a container.
 *
 * @snippet Log/Sample/Sample.cpp UsageMockLogger
 *
 * @ingroup Log
 */
class MockLogger : public ContainerLogger
{
public:
    /**
     * @brief Constructs a mock for the given logger.
     */
    MockLogger(Logger& logger);

private:
    LoggerStateSaver m_stateSaver;
};

inline MockLogger::MockLogger(Logger& logger)
    : ContainerLogger{}
    , m_stateSaver{logger}
{
    logger.clear();
    logger.pushBack(boost::ref(*this));
}

inline std::ostream& operator<<(std::ostream& o, const MockLogger& ml)
{
    return Format::streamEach(o, ml.cbegin(), ml.cend(), '[', ']', '\n');
}
}
}
}
