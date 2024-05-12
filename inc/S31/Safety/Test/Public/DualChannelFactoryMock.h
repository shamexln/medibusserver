#pragma once

#include <S31/Safety/Public/DualChannelComparator.h>
#include <S31/Safety/Public/DualChannelFactory.h>

#include <memory>

namespace S31::Safety::Test
{

/**
 * @brief Mock implementation for \ref S31::Safety::DualChannelFactory.
 * @ingroup S31Safety
 */
class DualChannelFactoryMock: public Safety::DualChannelFactory
{
    public:
        /**
         * @ingroup S31Safety
         */
        class Value: public S31::Safety::DualChannelComparator
        {
            public:
            virtual bool isEqual(const std::string& value) const;

            std::string m_value;
        };
        DualChannelFactoryMock();
        virtual ~DualChannelFactoryMock();

        DFL::NotNull<std::unique_ptr<S31::Safety::DualChannelComparator>> createComparator(const std::string& dcFirstChannelValue) const override;
};

inline DualChannelFactoryMock::DualChannelFactoryMock()
{
}

inline DualChannelFactoryMock::~DualChannelFactoryMock()
{
}

inline DFL::NotNull<std::unique_ptr<S31::Safety::DualChannelComparator>> DualChannelFactoryMock::createComparator(
        const std::string& dcFirstChannelValue) const
{
    auto dcValue = DFL::asNotNull(std::make_unique<Value>());
    dcValue->m_value = std::string(dcFirstChannelValue.rbegin(), dcFirstChannelValue.rend());
    return dcValue;
}

inline bool DualChannelFactoryMock::Value::isEqual(const std::string& value) const
{
    return m_value == std::string(value.rbegin(), value.rend());
}

}
