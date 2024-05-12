#pragma once

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/HandleHelper.h>

#include <boost/optional.hpp>

#include <vector>
#include <set>

namespace DFL::Mdib
{

/**
 * @brief Untyped handle container.
 * @ingroup Mdib
 */
class Handle
{
    public:
        /**
         * @brief Default constructor creates invalid %Handle.
         */
        Handle() = default;

        /**
         * @brief Creates %Handle from string.
         */
        explicit Handle(const std::string& handle);

        /**
         * @brief Creates %Handle from string.
         */
        explicit Handle(const char* handle);

        /**
         * @brief Checks the handle string for validity.
         * @details The handle must not be empty and shall only contain
         * ASCII character codes in the range of [0x21, 0x7E]
         */
        bool isValid() const noexcept;

        /**
         * @brief Return the handle as string.
         * @details Invalid strings are not empty in contrast to the implicit conversion.
         */
        const std::string& string() const noexcept;

        /**
         * @brief Returns valid handle or empty string.
         */
        operator std::string() const;

    private:
        std::string m_handle{};
        Impl::HandleValidity m_validity{Impl::HandleValidity::Invalid};
};

/**
 * @brief Identifier for an object in the MDIB.
 * @details It is a non-empty string that shall only contain
 * ASCII character codes in the range of [0x21, 0x7E]
 *
 * @ingroup Mdib
 */
template <typename Entity>
class BasicHandle
{
    public:
        /**
         * @brief Provides access to the entity type.
         * @details Typically it is a specialization from one of MdibEntity, ContextStateEntity, and ContextDescriptorEntity
         * like \ref Mds, \ref LocationContext, and \ref LocationContextIndicator.
         */
        using EntityType = Entity;

        /**
         * @brief Default constructor creates invalid handle.
         */
        BasicHandle() = default;

        /**
         * @brief Creates typed handle from \ref DFL::Mdib::Handle.
         * @details Applies the validity from the input, so that it is not required to compute the validity again.
         */
        explicit BasicHandle(const Handle& handle);

        /**
         * @brief Creates handle from string.
         */
        explicit BasicHandle(const std::string& handle);

        /**
         * @brief Creates handle from string.
         */
        explicit BasicHandle(const char* handle);

        /**
         * @brief Checks the handle string for validity.
         * @details The handle must not be empty and shall only contain
         * ASCII character codes in the range [0x21, 0x7E].
         */
        bool isValid() const noexcept;

        /**
         * @brief Return the handle as string.
         * @details Invalid strings are not empty in contrast to the implicit conversion.
         */
        const std::string& string() const noexcept;

    private:
        std::string m_handle{};
        Impl::HandleValidity m_validity{Impl::HandleValidity::Invalid};
};

/**
 * @brief Conversion to untyped handle.
 * @ingroup Mdib
 */
template <typename Entity>
Handle toHandle(const BasicHandle<Entity>& basicHandle)
{
        return Handle(basicHandle.string());
}

/**
 * @brief Sequence of untyped \ref Handle.
 * @ingroup Mdib
 */
using Handles = std::vector<Handle>;

/**
 * @brief Set of untyped \ref Handle.
 * @ingroup Mdib
 */
using HandleSet = std::set<Handle>;

/**
 * @brief Comparator for Handle.
 * @details Invalid handles are not comparable (similar to float NaN).
 * When comparing an invalid handle, the comparison results in @c false.
 *
 * @ingroup Mdib
 * @{
 */

bool operator==(const Handle& lhs, const Handle& rhs) noexcept;
bool operator==(const std::string& lhs, const Handle& rhs) noexcept;
bool operator==(const Handle& lhs, const std::string& rhs) noexcept;
bool operator!=(const Handle& lhs, const Handle& rhs) noexcept;
bool operator!=(const std::string& lhs, const Handle& rhs) noexcept;

bool operator!=(const Handle& lhs, const std::string& rhs) noexcept;
bool operator<(const Handle& lhs, const Handle& rhs) noexcept;
bool operator<=(const Handle& lhs, const Handle& rhs) noexcept;
bool operator>(const Handle& lhs, const Handle& rhs) noexcept;
bool operator>=(const Handle& lhs, const Handle& rhs) noexcept;


template <typename Entity>
bool operator==(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept;

template <typename Entity>
bool operator!=(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept;

template <typename Entity>
bool operator<(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept;

template <typename Entity>
bool operator<=(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept;

template <typename Entity>
bool operator>(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept;

template <typename Entity>
bool operator>=(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept;
/** @} */

inline Handle::Handle(const std::string& handle) :
        m_handle(handle),
        m_validity(Impl::validityOf(handle))
{
}

inline Handle::Handle(const char* handle) :
        m_handle((handle == nullptr ? std::string() : handle)),
        m_validity(Impl::validityOf(m_handle))
{
}

inline bool Handle::isValid() const noexcept
{
    return m_validity == Impl::HandleValidity::Valid;
}

inline const std::string& Handle::string() const noexcept
{
    return m_handle;
}

inline Handle::operator std::string() const
{
    if (isValid())
    {
        return m_handle;
    }
    return {};
}

template <typename Entity>
inline BasicHandle<Entity>::BasicHandle(const Handle& handle) :
        m_handle(handle.string()),
        m_validity(handle.isValid() ? Impl::HandleValidity::Valid : Impl::HandleValidity::Invalid)
{
}

template <typename Entity>
inline BasicHandle<Entity>::BasicHandle(const std::string& handle) :
        m_handle(handle),
        m_validity(Impl::validityOf(handle))
{
}

template <typename Entity>
inline BasicHandle<Entity>::BasicHandle(const char* handle) :
        m_handle(handle),
        m_validity(Impl::validityOf(m_handle))
{
}

template <typename Entity>
inline bool BasicHandle<Entity>::isValid() const noexcept
{
    return m_validity == Impl::HandleValidity::Valid;
}

template <typename Entity>
inline const std::string& BasicHandle<Entity>::string() const noexcept
{
    return m_handle;
}

inline bool operator ==(const Handle& lhs, const Handle& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() == rhs.string();
}
inline bool operator ==(const std::string& lhs, const Handle& rhs) noexcept
{
    return rhs.isValid() && lhs == rhs.string();
}
inline bool operator ==(const Handle& lhs, const std::string& rhs) noexcept
{
    return lhs.isValid() && lhs.string() == rhs;
}

inline bool operator !=(const Handle& lhs, const Handle& rhs) noexcept
{
    return !(lhs == rhs);
}
inline bool operator !=(const std::string& lhs, const Handle& rhs) noexcept
{
    return !(lhs == rhs);
}
inline bool operator !=(const Handle& lhs, const std::string& rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator <(const Handle& lhs, const Handle& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() < rhs.string();
}

inline bool operator <=(const Handle& lhs, const Handle& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() <= rhs.string();
}

inline bool operator >(const Handle& lhs, const Handle& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() > rhs.string();
}

inline bool operator >=(const Handle& lhs, const Handle& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() >= rhs.string();
}


template <typename Entity>
inline bool operator ==(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() == rhs.string();
}

template <typename Entity>
inline bool operator !=(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept
{
    return !(lhs == rhs);
}

template <typename Entity>
inline bool operator <(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() < rhs.string();
}

template <typename Entity>
inline bool operator <=(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() <= rhs.string();
}

template <typename Entity>
inline bool operator >(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() > rhs.string();
}

template <typename Entity>
inline bool operator >=(const DFL::Mdib::BasicHandle<Entity>& lhs, const DFL::Mdib::BasicHandle<Entity>& rhs) noexcept
{
    return lhs.isValid() && rhs.isValid() && lhs.string() >= rhs.string();
}

}
