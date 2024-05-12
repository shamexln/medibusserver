#pragma once

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/LocalDateTime.h>

namespace DFL {
namespace Chrono {
namespace UnitTest {

class TestClocksHelper
{
public:
    static Microseconds mockTimeSinceEpoch();
    static LocalDateTime dummyToLocal(const Microseconds&);

    static Microseconds returnValueForMockTimeSinceEpoch;
};

}
}
}
