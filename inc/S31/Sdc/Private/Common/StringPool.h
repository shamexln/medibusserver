#pragma once

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <list>
#include <memory>
#include <mutex>
#include <string>

namespace S31::Sdc::Impl
{

struct InitialPoolSizeTag;
using InitialPoolSize = DFL::StrongTypedef<unsigned int, InitialPoolSizeTag>;
struct StringSizeTag;
using StringSize = DFL::StrongTypedef<unsigned int, StringSizeTag>;
class StringPool;

/**
 * @brief Class to encapsulate/scope the pooled string
 *          automatically gets string in ctor and releases in dtor
 *          when the string pool size is exceeded non pooled objects are returned
 * @ingroup S31SdcCommon
 */
class PooledString
{
    DFL_NOT_COPYABLE (PooledString)
    public:
        /**
         * create string from pool, will be handed back to pool in dtor
         * @param pool pool to take the string from
         */
        explicit PooledString(DFL::NotNull<std::shared_ptr<StringPool> >& pool);
        ~PooledString();

        DFL::NotNull<std::shared_ptr<std::string>> get() const;
    private:
        DFL::NotNull<std::shared_ptr<StringPool>> m_pool;
        DFL::NotNull<std::shared_ptr<std::string>> m_string;
};
/**
 * @brief Provides pooled strings
 * starts with initial set of strings of given size
 * grows dynamically as required (when the pool is empty and get is called the string grows)
 *
 * @ingroup S31SdcCommon
 */
class StringPool
{
    public:
        /**
         * Create StringPool with given parameters, memory is allocated in ctor
         * @param initialSize number of elements to acquire initially
         * @param elementSize (minimum) size of each string in this pool
         */
        StringPool(InitialPoolSize initialSize, StringSize elementSize);

        /**
         * gets a string from the pool, extends if no free strings are available
         * @return empty string of at least given size
         */
        DFL::NotNull<std::shared_ptr<std::string>> getString();
        /**
         * hand back string into pool
         * @param str string that was previously acquired from pool
         */
        void releaseString(const DFL::NotNull<std::shared_ptr<std::string>>& str);
        /**
         * get number of available strings without new allocation
         * @return number of strings that are available
         */
        size_t capacity();

    private:
        std::list<std::shared_ptr<std::string>> m_availableStrings;
        std::list<std::shared_ptr<std::string>> m_takenStrings;
        std::mutex m_mutex;
        StringSize m_stringSize;
};

}
