#pragma once

#include <S31/S31CoreExImp.h>

#include <string>

namespace S31::Safety
{

/**
 * @brief Interface to satisfy a dual channel comparator.
 * @details To enable the network layer to check two channels for equality, %DualChannelComparator has to provide \ref DualChannelComparator::isEqual().
 * @ingroup S31Safety
 */
class S31_CORE_EXPIMP DualChannelComparator
{
    public:
        virtual ~DualChannelComparator() = default;

        /**
         * @brief Checks a first channel against the second channel which is represented by this comparator.
         *
         * @param firstChannel The first channel value as it arrives from the network (XML canonical string).
         * @return \c true if \c firstChannel is equal to the second channel, otherwise \c false.
         */
        virtual bool isEqual(const std::string& firstChannel) const = 0;
};

}
