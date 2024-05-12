#pragma once

#include <boost/mp11/tuple.hpp>

#include <iterator>
#include <type_traits>
#include <utility>

namespace DFL
{
namespace StdExt
{
namespace Impl
{
template <typename Container>
class back_emplace_iterator
{
private:
    struct do_emplace_back
    {
        do_emplace_back(Container* c)
            : container{c}
        {
        }

        template <class... Args>
        void operator()(Args&&... args)
        {
            container->emplace_back(std::forward<Args>(args)...);
        }

        Container* container{nullptr};
    };

    template <class T>
    using not_self = typename std::enable_if<
        !std::is_same<typename std::decay<T>::type,
                      back_emplace_iterator>::value>::type;

public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    explicit back_emplace_iterator(Container& c)
        : container{std::addressof(c)}
    {
    }

    template <class T, class = not_self<T>>
    back_emplace_iterator& operator=(T&& args)
    {
        boost::mp11::tuple_apply(do_emplace_back{container},
                                 std::forward<T>(args));

        return *this;
    }

    back_emplace_iterator& operator*()
    {
        return *this;
    }

    back_emplace_iterator& operator++()
    {
        return *this;
    }

    back_emplace_iterator& operator++(int)
    {
        return *this;
    }

private:
    Container* container;
};

template <typename Container>
inline back_emplace_iterator<Container> back_emplacer(Container& c)
{
    return back_emplace_iterator<Container>{c};
}
}
}
}
