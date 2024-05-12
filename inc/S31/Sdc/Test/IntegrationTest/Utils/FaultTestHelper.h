#pragma once

#include <string>

namespace S31Test::Sdc
{

/**
 * @brief Run a test that will cause a soap fault response
 *
 * @param message httpRequest XML to send
 * @param fault expected fault string received in fault respoonse
 */

void runFaultTest(const std::string& message, const std::string& fault);

/**
 * @brief Run a test that will not cause a soap fault response
 *
 * @param message httpRequest XML to send
 */
void runNoFaultTest(const std::string& message);

}
