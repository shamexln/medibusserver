#pragma once

#include <Framework/Crypto/IntegrationTest/ThisProcess.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Config/Public/Config.h>
#include <Framework/Filesystem/Private/Protected/Filesystem.h>
#include <Framework/Persistence/Private/Protected/FileLock.h>
#include <Framework/Thread/Public/AdoptLock.h>
#include <Framework/Thread/Public/LockGuard.h>

#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

namespace DFLTest
{
namespace FileLock
{
const auto maxNumber = 1000;

#if defined(DFL_CONFIG_OS_VXWORKS)
// the path where the vxe is stored (e.g. an nfs-path)
// might not be writable so instead of the current-exe-folder
// we take current-path instead
const auto testRoot = DFL::Filesystem::V2::currentPath();
#else
const auto testRoot = DFL::Filesystem::V2::currentExeFolder();
#endif
const auto testFolder = testRoot / "TestFileLock";
const auto testPath = testFolder / "adjacent_numbers.txt";
const std::string testStr = testPath.string();
const char* const testFileName = testStr.c_str();

inline std::vector<int> readNums()
{
    std::ifstream in{testFileName};
    return {std::istream_iterator<int>{in}, std::istream_iterator<int>{}};
}

inline bool appendNext()
{
    const auto& nums = readNums();

    if (nums.empty())
    {
        return false;
    }
    if (std::find_if(nums.rbegin(), nums.rend(), [](int a) {
            return a >= maxNumber;
        }) != nums.rend())
    {
        return true;
    }

    std::ofstream out{testFileName, std::ios_base::app};
    const auto nextNum = nums.back() + 1;
    out << nextNum << '\n';
    out.flush();
    return false;
}

inline void workerFileLockBlock()
{
    DFL::Persistence::FileLock l{testPath};
    l.lock();
    for (;;)
    {
    }
}

inline void workerWithLock()
{
    // NOLINTNEXTLINE(misc-const-correctness)
    DFL::Persistence::FileLock l{testPath};
    for (;;)
    {
        const DFL::Thread::LockGuard<DFL::Persistence::FileLock> sl{l};
        if (appendNext())
        {
            break;
        }
    }
}

inline void workerWithTryLock()
{
    // NOLINTNEXTLINE(misc-const-correctness)
    DFL::Persistence::FileLock l{testPath};
    for (;;)
    {
        if (l.try_lock())
        {
            const DFL::Thread::LockGuard<DFL::Persistence::FileLock> sl{
                l,
                DFL::Thread::adoptLock};
            if (appendNext())
            {
                break;
            }
        }
    }
}

inline void workerWithTryLockFor()
{
    using namespace DFL::Chrono::Literals;

    // NOLINTNEXTLINE(misc-const-correctness)
    DFL::Persistence::FileLock l{testPath};
    for (;;)
    {
        if (l.try_lock_for(500_ms))
        {
            const DFL::Thread::LockGuard<DFL::Persistence::FileLock> sl{
                l,
                DFL::Thread::adoptLock};
            if (appendNext())
            {
                break;
            }
        }
    }
}
}
}
