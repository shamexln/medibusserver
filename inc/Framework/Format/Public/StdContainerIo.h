#pragma once

#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/StreamEach.h>

#include <array>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

namespace DFL
{
namespace Format
{
/**
 * @brief Streams content of given std container to given stream.
 *
 * @ingroup Format
 * @{
 */
template <class T, class U>
Stream& operator<<(Stream& str, const std::pair<T, U>& c);
template <class T, size_t N>
Stream& operator<<(Stream& str, T (&c)[N]);
template <class T, size_t N>
Stream& operator<<(Stream& str, const std::array<T, N>& a);
template <class T, class A>
Stream& operator<<(Stream&, const std::vector<T, A>& c);
template <class T, class A>
Stream& operator<<(Stream&, const std::deque<T, A>& c);
template <class T, class A>
Stream& operator<<(Stream&, const std::list<T, A>& c);
template <class T, class C, class A>
Stream& operator<<(Stream& str, const std::set<T, C, A>& c);
template <class K, class V, class C, class A>
Stream& operator<<(Stream& str, const std::map<K, V, C, A>& c);
template <class K, class V, class C, class A>
Stream& operator<<(Stream& str, const std::multimap<K, V, C, A>& c);
/** @} */
template <class T, class U>
inline Stream& operator<<(Stream& str, const std::pair<T, U>& c)
{
    str << '{' << c.first << ',' << c.second << '}';
    return str;
}

template <class T, size_t N>
inline Stream& operator<<(Stream& str, T (&c)[N])
{
    return streamEach(str, c);
}

template <class T, size_t N>
inline Stream& operator<<(Stream& str, const std::array<T, N>& a)
{
    return streamEach(str, a);
}

template <class T, class A>
inline Stream& operator<<(Stream& str, const std::vector<T, A>& c)
{
    return streamEach(str, c);
}

template <class T, class A>
inline Stream& operator<<(Stream& str, const std::deque<T, A>& c)
{
    return streamEach(str, c);
}

template <class T, class A>
inline Stream& operator<<(Stream& str, const std::list<T, A>& c)
{
    return streamEach(str, c, "(", ")");
}

template <class T, class C, class A>
inline Stream& operator<<(Stream& str, const std::set<T, C, A>& c)
{
    return streamEach(str, c, "<", ">");
}

template <class K, class V, class C, class A>
inline Stream& operator<<(Stream& str, const std::map<K, V, C, A>& c)
{
    return streamEach(str, c, "<", ">");
}

template <class K, class V, class C, class A>
inline Stream& operator<<(Stream& str, const std::multimap<K, V, C, A>& c)
{
    return streamEach(str, c, "<", ">");
}
}
}
