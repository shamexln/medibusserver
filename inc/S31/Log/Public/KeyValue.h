#pragma once

#include <S31/Log/Private/S31LogExImp.h>

#include <Framework/Format/Public/ToString.h>

#include <string>
#include <vector>

namespace S31::Log
{
/**
 * \brief Container holding a key value pair.
 * \ingroup S31Log
 */
class S31_LOG_EXPIMP KeyValue
{
    public:
        KeyValue(const char* key, const char* value);
        KeyValue(const char* key, std::string value);

        template <class Value>
        KeyValue(const char* key, const Value& value);

        const std::string& key() const;
        const std::string& value() const;
    private:
        std::string m_key;
        std::string m_value;
};

/**
 * \brief Sequence of \ref S31::Log::KeyValue.
 * \ingroup S31Log
 */
using KeyValues = std::vector<KeyValue>;

template<class Value>
KeyValue::KeyValue(const char* key, const Value& value):
        m_key(key ? key: ""),
        m_value(DFL::Format::toString(value))
{
}

}
