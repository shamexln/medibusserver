#pragma once

#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Public/Model/Measurement.h>
#include <Framework/Utils/Public/Utf8.h>

#include <utility>

namespace DFL::Mdib
{

/**
 * @brief Single allowed enumeration value.
 */
class AllowedEnumValue
{
    public:
        /**
         * @brief Constructor that sets a value and other members to none.
         */
        AllowedEnumValue(DFL::Locale::Utf8 value);

        /**
         * @brief Full constructor.
         */
        AllowedEnumValue(DFL::Locale::Utf8 value,
                         const boost::optional<CodedValue>& type,
                         const boost::optional<InstanceIdentifier>& identification,
                         const boost::optional<Measurement>& characteristic);

        /**
         * @brief Accepted string value.
         */
        const DFL::Locale::Utf8& value() const;

        /**
         * @brief Semantically describe the allowed value.
         * @return The coded value or \c boost::none if undeclared.
         */
        const boost::optional<CodedValue>& type() const;

        /**
         * @brief Applies an identification to the allowed value.
         * @return The instance identifier or \c boost::none if undeclared.
         */
        const boost::optional<InstanceIdentifier>& identification() const;

        /**
         * @brief Attaches a dimensional measurement to the allowed value.
         * @return The measurement or \c boost::none if undeclared.
         */
        const boost::optional<Measurement>& characteristic() const;

        /**
         * @brief Equal operator compares all members (including descriptive texts).
         * @param rhs Instance to compare with
         * @return \c true in case all members equals.
         */
        bool operator==(const AllowedEnumValue& rhs) const;

        /**
         * @brief Not equal operator compares all members (including descriptive texts).
         * @param rhs Instance to compare with
         * @return \c true in case at least one member does not equal.
         */
        bool operator!=(const AllowedEnumValue& rhs) const;

    private:
        DFL::Locale::Utf8 m_value;
        boost::optional<CodedValue> m_type;
        boost::optional<InstanceIdentifier> m_identification;
        boost::optional<Measurement> m_characteristic;
};

/**
 * @brief A sequence of \ref AllowedEnumValues "allowed enumeration values".
 * @ingroup Mdib
 */
using AllowedEnumValues = std::vector<AllowedEnumValue>;

inline AllowedEnumValue::AllowedEnumValue(DFL::Locale::Utf8 value) :
        m_value(std::move(value)),
        m_type(boost::none),
        m_identification(boost::none),
        m_characteristic(boost::none)
{
}

inline AllowedEnumValue::AllowedEnumValue(DFL::Locale::Utf8 value,
                                          const boost::optional<CodedValue>& type, // NOLINT(modernize-pass-by-value)
                                          const boost::optional<InstanceIdentifier>& identification, // NOLINT(modernize-pass-by-value)
                                          const boost::optional<Measurement>& characteristic) : // NOLINT(modernize-pass-by-value)
        m_value(std::move(value)),
        m_type(type),
        m_identification(identification),
        m_characteristic(characteristic)
{
}

inline const DFL::Locale::Utf8& AllowedEnumValue::value() const
{
    return m_value;
}

inline const boost::optional<CodedValue>& AllowedEnumValue::type() const
{
    return m_type;
}

inline const boost::optional<InstanceIdentifier>& AllowedEnumValue::identification() const
{
    return m_identification;
}

inline const boost::optional<Measurement>& AllowedEnumValue::characteristic() const
{
    return m_characteristic;
}

inline bool AllowedEnumValue::operator ==(const AllowedEnumValue& rhs) const
{
    if (this == &rhs)
    {
        return true;
    }

    return m_value == rhs.m_value
        && m_type == rhs.m_type
        && m_identification == rhs.m_identification
        && m_characteristic == rhs.m_characteristic;
}

inline bool AllowedEnumValue::operator!=(const AllowedEnumValue& rhs) const
{
    return !(*this == rhs);
}

}
