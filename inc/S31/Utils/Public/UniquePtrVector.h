#pragma once

#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <vector>

namespace S31::Utils
{

/**
 * @brief A std::vector that holds not-null unique pointers.
 * @ingroup S31Utils
 */
template <typename T>
class UniquePtrVector: public std::vector<DFL::NotNull<std::unique_ptr<T>>>
{
    public:
        /**
         * @brief Ctor
         * @details The main purpose of this class. So the class can be created with a first element.
         * @param firstElement A potential first element for the vector. Can be nullptr.
         */
        explicit UniquePtrVector(std::unique_ptr<T> firstElement):
            std::vector<DFL::NotNull<std::unique_ptr<T>>>()
        {
            pushBackIfNotNull(std::move(firstElement));
        }

        UniquePtrVector() = default;
        UniquePtrVector(UniquePtrVector&&) = default;
        UniquePtrVector& operator=(UniquePtrVector&&) = default;
        UniquePtrVector(const UniquePtrVector&) = delete;
        UniquePtrVector& operator=(const UniquePtrVector&) = delete;

        using std::vector<DFL::NotNull<std::unique_ptr<T>>>::push_back; // gcc 4.8. needs this

        void pushBackIfNotNull(std::unique_ptr<T>&& element)
        {
            if (element)
            {
                push_back(std::move(DFL::asNotNull(std::move(element))));
            }
        }

};

}
