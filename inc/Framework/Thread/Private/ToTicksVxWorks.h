#pragma once

#include <Framework/Chrono/Public/Duration.h>

namespace DFL {
namespace Thread {
namespace Impl {

unsigned int ticksPerSecond();
unsigned int toTicks(
    const Chrono::Milliseconds& milliseconds,
    unsigned int ticksPerSecond);
unsigned int toTicks(
    const Chrono::Milliseconds& milliseconds);

}
}
}
