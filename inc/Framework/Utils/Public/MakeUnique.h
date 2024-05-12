#pragma once

/**
 * @file
 *
 * @brief Makes the c++14 function [std::make_unique](https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique)
 * available on platforms supporting the c++11 type std::unique_ptr.
 *
 * The motivation for using \c std::make_unique<T>(a, b) instead of \c std::unique_ptr<T>(new T(a, b))
 * is to avoid the creation of memory leaks, e.g:
 * @code
 * foo(std::unique_ptr<T>(new T(a, b)), std::unique_ptr<T>(new T(c, d)));
 * @endcode
 * A new expression consists of three steps:
 * - reserve memory
 * - construct object into that memory
 * - set variable to the address of that memory
 *
 * However the compiler is free to reorder these three instructions. Thus in the example above
 * the compiler is free to reorder all 6 steps. For example one order could be:
 * - reserve memory for first parameter
 * - reserve memory for second parameter
 * - construct first parameter into reserved memory
 *
 * And here it gets interesting. If the constructor throws there is no way to free the memory
 * reserved for the second parameter.
 * @code
 * foo(std::make_unique<T>(a, b), std::make_unique<T>(new T(c, d)));
 * @endcode
 * Using \c make_unique avoids this problem since the compiler either constructs the first parameter
 * and then the second parameter or the other way round.
 * But it can no longer mix the construction steps of the two parameters.
 *
 * @ingroup Utils
 */
#include <memory>
