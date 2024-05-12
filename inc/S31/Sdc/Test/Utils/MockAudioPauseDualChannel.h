#pragma once

#include <S31/Safety/Public/DualChannelComparator.h>
#include <S31/Safety/Public/DualChannelFactory.h>
#include <memory>

namespace S31
{

/*!
 * \brief Mock implementation of a dual-channel factory that is used by unit test instances
 *
 * Uses reverse string order as second channel representation.
 */
class MockAudioPauseDualChannel: public Safety::DualChannelFactory
{
    public:
        class Value: public Safety::DualChannelComparator
        {
            public:
            virtual bool isEqual(const std::string& value) const;

            std::string value;
        };
        MockAudioPauseDualChannel();
        virtual ~MockAudioPauseDualChannel();

        DFL::NotNull<std::unique_ptr<S31::Safety::DualChannelComparator>> createComparator(const std::string& dcFirstChannelValue) const override;
};

} /* namespace S31 */
