#pragma once

#include <S31/Safety/Public/DualChannelHash.h>

#include <memory>
#include <string>

namespace S31::Safety
{
class DualChannelComparator;
class DualChannelFactory;

/**
 * @brief Reconstruct a comparator based on received network information.
 * @details
 * To reconstruct a dual-channel comparator on the receiving side, the first channel
 * is used as a hint. (The checksum alone is not sufficient to recreate the second channel.)
 * Since it is not allowed to recreate the second channel from the first channel,
 * it must be taken care, that the created comparator matches the received second channel (checksum).
 * Only if this is the case the constructed comparator is valid.
 *
 * @warning Yet it is unclear how to signal a self check failure!
 *
 * @warning This class contains safety-relevant data operations.
 * Be careful when changing code in this class.
 *
 * @ingroup S31Safety
 */
class DualChannelReconstruction
{
    public:
        /**
         * @brief Reconstructs the second channel in user format.
         * @details
         * Uses the passed factory to create a dual-channel comparator based
         * on the first channel (hint only). Before the constructed comparator
         * is returned it is checked against the second channel from the
         * dual-channel container. Only if is matches, the constructed
         * comparator is valid.
         *
         * To ensure, that the program code is not corrupted in RAM, the
         * function includes a self-test.
         *
         * @param firstChannelValue First channel used as hint for creation of the comparator.
         * @param factory Custom user factory for comparator creation.
         * @param dualChannelId Identifier for the dual channel checksum.
         * @param dcHashes Container with all dual-channel information.
         * @return Constructed comparator based on both channels only in case first an second channel matches.
         */
        static std::unique_ptr<DualChannelComparator> constructComparator(
            const std::string& firstChannelValue,
            const DualChannelFactory& factory,
            const DualChannelId& dualChannelId,
            const DualChannelHashes& dcHashes);
};

}
