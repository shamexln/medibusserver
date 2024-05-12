#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/Range.h>

#include <vector>

namespace DFL::Mdib
{

/**
 * @brief Representation of the normal or abnormal reference range for a measurement.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP ReferenceRange
{
    public:
        /**
         * @brief Constructor.
         */
        ReferenceRange(Range range, const boost::optional<CodedValue>& meaning);

        /**
         * @brief Range. Shall be populated by at least Upper and Lower.
         * @return Range value.
         * @ingroup Mdib
         */
        const Range& range() const;

        /**
         * @brief Indicates the meaning of the reference range.
         * @return Coded value meaning.
         * @ingroup Mdib
         */
        const boost::optional<CodedValue>& meaning() const;

    private:
        Range m_range;
        boost::optional<CodedValue> m_meaning;

};

/**
 * @brief Sequence of \ref ReferenceRange "referenced ranges".
 */
using ReferenceRanges = std::vector<ReferenceRange>;

}
