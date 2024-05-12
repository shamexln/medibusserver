#pragma once

#include <boost/asio/io_context.hpp>

#include <thread>

namespace S31::Sdc::Test
{

/**
 * @brief Start a thread to run the io_context.
 *
 * @details The thread includes DFL::Crypto::OpenSsl::threadStop()
 * to clean up openssl thread local memory
 */
std::thread runIoContextOnThread(boost::asio::io_context &ioc);

}
