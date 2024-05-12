#pragma once

#include <Framework/Mdib/Public/Model/Uri.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief BICEPS instance identifier root.
 * @ingroup Mdib
 */
class Root
{
    public:
        /**
         * @brief Creates a %Root from given \ref Uri instance.
         */
        Root(const Uri& rootUri);

        /**
         * @brief Gets the plain \ref Uri object.
         */
        const Uri& get() const noexcept;

        /**
         * @brief Returns \c true if this root is the null-flavor unknown root as specified by BICEPS (biceps:R0135), otherwise \c false.
         */
        bool isUnknown() const noexcept;

        /**
         * @brief Returns the null-flavor unknown root as specified by BICEPS (biceps:R0135).
         */
        static const Root& unknownRoot();

        friend bool operator==(const Root& lhs, const Root& rhs) noexcept;

        friend bool operator!=(const Root& lhs, const Root& rhs) noexcept;

        friend bool operator<(const Root& lhs, const Root& rhs);

        friend bool operator<=(const Root& lhs, const Root& rhs);

        friend bool operator>(const Root& lhs, const Root& rhs);

        friend bool operator>=(const Root& lhs, const Root& rhs);

    private:
        Uri m_root;
};

inline Root::Root(const Uri& rootUri) :
        m_root(rootUri.get().empty() ? unknownRoot().get() : rootUri)
{
}

inline const Uri& Root::get() const noexcept
{
    return m_root;
}

inline bool Root::isUnknown() const noexcept
{
    return m_root.get() == "biceps.uri.unk";
}

inline const Root& Root::unknownRoot()
{
    // The unknown root is encoded as defined in biceps:R0135
    static const Root unknownRoot = Root(Uri("biceps.uri.unk"));
    return unknownRoot;
}

/**
 * @brief Returns \c true if \c lhs is equal to \c rhs, otherwise \c false.
 * @ingroup Mdib
 */
inline bool operator==(const Root& lhs, const Root& rhs) noexcept
{
    return lhs.m_root == rhs.m_root;
}
/**
 * @brief Returns \c true if \c lhs is not equal to \c rhs, otherwise \c false.
 * @ingroup Mdib
 */
inline bool operator!=(const Root& lhs, const Root& rhs) noexcept
{
    return lhs.m_root != rhs.m_root;
}

/**
 * @brief Returns \c true if \c lhs is lexicographically lower than \c rhs, otherwise \c false.
 * @ingroup Mdib
 */
inline bool operator<(const Root& lhs, const Root& rhs)
{
    return lhs.m_root < rhs.m_root;
}

/**
 * @brief Returns \c true if \c lhs is lexicographically lower than or equal to \c rhs, otherwise \c false.
 * @ingroup Mdib
 */
inline bool operator<=(const Root& lhs, const Root& rhs)
{
    return lhs.m_root <= rhs.m_root;
}

/**
 * @brief Returns \c true if \c lhs is lexicographically greater than \c rhs, otherwise \c false.
 * @ingroup Mdib
 */
inline bool operator>(const Root& lhs, const Root& rhs)
{
    return lhs.m_root > rhs.m_root;
}

/**
 * @brief Returns \c true if \c lhs is lexicographically greater than or equal to \c rhs, otherwise \c false.
 * @ingroup Mdib
 */
inline bool operator>=(const Root& lhs, const Root& rhs)
{
    return lhs.m_root >= rhs.m_root;
}

}
}
