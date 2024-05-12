#pragma once

#include <Framework/Mdib/Private/ErrorHandles.h>
#include <Framework/Mdib/Public/WriteResult.h>

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Definition of a result status that comes from any MDIB access write operation.
 *
 * This enumeration relates to @ref WriteStatus. This enum here is more about operations over a part of
 * change set.
 */
enum class MdibAccessHelperWriteStatus
{
    Success,                        //!< %Operation succeed, all elements of the processed part of the change set are handled
    SuccessNoEntitiesProcessed,     //!< %Operation succeeded but the processed part of the changes set was empty
    Fail,                           //!< %Operation failed
    DuplicateHandle,                //!< Duplicate handle
    HandleNotFound,                 //!< A handle was not found
    MdibVersionAlreadySeen,         //!< Try to insert data with older MdibVersion in remote MDIBs
    ConsistencyError,               //!< Consistency problem
    InvalidHandle                   //!< Handle contains empty or invalid characters ( U+0000 to U+0020 or U+FFFD )
};
DFL_ENUM_CLASS_STREAM_OPERATOR(
    MdibAccessHelperWriteStatus,
    (Success)(SuccessNoEntitiesProcessed)(Fail)(DuplicateHandle)(HandleNotFound)(MdibVersionAlreadySeen)(ConsistencyError)(InvalidHandle))

class WriteResult
{
public:
    explicit WriteResult(MdibAccessHelperWriteStatus status);

    WriteResult(MdibAccessHelperWriteStatus status,
                const ErrorHandles& handles);

    WriteResult(MdibAccessHelperWriteStatus status,
                DFL::Mdib::Handle handle,
                DFL::Mdib::Handle parentHandle);

    MdibAccessHelperWriteStatus writeStatus() const noexcept
    {
        return m_writeStatus;
    }
    /// @brief Only error codes can be map consistently.
    WriteStatus asWriteResultFailStatus() const noexcept;

    ErrorHandles handles() const
    {
        return {m_errorHandle, m_errorParentHandle};
    }
    const DFL::Mdib::Handle& handle() const noexcept
    {
        return m_errorHandle;
    }
    const DFL::Mdib::Handle& parentHandle() const noexcept
    {
        return m_errorParentHandle;
    }
    bool isSuccess() const noexcept;

private:
    MdibAccessHelperWriteStatus m_writeStatus;
    DFL::Mdib::Handle m_errorHandle;
    DFL::Mdib::Handle m_errorParentHandle;
};

}
}
}
