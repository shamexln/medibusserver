#pragma once

#include <Framework/Format/Public/StreamEach.h>

#include <deque>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <utility>
#include <vector>

/**
 * @file
 *
 * @brief IO streaming operators for std containers.
 * @details \note The CPP standard says that it is undefined behavior to add declarations or definitions to namespace std
 * (or to any namespace nested within std). StdContainerIo.h should not cause any undefined behavior as it only adds
 * missing streaming operators to the namespace.
 * Further information: https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL58-CPP.+Do+not+modify+the+standard+namespaces
 *
 * Usage:
 *
 * @snippet Utils/Test/UnitTest/TestStdContainerIo.cpp StdContainerIo
 *
 * @ingroup Utils
 */

// warning: modification of 'std' namespace can result in undefined behavior [cert-dcl58-cpp]
// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std
{

/**
 * @{
 * @brief Streams content of given container to given stream.
 *
 * @ingroup Utils
 */

template <class T, class U>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::pair<T, U>& c);

template <class T, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::vector<T, A>& c);

template <class T, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::deque<T, A>& c);

template <class T, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::list<T, A>& c);

template <class T, class C, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::set<T, C, A>& c);

template <class K, class V, class C, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::map<K, V, C, A>& c);

template <class K, class V, class C, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm,
                         const std::multimap<K, V, C, A>& c);

///@}

template <class T, class U>
// NOLINTNEXTLINE(cert-dcl58-cpp)
inline std::ostream& operator<<(std::ostream& strm, const std::pair<T, U>& c)
{
    strm << '{' << c.first << ',' << c.second << '}';
    return strm;
}

template <class T, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
inline std::ostream& operator<<(std::ostream& strm, const std::vector<T, A>& c)
{
    return DFL::Format::streamEach(strm, c);
}

template <class T, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::deque<T, A>& c)
{
    return DFL::Format::streamEach(strm, c);
}

template <class T, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::list<T, A>& c)
{
    return DFL::Format::streamEach(strm, c, "(", ")");
}

template <class T, class C, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::set<T, C, A>& c)
{
    return DFL::Format::streamEach(strm, c, "<", ">");
}

template <class K, class V, class C, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::map<K, V, C, A>& c)
{
    return DFL::Format::streamEach(strm, c, "<", ">");
}

template <class K, class V, class C, class A>
// NOLINTNEXTLINE(cert-dcl58-cpp)
std::ostream& operator<<(std::ostream& strm, const std::multimap<K, V, C, A>& c)
{
    return DFL::Format::streamEach(strm, c, "<", ">");
}
}
