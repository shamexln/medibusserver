#pragma once

#include <Framework/Chrono/Public/Duration.h>

namespace DFLTest
{
namespace Log
{
namespace UnitTest
{
class MockToLocal
{
public:
    explicit MockToLocal(::DFL::Chrono::Minutes newOffset);
    ~MockToLocal();
};
}
}
}
