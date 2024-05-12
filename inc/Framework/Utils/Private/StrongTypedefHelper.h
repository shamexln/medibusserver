#pragma once

namespace DFL
{
namespace Impl
{
template<class T, template<class> class CrtpType>
struct CrtpHelper
{
    T& underlying() noexcept
    {
        return static_cast<T&>(*this);
    }

    const T& underlying() const noexcept
    {
        return static_cast<const T&>(*this);
    }
};

template<class T>
struct Ignore1
{};

template<class T>
struct Ignore2
{};

template<class T>
struct Ignore3
{};

template<class T>
struct Ignore4
{};

template<class T>
struct Ignore5
{};

template<class T>
struct Ignore6
{};

template<class T>
struct Ignore7
{};

template<class T>
struct Ignore8
{};

template<class T>
struct Ignore9
{};

template<class T>
struct Ignore10
{};
}
}
