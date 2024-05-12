#pragma once

#include <S31/Safety/Public/DualChannelComparator.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Safety
{

/**
 * @brief Interface to create dual channel comparators.
 *
 * @details Since the first channel and second channel representation in a dual channel transfer differs in representation,
 * the network layer does not know how to build that second channel. Instead, it uses an injected factory instance
 * to create a dual channel comparator from the first channel.
 *
 * @ingroup S31Safety
 */
class S31_CORE_EXPIMP DualChannelFactory
{
    public:
        virtual ~DualChannelFactory() = default;

        /**
         * @brief Comparator factory method.
         * @param dualChannelFirstChannelValue The first channel value to build the comparator from.
         * @return A dual channel comparator that represents the second channel of \c dualChannelFirstChannelValue.
         */
        virtual DFL::NotNull<std::unique_ptr<DualChannelComparator>> createComparator(const std::string& dualChannelFirstChannelValue) const = 0;
};

}
