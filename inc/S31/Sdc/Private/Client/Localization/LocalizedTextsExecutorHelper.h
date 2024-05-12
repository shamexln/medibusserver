#pragma once

#include <S31/Localization/Public/Common/LocalizedTextReference.h>
#include <S31/Localization/S31Only/Common/LocalizedTextFilter.h>
#include <S31/Sdc/Private/Client/Localization/GetLocalizedTextJob.h>
#include <S31/Sdc/Private/Common/Endpoint/Executor.h>
#include <S31/Utils/Public/Outcome.h>

#include <atomic>

namespace S31::Sdc::Impl::LocalizationImpl::Execution
{

/**
 * @brief Alias for code simplification
 * @ingroup S31SdcClient
 */
using Handler = S31::Utils::OutcomeTypes::HandlerPtr<Sdc::Impl::GetLocalizedTextJobResult>;

/**
 * @name Unique Ids
 * @brief Unique atomic Id.
 * @details Based on atomic unsigned int.
 * @ingroup S31SdcClient
 */
///@{
class UniqueId
{
    public:
        UniqueId();
        friend bool operator==(const UniqueId& lhs, const UniqueId& rhs);
        friend bool operator!=(const UniqueId& lhs, const UniqueId& rhs);
        friend bool operator<(const UniqueId& lhs, const UniqueId& rhs);
    private:
        static std::atomic_uint m_counter;
        unsigned int m_value = 0;
};

class JobId: public UniqueId {};
class TransactionId: public UniqueId {};
///@}

/**
 * @brief Alias for code simplification
 * @ingroup S31SdcClient
 */
using CreateJobCallback = S31::Sdc::Impl::Endpoint::CreateJobCallback<Sdc::Impl::GetLocalizedTextJobResult>;

/**
 * @brief Data of a certain job (representing one http request job)
 * @ingroup S31SdcClient
 */
struct JobData
{
        JobId id;
        Handler handler;
        CreateJobCallback createJobCallback;
        Utils::OutcomeTypes::UntypedHandlerPtr executorHandler;
        S31::Localization::LocalizedTextReferences references;
        S31::Localization::LocalizedTextFilter filter;
};

/**
 * @brief Data of multiple jobs belonging together, transaction.
 * @ingroup S31SdcClient
 */
struct Transaction
{
        DFL::Locale::LanguageTag language;
        std::map<JobId, JobData> jobs;
};

/**
 * @brief Container of transactions.
 * @details
 * @ingroup S31SdcClient
 */
class Transactions
{
    public:
        /// Adds the given transactions
        void add(TransactionId id, Transaction&& t);

        /// @brief Get an existing transaction.
        /// @returns the transaction or nullptr if not found.
        Transaction* transaction(TransactionId transactionId);

        /// @brief Get an existing job.
        /// @returns the job or nullptr if not found.
        JobData* jobData(TransactionId transactionId, JobId jobId);

        /// @brief Get the job and delete it from the store.
        /// @returns the job or a default object if the job was not found.
        JobData extractJobData(TransactionId transactionId, JobId jobId);

        /// Deletes the job.
        void deleteJobData(TransactionId transactionId, JobId jobId);

        /// Deletes the transaction.
        void deleteTransaction(TransactionId transactionId);

    private:
        std::map<TransactionId, Transaction> m_data;
};

inline UniqueId::UniqueId():
    m_value(++UniqueId::m_counter)
{
}

inline bool operator==(const UniqueId& lhs, const UniqueId& rhs)
{
    return lhs.m_value == rhs.m_value;
}

inline bool operator!=(const UniqueId& lhs, const UniqueId& rhs)
{
    return lhs.m_value != rhs.m_value;
}

inline bool operator<(const UniqueId& lhs, const UniqueId& rhs)
{
    return lhs.m_value < rhs.m_value;
}

inline void Transactions::add(TransactionId id, Transaction&& t)
{
    m_data[id] = std::move(t);
}

inline Transaction* Transactions::transaction(TransactionId transactionId)
{
    auto it = m_data.find(transactionId);
    if (it != m_data.end())
    {
        return &it->second;
    }
    return nullptr;
}

inline JobData* Transactions::jobData(TransactionId transactionId, JobId jobId)
{
    if (auto* t = transaction(transactionId))
    {
        auto it = t->jobs.find(jobId);
        if (it != t->jobs.end())
        {
            return &it->second;
        }
    }
    return nullptr;
}

inline JobData Transactions::extractJobData(TransactionId transactionId, JobId jobId)
{
    auto* j = jobData(transactionId, jobId);
    if (j)
    {
        auto result = std::move(*j);
        deleteJobData(transactionId, jobId);
        return result;
    }
    return {};
}

inline void Transactions::deleteJobData(TransactionId transactionId, JobId jobId)
{
    if (auto* t = transaction(transactionId))
    {
        t->jobs.erase(jobId);
    }
}

inline void Transactions::deleteTransaction(TransactionId transactionId)
{
    m_data.erase(transactionId);
}

}
