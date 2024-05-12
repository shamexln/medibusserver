#pragma once

#include <Framework/Mdib/Public/Model/Handle.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Identifies a handle and parent handle involved in an error situation.
 * @ingroup Mdib
 */
class ErrorHandles
{
public:
    ErrorHandles() = default;
    ErrorHandles(DFL::Mdib::Handle handle, DFL::Mdib::Handle parentHandle)
        : m_handle(std::move(handle))
        , m_parentHandle(std::move(parentHandle))
    {
    }
    const DFL::Mdib::Handle& handle() const noexcept
    {
        return m_handle;
    }
    const DFL::Mdib::Handle& parentHandle() const noexcept
    {
        return m_parentHandle;
    }

private:
    DFL::Mdib::Handle m_handle;
    DFL::Mdib::Handle m_parentHandle;
};
}
}
}
