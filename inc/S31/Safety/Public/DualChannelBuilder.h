#pragma once

#include <S31/Safety/Public/DualChannelComparator.h>
#include <S31/Safety/Public/DualChannelHash.h>

#include <memory>

#include <boost/optional/optional.hpp>

namespace S31::Safety
{

/**
 * @brief Calculation of network representation for the second channel.
 * @details
 * Builds the vendor independent network representation of the second channel for
 * safe dual channel communication.
 *
 * The function includes an internal self check for the checksum calculation to detect a
 * RAM modification in the program code relevant for checksum creation.
 *
 * @warning Yet it is unclear how to signal a self check failure!
 *
 * @warning This class contains safety-relevant data operations.
 * Be careful when changing code in this class.
 *
 * @ingroup S31Safety
 */
class DualChannelBuilder
{
    public:
        /**
         * @brief Creates the vendor-independent second channel representation.
         * @details
         * The function takes care that only a checksum will be returned in
         * case it matches both input channels. Furthermore, it has in
         * internal self-check to be sure in memory code modifications do not
         * provide wrong dual-channel representations.
         *
         * @param firstChannelValue String representation of the first channel.
         * @param secondChannelComparator A comparator with the second channel stored internally,
         *        to check the value from the first channel.
         * @return Vendor-independent (SHA1 checksum) representing both channels (both must match).
         */
        static boost::optional<Safety::DualChannelHash> calculateDualChannelRepresentation(
                const std::string& firstChannelValue,
                const S31::Safety::DualChannelComparator& secondChannelComparator);
};

}
