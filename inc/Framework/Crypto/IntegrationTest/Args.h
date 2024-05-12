#pragma once

namespace Args
{
const char* const testWait = "test-wait";
const char* const testWaitDesc = "test Process::wait";

const char* const testWaitFor = "test-wait-for";
const char* const testWaitForDesc = "test Process::wait_for";

const char* const testFileLockBlock = "test-file-lock-block";
const char* const testFileLockBlockDesc = "test FileLock blocks access to file";

const char* const testFileLockLock = "test-file-lock-lock";
const char* const testFileLockLockDesc = "test FileLock::lock";

const char* const testFileLockTryLock = "test-file-lock-try-lock";
const char* const testFileLockTryLockDesc = "test FileLock::try_lock";

const char* const testFileLockTryLockFor = "test-file-lock-try-lock-for";
const char* const testFileLockTryLockForDesc = "test FileLock::try_lock_for";
}
