#pragma once

#include <S31/Safety/Public/Information.h>
#include <S31/SetService/Public/Client/OperationInvokerQueue.h>

#include <any>
#include <string>

namespace S31::SetService::Test
{

/**
 * @brief Mock implementation of S31::SetService::OperationInvokerQueue.
 * @ingroup S31SetService
 */
class OperationInvokerQueueMock: public OperationInvokerQueue
{
    public:
        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const Arguments& arguments,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const DFL::Locale::Utf8& stringValue,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const DFL::Mdib::Decimal& decimalValue,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const ProposedContextStates& states,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const ProposedAlertStates& states,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const ProposedAlertSystemState& state,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const ProposedAlertConditionState& state,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const ProposedLimitAlertConditionState& state,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const ProposedAlertSignalState& state,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const ProposedComponentStates& state,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                     const ProposedMetricStates& state,
                     const OperationHandle& handle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        std::shared_ptr<ClientTransactionWriter> transaction() const;
        std::string handle() const;

        template<class T_Data>
        boost::optional<T_Data> data() const;

    private:
        std::any m_data;
        std::string m_handle;
        std::shared_ptr<ClientTransactionWriter> m_transaction;

        template<class T_Data>
        void storeData(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction, const T_Data& data,
                       const OperationHandle& handle,
                       const Safety::Information& safetyInformation,
                       const DFL::Mdib::ExtensionTypes& extensions);

};

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const Arguments& arguments,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, arguments, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const DFL::Locale::Utf8& stringValue,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, stringValue, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const DFL::Mdib::Decimal& decimalValue,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, decimalValue, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const ProposedContextStates& states,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, states, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const ProposedAlertStates& states,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, states, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const ProposedAlertSystemState& state,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, state, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const ProposedAlertConditionState& state,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, state, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const ProposedLimitAlertConditionState& state,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, state, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const ProposedAlertSignalState& state,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, state, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const ProposedComponentStates& state,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData(transaction, state, handle, safetyInformation, extensions);
}

inline void OperationInvokerQueueMock::enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                               const ProposedMetricStates& state,
                                               const OperationHandle& handle,
                                               const Safety::Information& safetyInformation,
                                               const DFL::Mdib::ExtensionTypes& extensions)
{
    storeData<ProposedMetricStates>(transaction, state, handle, safetyInformation, extensions);
}

template<class T_Data>
inline void OperationInvokerQueueMock::storeData(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
                                                 const T_Data& data,
                                                 const OperationHandle& handle,
                                                 const Safety::Information& /*safetyInformation*/,
                                                 const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    m_transaction = transaction.get();
    m_data = data;
    m_handle = handle.get().string();
}

inline std::shared_ptr<ClientTransactionWriter> OperationInvokerQueueMock::transaction() const
{
    return m_transaction;
}
inline std::string OperationInvokerQueueMock::handle() const
{
    return m_handle;
}

template<class T_Data>
boost::optional<T_Data> OperationInvokerQueueMock::data() const
{
    try
    {
        return std::any_cast<T_Data>(m_data);
    }
    catch (std::bad_any_cast&)
    {
        return boost::none;
    }
}

}
