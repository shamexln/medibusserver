#pragma once

#include <S31/Test/S31Only/Exception.h>

#include <string>

/**
 * @brief Macro for checking shared pointers.
 *
 * @details When called for a shared pointer \c sharedPointer then it checks that use count is at most 1 or
 * otherwise raises an google test error. If use count is OK, \c sharedPointer is reset.
 * Used in tests to check for circular \c shared_ptr references.
 */
#define FREELASTREFERENCE(sharedPointer) do { if (sharedPointer.use_count() > 1) \
{ THROW_EXCEPTION("Use count of " #sharedPointer " is " + std::to_string(sharedPointer.use_count()) + ". This is not the last reference."); } sharedPointer.reset(); } while (false)
