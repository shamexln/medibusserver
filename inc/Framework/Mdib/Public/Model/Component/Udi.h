#pragma once

#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Private/HasExtensions.h>

#include <Framework/Utils/Public/SkillBoostSerializable.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/Utf8.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct DeviceIdentifierTag;
struct HumanReadableFormTag;
}

/**
 * @brief Strong typedef of a \ref Udi "UDI" device identifier.
 * @details A mandatory, fixed portion of a UDI that identifies the labeler and the specific version or model of a device.
 * @ingroup Mdib
 */
using DeviceIdentifier = DFL::StrongTypedef<Locale::Utf8, Impl::DeviceIdentifierTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/**
 * @brief Strong typedef of a \ref Udi "UDI" in human readable form as printed on the barcode.
 * @ingroup Mdib
 */
using HumanReadableForm = DFL::StrongTypedef<Locale::Utf8, Impl::HumanReadableFormTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;


/**
 * @brief UDI fragments as defined by the FDA.
 * @details An example UDI in human readable form (GS1 barcode) is
 * "(01)51022222233336(11)141231(17)150707(10)A213B1(21)1234".
 * The "(01)" application identifier identifies the DeviceIdentifier (DI) of the UDI.
 * Thus in the example the DI is "51022222233336".
 * @ingroup Mdib
 */
class Udi: public Impl::HasExtensions
{
    public:
        /**
         * @brief Constructor with empty jurisdiction.
         */
        Udi(DeviceIdentifier deviceIdentifier,
            HumanReadableForm humanReadableForm,
            const InstanceIdentifier& issuer);

        /**
         * @brief Full constructor.
         */
        Udi(DeviceIdentifier deviceIdentifier,
            HumanReadableForm humanReadableForm,
            const InstanceIdentifier& issuer,
            const boost::optional<InstanceIdentifier>& jurisdiction,
            ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief A mandatory, fixed portion of a UDI that identifies the labeler and the specific version or model of a device.
         */
        const DeviceIdentifier& deviceIdentifier() const;

        /**
         * @brief UDI human readable form as printed on the barcode.
         */
        const HumanReadableForm& humanReadableForm() const;

        /**
         * @brief Organization that has issued the UDI.
         */
        const InstanceIdentifier& issuer() const;

        /**
         * @brief Jurisdiction that the UDI is valid for. If no value is defined, then the UDI is not bound to a specific jurisdiction.
         */
        const boost::optional<InstanceIdentifier>& jurisdiction() const;

        /**
         * @brief Equal compare of \ref Udi.
         * @param rhs right value for comparison.
         * @return \c true in case all value are equal.
         */
        bool operator==(const Udi& rhs) const;

        /**
         * @brief Not equal compare of \ref Udi.
         * @param rhs right value for comparison.
         * @return \c true in case all value are not equal.
         */
        bool operator!=(const Udi& rhs) const;

    private:
        DeviceIdentifier m_deviceIdentifier;
        HumanReadableForm m_humanReadableForm;
        InstanceIdentifier m_issuer;
        boost::optional<InstanceIdentifier> m_jurisdiction;
};

/**
 * @brief Sequence of \ref Udi "UDIs".
 * @ingroup Mdib
 */
using Udis = std::vector<Udi>;


inline Udi::Udi(DeviceIdentifier deviceIdentifier,
                HumanReadableForm humanReadableForm,
                const InstanceIdentifier& issuer) : // NOLINT(modernize-pass-by-value)
        m_deviceIdentifier(std::move(deviceIdentifier)),
        m_humanReadableForm(std::move(humanReadableForm)),
        m_issuer(issuer),
        m_jurisdiction()
{
}

inline Udi::Udi(DeviceIdentifier deviceIdentifier,
                HumanReadableForm humanReadableForm,
                const InstanceIdentifier& issuer, // NOLINT(modernize-pass-by-value)
                const boost::optional<InstanceIdentifier>& jurisdiction, // NOLINT(modernize-pass-by-value)
                ExtensionTypes extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_deviceIdentifier(std::move(deviceIdentifier)),
        m_humanReadableForm(std::move(humanReadableForm)),
        m_issuer(issuer),
        m_jurisdiction(jurisdiction)
{
}

inline const DeviceIdentifier& Udi::deviceIdentifier() const
{
    return m_deviceIdentifier;
}

inline const HumanReadableForm& Udi::humanReadableForm() const
{
    return m_humanReadableForm;
}

inline const InstanceIdentifier& Udi::issuer() const
{
    return m_issuer;
}

inline const boost::optional<InstanceIdentifier>& Udi::jurisdiction() const
{
    return m_jurisdiction;
}

inline bool Udi::operator ==(const Udi& rhs) const
{
    return m_deviceIdentifier == rhs.m_deviceIdentifier &&
            m_humanReadableForm == rhs.m_humanReadableForm &&
            m_issuer == rhs.m_issuer &&
            m_jurisdiction == rhs.m_jurisdiction &&
            extensions() == rhs.extensions();
}

inline bool Udi::operator!=(const Udi& rhs) const
{
    return !(*this == rhs);
}

}
}
