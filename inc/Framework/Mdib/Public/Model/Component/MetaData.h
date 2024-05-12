#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Component/Udi.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Mdib/Private/HasExtensions.h>

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/SkillBoostSerializable.h>
#include <Framework/Utils/Public/Utf8.h>

#include <vector>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct SerialNumberTag;
}

/**
 * @brief Representation of a serial number.
 * @ingroup Mdib
 */
using SerialNumber = DFL::StrongTypedef<Locale::Utf8, Impl::SerialNumberTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/**
 * @brief Sequence of \ref SerialNumber "serial numbers".
 * @ingroup Mdib
 */
using SerialNumbers = std::vector<SerialNumber>;

/*!
 * \brief Class to store \ref Mds meta data.
 * \ingroup Mdib
 */
class MetaData: public Impl::HasExtensions
{
    public:
        /**
         * @brief Empty meta data (optionals and containers are empty).
         */
        MetaData() = default;

        /**
         *@brief Constructor.
         */
        MetaData(const Udis& udis,
                 Locale::Utf8 lotNumber,
                 const LocalizedTexts& manufacturer,
                 boost::optional<Timestamp> manufactureDate,
                 boost::optional<Timestamp> expirationDate,
                 const LocalizedTexts& modelName,
                 Locale::Utf8 modelNumber,
                 SerialNumbers serialNumbers,
                 ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The Unique Device Identification as defined by FDA.
         * @details
         *
         * \note The amount of elements is unbounded in order to support the provision of UDIs from different jurisdictions.
         */
        const Udis& udis() const;

        /**
         * @brief Optional lot number of manufacturer
         */
        const Locale::Utf8& lotNumber() const;

        /**
         * @brief Optional texts that describe the manufacturer name.
         */
        const LocalizedTexts& manufacturer() const;

        /**
         * @brief Optional date when the device was made.
         */
        const boost::optional<Timestamp>& manufactureDate() const;

        /**
         * @brief Optional date and time of expiry of the device (if applicable).
         */
        const boost::optional<Timestamp>& expirationDate() const;

        /**
         * @brief Optional model name.
         */
        const LocalizedTexts& modelName() const;

        /**
         * @brief Empty string if no model number.
         */
        Locale::Utf8 modelNumber() const;

        /**
         * @brief Optional serial numbers of system.
         */
        const SerialNumbers& serialNumbers() const;

    private:
        Udis m_udis;
        Locale::Utf8 m_lotNumber;
        LocalizedTexts m_manufacturer;
        boost::optional<Timestamp> m_manufactureDate;
        boost::optional<Timestamp> m_expirationDate;
        LocalizedTexts m_modelName;
        Locale::Utf8 m_modelNumber;
        SerialNumbers m_serialNumbers;
};

/**
 * @brief Equal compare of \ref MetaData.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are equal.
 */
DFL_MDIB_EXPIMP bool operator==(const MetaData& lhs, const MetaData& rhs);

/**
 * @brief Not equal compare of \ref MetaData.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are not equal.
 */
DFL_MDIB_EXPIMP bool operator!=(const MetaData& lhs, const MetaData& rhs);

inline MetaData::MetaData(const Udis& udis, // NOLINT(modernize-pass-by-value)
                          Locale::Utf8 lotNumber,
                          const LocalizedTexts& manufacturer, // NOLINT(modernize-pass-by-value)
                          boost::optional<Timestamp> manufactureDate,
                          boost::optional<Timestamp> expirationDate,
                          const LocalizedTexts& modelName, // NOLINT(modernize-pass-by-value)
                          Locale::Utf8 modelNumber,
                          SerialNumbers serialNumbers,
                          ExtensionTypes extensions):
        Impl::HasExtensions(std::move(extensions)),
        m_udis(udis),
        m_lotNumber(std::move(lotNumber)),
        m_manufacturer(manufacturer),
        m_manufactureDate(std::move(manufactureDate)),
        m_expirationDate(std::move(expirationDate)),
        m_modelName(modelName),
        m_modelNumber(std::move(modelNumber)),
        m_serialNumbers(std::move(serialNumbers))
{
}

inline const Udis& MetaData::udis() const
{
    return m_udis;
}

inline const Locale::Utf8& MetaData::lotNumber() const
{
    return m_lotNumber;
}

inline const LocalizedTexts& MetaData::manufacturer() const
{
    return m_manufacturer;
}

inline const boost::optional<Timestamp>& MetaData::manufactureDate() const
{
    return m_manufactureDate;
}

inline const boost::optional<Timestamp>& MetaData::expirationDate() const
{
    return m_expirationDate;
}

inline const LocalizedTexts& MetaData::modelName() const
{
    return m_modelName;
}

inline Locale::Utf8 MetaData::modelNumber() const
{
    return m_modelNumber;
}

inline const SerialNumbers& MetaData::serialNumbers() const
{
    return m_serialNumbers;
}

}
}
