#pragma once

#include <Framework/Log/Public/Message.h>

namespace DFL
{
namespace Log
{
namespace UnitTest
{
class Monitor
{
    public:
        DFL::Log::Message operator()(const DFL::Log::Message& m)
        {
            m_monitorCalled = true;
            return m;
        }
        void resetMonitor()
        {
            m_monitorCalled = false;
        }
        bool called() const
        {
            return m_monitorCalled;
        }
    private:
        bool m_monitorCalled = false;
};
}
}
}
