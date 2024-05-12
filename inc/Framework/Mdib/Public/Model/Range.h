#pragma once

#include <vector>
#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Private/HasExtensions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Container for a range.
 * @ingroup Mdib
 */
class Range: public Impl::HasExtensions
{
    public:

        /**
         * @brief Constructor of a range with all empty members.
         */
        Range() = default;

        /**
         * @brief Constructor with limits only.
         */
        Range(boost::optional<Decimal> lower,
              boost::optional<Decimal> upper);

        /**
         * @brief Constructor with limits and step width.
         * @deprecated Please use use either the constructor with limits only or the constructor with all members.
         */
        Range(boost::optional<Decimal> lower,
              boost::optional<Decimal> upper,
              boost::optional<Decimal> stepWidth);

        /**
         * @brief Constructor with all members.
         *
         */
        Range(boost::optional<Decimal> lower,
              boost::optional<Decimal> upper,
              boost::optional<Decimal> stepWidth,
              boost::optional<Decimal> relativeAccuracy,
              boost::optional<Decimal> absoluteAccuracy,
              ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The including lower bound of the range.
         */
        const boost::optional<Decimal>& lower() const;

        /**
         * @brief The including upper bound of the range.
         */
        const boost::optional<Decimal>& upper() const;

        /**
         * @brief The numerical distance between two values in the range of the given upper and lower bound.
         */
        const boost::optional<Decimal>& stepWidth() const;

        /**
         * @brief Maximum relative error in relation to the correct value within the given range.
         */
        const boost::optional<Decimal>& relativeAccuracy() const;

        /**
         * @brief Maximum absolute error in relation to the correct value within the given range.
         */
        const boost::optional<Decimal>& absoluteAccuracy() const;

    private:
        boost::optional<Decimal> m_lower;
        boost::optional<Decimal> m_upper;
        boost::optional<Decimal> m_stepWidth;
        boost::optional<Decimal> m_relativeAccuracy;
        boost::optional<Decimal> m_absoluteAccuracy;
};

/**
 * @name Comparison operators
 */
///@{
bool operator==(const Range& lhs, const Range& rhs);
bool operator!=(const Range& lhs, const Range& rhs);
///@}

/**
 * @brief Sequence of ranges.
 * @ingroup Mdib
 */
using Ranges = std::vector<Range>;

inline Range::Range(boost::optional<Decimal> lower,
                    boost::optional<Decimal> upper) :
        m_lower(std::move(lower)),
        m_upper(std::move(upper))
{
}


inline Range::Range(boost::optional<Decimal> lower,
                    boost::optional<Decimal> upper,
                    boost::optional<Decimal> stepWidth):
        m_lower(std::move(lower)),
        m_upper(std::move(upper)),
        m_stepWidth(std::move(stepWidth))
{
}

inline Range::Range(boost::optional<Decimal> lower,
                    boost::optional<Decimal> upper,
                    boost::optional<Decimal> stepWidth,
                    boost::optional<Decimal> relativeAccuracy,
                    boost::optional<Decimal> absoluteAccuracy,
                    ExtensionTypes extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_lower(std::move(lower)),
        m_upper(std::move(upper)),
        m_stepWidth(std::move(stepWidth)),
        m_relativeAccuracy(std::move(relativeAccuracy)),
        m_absoluteAccuracy(std::move(absoluteAccuracy))
{
}

inline const boost::optional<Decimal>& Range::lower() const
{
    return m_lower;
}

inline const boost::optional<Decimal>& Range::upper() const
{
    return m_upper;
}

inline const boost::optional<Decimal>& Range::stepWidth() const
{
    return m_stepWidth;
}

inline const boost::optional<Decimal>& Range::relativeAccuracy() const
{
    return m_relativeAccuracy;
}

inline const boost::optional<Decimal>& Range::absoluteAccuracy() const
{
    return m_absoluteAccuracy;
}

inline bool operator==(const Range& lhs, const Range& rhs)
{
    if (&lhs == &rhs)
    {
        return true;
    }

    return lhs.upper() == rhs.upper()
            && lhs.lower() == rhs.lower()
            && lhs.stepWidth() == rhs.stepWidth()
            && lhs.relativeAccuracy() == rhs.relativeAccuracy()
            && lhs.absoluteAccuracy() == rhs.absoluteAccuracy()
            && lhs.extensions() == rhs.extensions();
}

inline bool operator!=(const Range& lhs, const Range& rhs)
{
    return !(lhs == rhs);
}

} /* namespace Mdib */
} /* namespace DFL */
