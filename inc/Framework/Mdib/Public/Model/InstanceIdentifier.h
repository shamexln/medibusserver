#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Mdib/Public/Model/Root.h>
#include <Framework/Mdib/Private/HasExtensions.h>

#include <boost/optional/optional.hpp>
#include <utility>

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Utils/Public/Utf8.h>

namespace DFL::Mdib
{
/**
 * @brief Strong typedef of a BICEPS instance identifier extension.
 * @ingroup Mdib
 */
using Extension = DFL::StrongTypedef<DFL::Locale::Utf8, struct ExtensionTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Represents an %InstanceIdentifier from BICEPS to identify arbitrary things or objects.
 * @details Example instance identifiers: medical record numbers, order IDs, location IDs, etc.
 *
 * The \ref InstanceIdentifier::root() "root" is used for globally unique identification.
 * If the root is not sufficient for identification, e.g., if it represents an organization, then
 * the \ref InstanceIdentifier::extension() "extension" can be used to distinguish within the root.
 *
 * If no globally unique identifier is available, then the extension field without the root can be
 * used determine instance identifiers in an unknown space.
 *
 * @ingroup Mdib
 */
class InstanceIdentifier: public Impl::HasExtensions
{
    public:
        /**
         * @brief Creates an instance identifier with default BICEPS null-flavor root.
         */
        explicit InstanceIdentifier(Extension identifierExtension);

        /**
         * @brief Creates an instance identifier with default BICEPS null-flavor root.
         */
        InstanceIdentifier(Extension identifierExtension, const boost::optional<CodedValue>& identifierType);

        /**
         * @brief Creates an instance identifier where the root fully qualifies the instance.
         */
        explicit InstanceIdentifier(Root identifierRoot);

        /**
         * @brief Creates an instance identifier where the root fully qualifies the instance.
         */
        InstanceIdentifier(Root identifierRoot, const boost::optional<CodedValue>& identifierType);

        /**
         * @brief Constructs an instance identifier with empty type.
         * @param identifierRoot Root of the instance identifier. Use \ref DFL::Mdib::InstanceIdentifier(const Extension&) in case of an unknown root.
         * @param identifierExtension Extension of the instance identifier. Use \ref DFL::Mdib::InstanceIdentifier(const Root&) in case that the root fully qualifies the instance.
         */
        InstanceIdentifier(Root identifierRoot, Extension identifierExtension);

        /**
         * @brief Constructs an instance identifier.
         * @param identifierRoot Root of the instance identifier. Use \ref DFL::Mdib::InstanceIdentifier(const Extension&) in case of an unknown root.
         * @param identifierExtension Extension of the instance identifier. Use \ref DFL::Mdib::InstanceIdentifier(const Root&) in case that the root fully qualifies the instance.
         * @param identifierType Optional type of an identifier, see \ref InstanceIdentifier::type().
         * @param extensions \ref DFL::Mdib::ExtensionType "Extensions" of any kind
         */
        InstanceIdentifier(Root identifierRoot,
                           Extension identifierExtension,
                           const boost::optional<CodedValue>& identifierType,
                           ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Creates an instance identifier with default BICEPS null-flavor root and empty extension.
         * @deprecated Please use \ref DFL::Mdib::InstanceIdentifier(const Extension&) instead.
         */
        DFL_ATTRIBUTE_DEPRECATED("Replace by type safe variant to distinguish between given root and extension")
        explicit InstanceIdentifier(const Locale::Utf8& identifierExtension);

        /**
         * @brief Constructs an identifier.
         * @deprecated Please use \ref DFL::Mdib::InstanceIdentifier(const Root&, const Extension&) instead.
         * @param identifierRoot Use empty string in case of unknown root.
         * @param identifierExtension Use empty string in case of a root that fully qualifies the instance.
         */
        DFL_ATTRIBUTE_DEPRECATED("Replace by type safe variant to avoid mixing up root and extension")
        InstanceIdentifier(const Locale::Utf8& identifierRoot, const Locale::Utf8& identifierExtension);



        /**
         * @name Identifier Name
         * @brief An identifier might have a localized human-readable name for the namespace represented in the root.
         * @details
         * The identifier name has no computational value. It can never modify the meaning of root.
         * The purpose of an identifier name is to assist an unaided human interpreter of an InstanceIdentifier value to interpret the identifier.
         * Applications SHALL NOT attempt to perform any decision-making, matching, filtering or other processing based on this presence or value of this property.
         * It is for display and development assistance only.
         * All decision logic SHALL be based solely on the root and extension properties.
         */
        ///@{

        /**
         * @brief Add another localized name to the identifier.
         * @param identifierName additional (localized) name
         */
        void addIdentifierName(const LocalizedText& identifierName);

        /**
         * @brief Returns localized name of identifier.
         * @return Container with localized names. (Empty in case of missing name.)
         */
        const LocalizedTexts& identifierNames() const;
        ///@}

        /**
         * @brief Returns the root part of the instance identifier.
         * @return root
         */
        const Root& root() const;

        /**
         * @brief Returns the extension part of the instance identifier.
         * @return extension
         */
        const Extension& extension() const;

        /**
         * @brief Optional type of an identifier.
         * @details Designates the type of the \ref InstanceIdentifier, e.g.,
         * whether it is a %Medical Record Number (MRN), license number,
         * visit number etc.
         */
        const boost::optional<CodedValue>& type() const;

        friend  bool operator==(const InstanceIdentifier& lhs, const InstanceIdentifier& rhs) noexcept;

    private:
        Root m_root;
        Extension m_extension;
        boost::optional<CodedValue> m_type;
        LocalizedTexts m_identifierNames;
};

/**
 * @brief Sequence of InstanceIdentifiers.
 * @ingroup Mdib
 */
using InstanceIdentifiers = std::vector<InstanceIdentifier>;

inline InstanceIdentifier::InstanceIdentifier(Extension identifierExtension) :
        m_root(Root::unknownRoot()),
        m_extension(std::move(identifierExtension)),
        m_type(),
        m_identifierNames()
{
}

inline InstanceIdentifier::InstanceIdentifier(Extension identifierExtension,
                                              const boost::optional<CodedValue>& identifierType) : // NOLINT(modernize-pass-by-value)
        m_root(Root::unknownRoot()),
        m_extension(std::move(identifierExtension)),
        m_type(identifierType),
        m_identifierNames()
{
}

inline InstanceIdentifier::InstanceIdentifier(Root identifierRoot) :
        m_root(std::move(identifierRoot)),
        m_extension(Extension(Locale::Utf8())),
        m_type(),
        m_identifierNames()
{
}

inline InstanceIdentifier::InstanceIdentifier(Root identifierRoot,
                                              const boost::optional<CodedValue>& identifierType) : // NOLINT(modernize-pass-by-value)
        m_root(std::move(identifierRoot)),
        m_extension(Extension(Locale::Utf8())),
        m_type(identifierType),
        m_identifierNames()
{
}

inline InstanceIdentifier::InstanceIdentifier(Root identifierRoot,
                                              Extension identifierExtension) :
        m_root(std::move(identifierRoot)),
        m_extension(std::move(identifierExtension)),
        m_type(),
        m_identifierNames()
{
}

inline InstanceIdentifier::InstanceIdentifier(Root identifierRoot,
                                              Extension identifierExtension,
                                              const boost::optional<CodedValue>& identifierType, // NOLINT(modernize-pass-by-value)
                                              ExtensionTypes extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_root(std::move(identifierRoot)),
        m_extension(std::move(identifierExtension)),
        m_type(identifierType),
        m_identifierNames()
{
}

inline InstanceIdentifier::InstanceIdentifier(const Locale::Utf8& identifierExtension) :
        m_root(Root::unknownRoot()),
        m_extension(Extension(identifierExtension)),
        m_type(),
        m_identifierNames()
{
    //TODO Shouldn't unknown root only be assigned if Extension exists, i.e has length >= 1?
}

inline InstanceIdentifier::InstanceIdentifier(const Locale::Utf8& identifierRoot, const Locale::Utf8& identifierExtension) :
        m_root(Root(Uri(identifierRoot))),
        m_extension(Extension(identifierExtension)),
        m_type(),
        m_identifierNames()
{
}

inline const Root& InstanceIdentifier::root() const
{
    return m_root;
}

inline const Extension& InstanceIdentifier::extension() const
{
    return m_extension;
}

inline void InstanceIdentifier::addIdentifierName(const LocalizedText& identifierName)
{
    m_identifierNames.push_back(identifierName);
}

inline const LocalizedTexts& InstanceIdentifier::identifierNames() const
{
    return m_identifierNames;
}

inline const boost::optional<CodedValue>& InstanceIdentifier::type() const
{
    return m_type;
}

/**
 * @brief Compares two InstanceIdentifier instances.
 * @param lhs value to compare with
 * @param rhs value to compare with
 * @return \c true in case root, extension, and all localized texts are the same
 */
inline bool operator==(const InstanceIdentifier& lhs, const InstanceIdentifier& rhs) noexcept
{
    if (&lhs == &rhs)
    {
        return true;
    }
    return lhs.m_root == rhs.m_root &&
           lhs.m_type == rhs.m_type &&
           lhs.m_identifierNames == rhs.m_identifierNames &&
           lhs.extension() == rhs.extension();
}

/**
 * @brief Compares two InstanceIdentifier instances.
 * @param lhs value to compare with
 * @param rhs value to compare with
 * @return \c true in case root, extension, or any of the localized texts is
 * different
 */
inline bool operator!=(const InstanceIdentifier& lhs, const InstanceIdentifier& rhs) noexcept
{
    return !(lhs == rhs);
}

}
