#pragma once

#include <Framework/Log/Private/BasicContainerLogger.h>
#include <Framework/Log/Private/ExpImp.h>

#include <boost/circular_buffer.hpp>

namespace DFL
{
namespace Log
{
class Message;

/**
 * @brief Logs messages in a circular buffer.
 *
 * Stores the last n messages whilst n
 * is given to the constructor of this class.
 * Stored messages can be flushed into a @ref DFL::Log::Logger.
 * @snippet Log/Test/UnitTest/TestCircularLogger.cpp SetUp
 * @snippet Log/Test/UnitTest/TestCircularLogger.cpp FlushIntoLogger
 * After flushing the circular buffer is empty.
 *
 * @ingroup Log
 */
class DFL_LOG_EXPIMP CircularLogger
    : public Impl::BasicContainerLogger<boost::circular_buffer<Message>>
{
public:
    /**
     * @brief The capacity type.
     */
    using CapacityType = Type::capacity_type;
    /**
     * @brief Create an empty circular buffer with capacity zero.
     */
    CircularLogger() = default;
    /**
     * @brief Create an empty circular buffer with the specified capacity.
     *
     * @param capacity Count of the last n messages kept in buffer.
     */
    explicit CircularLogger(const CapacityType& capacity);
};
}
}
