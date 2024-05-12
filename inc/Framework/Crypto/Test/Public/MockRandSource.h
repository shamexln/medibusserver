#pragma once

#include <Framework/Crypto/Public/RandomDeviceResultType.h>
#include <Framework/Crypto/Public/Registry.h>

#include <Framework/Utils/Public/StateSaver.h>

namespace DFL
{
namespace Crypto
{
namespace Test
{
/**
 * @brief Exchanges the randsource of @ref DFL::Crypto::RandomDevice with one
 * that always returns the given value.
 *
 * @snippet Crypto/Test/UnitTest/TestUtils/TestMockRandSource.cpp exchangeSource
 *
 * @ingroup Crypto
 */
class MockRandSource
{
public:
    /**
     * @brief Remembers current randsource and installs a new one which always
     * returns given value.
     */
    explicit MockRandSource(RandomDeviceResultType returnValue = 0)
        : m_stateSaver{Registry::randSource(),
                       [](const Registry::RandSource& rs) {
                           Registry::randSource(rs);
                       }}
        , m_valueSaver{value(), [](RandomDeviceResultType v) { value() = v; }}
    {
        value() = returnValue;
        Registry::randSource(randSource);
    }

private:
    static RandomDeviceResultType& value()
    {
        static RandomDeviceResultType v{};
        return v;
    }

    static RandomDeviceResultType randSource()
    {
        return value();
    }

    StateSaver<Registry::RandSource> m_stateSaver;
    StateSaver<RandomDeviceResultType> m_valueSaver;
};
}
}
}
