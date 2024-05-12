#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/ExtensionType.h>

#include <boost/optional/optional.hpp>

namespace DFL::Mdib::Ext
{
class AlertSignalFlashing;
class CountdownEndTime;
class HighestPresentAlert;
class InvocationPerformedFrom;
class NormalizedWaveform;
class PlaceholderText;
class PriorityChange;
class RetrospectiveAnnotation;
using RetrospectiveAnnotations = std::vector<RetrospectiveAnnotation>;
class SubType;
class SuppressExternalControlAlert;


/**
 * @brief Helper functions for the ParticipantModelExtensions extension.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP ParticipantModelExtensions
{
public:
    /**
     * @brief Converts known extension to MDIB extension type.
     */
    static ExtensionType toExtension(
        const AlertSignalFlashing& alertSignalFlashing);

    /**
     * @brief Converts known extension to MDIB extension type.
     */
    static ExtensionType toExtension(
        const CountdownEndTime& countdownEndTime);

    /**
     * @brief Converts known extension to MDIB extension type.
     */
    static ExtensionType toExtension(
        const InvocationPerformedFrom& invocationPerformedFrom);

    /**
     * @brief Converts known extension to MDIB extension type.
     */
    static ExtensionType toExtension(
        const NormalizedWaveform& normalizedWaveform);

    /**
     * @brief Converts known extension to MDIB extension type.
     */
    static ExtensionType toExtension(
        const PlaceholderText& placeholderText);

    /**
     * @brief Converts known extension to MDIB extension type.
     */
    static ExtensionType toExtension(
        const PriorityChange& priorityChange);

    /**
     * @brief Converts known extension to MDIB extension type.
     */
    static ExtensionType toExtension(
        const HighestPresentAlert& highestPresentAlert);

    /**
     * @brief Converts known extension to MDIB extension type.
     */
    static ExtensionType toExtension(
        const RetrospectiveAnnotations& retrospectiveAnnotations);

    /**
     * @brief Converts known extension to MDIB extension type.
     * @details Note, not all elements of the SubType code are translated into the extension.
     * Namely, Translations and Extensions of the CodedValue are ignored.
     */
    static ExtensionType toExtension(
        const SubType& subType);

    /**
     * @brief Converts known extension to MDIB extension type.
     */
    static ExtensionType toExtension(
        const SuppressExternalControlAlert& suppressExternalControlAlert);

    /**
     * @brief Gets requested known extension from generic type (if matches).
     * @details
     * In case the generic extension represents the known extension (passed as
     * template type), it is returned. Otherwise, \c boost::none will be
     * returned.
     */
    template <class ExtensionType_T>
    static boost::optional<ExtensionType_T> get(const ExtensionType& extension);

    /**
     * @brief Searches for the requested known extension in a sequence of
     * generic extension.
     * @details
     * In case exactly one of the generic extension match the requested known
     * extension, it will be returned. Otherwise \c boost::none is returned.
     */
    template <class ExtensionType_T>
    static boost::optional<ExtensionType_T> get(
        const ExtensionTypes& extensions);

    /**
     * @brief Searches for the requested known extension in a sequence of
     * generic extension.
     * @details
     * All of the generic extensions that match the requested known extension
     * will be returned.
     */
    template <class ExtensionType_T>
    static std::vector<ExtensionType_T> getAll(
        const ExtensionTypes& extensions);

    /**
     * @brief Searches for the requested known extension in the extension of
     * passed (MDIB state or descriptor) type.
     * @details
     * In case exactly one of the generic extension match the requested known
     * extension, it will be returned. Otherwise \c boost::none is returned.
     *
     * An example usage for \ref DFL::Mdib::Ext::AlertSignalFlashing
     * "AlertSignalFlashing":
     * @snippet Mdib/Test/UnitTest/TestParticipantModelExtensions.cpp AlertSignalFlashingUsage
     */
    template <class ExtensionType_T, class Element_T>
    static boost::optional<ExtensionType_T> get(const Element_T& element);

    /**
     * @brief Searches for the requested known extension in the extension of
     * passed (MDIB state or descriptor) type.
     * @details
     * All of the generic extensions that match the requested known extension
     * will be returned.
     *
     * An example usage for \ref DFL::Mdib::Ext::InvocationPerformedFrom
     * "InvocationPerformedFrom":
     * @snippet Mdib/Test/UnitTest/TestParticipantModelExtensions.cpp InvocationPerformedFromUsage
     */
    template <class ExtensionType_T, class Element_T>
    static std::vector<ExtensionType_T> getAll(const Element_T& element);

    /**
     * @brief Adds (or overwrites) the extension in the container.
     * @param container Container where the extension shall be embedded.
     * @param value The extension to add.
     */
    static void setExtension(ExtensionTypes& container,
                             const AlertSignalFlashing& value);

    /**
     * @brief Adds (or overwrites) the extension in the container.
     * @param container Container where the extension shall be embedded.
     * @param value The extension to add.
     */
    static void setExtension(ExtensionTypes& container,
                             const CountdownEndTime& value);

    /**
     * @brief Adds (or overwrites) the extension in the container.
     * @param container Container where the extension shall be embedded.
     * @param value The extension to add.
     */
    static void setExtension(ExtensionTypes& container,
                             const NormalizedWaveform& value);

    /**
     * @brief Adds (or overwrites) the extension in the container.
     * @param container Container where the extension shall be embedded.
     * @param value The extension to add.
     */
    static void setExtension(ExtensionTypes& container,
                             const PlaceholderText& value);

    /**
     * @brief Adds (or overwrites) the extension in the container.
     * @param container Container where the extension shall be embedded.
     * @param value The extension to add.
     */
    static void setExtension(ExtensionTypes& container,
                             const PriorityChange& value);

    /**
     * @brief Adds (or overwrites) the extension in the container.
     * @param container Container where the extension shall be embedded.
     * @param value The extension to add.
     */
    static void setExtension(ExtensionTypes& container,
                             const HighestPresentAlert& value);

    /**
     * @brief Adds (or overwrites) the extension in the container.
     * @param container Container where the extension shall be embedded.
     * @param value The extension to add.
     */
    static void setExtension(ExtensionTypes& container,
                             const RetrospectiveAnnotations& value);

    /**
     * @brief Adds (or overwrites) the extension in the container.
     * @param container Container where the extension shall be embedded.
     * @param value The extension to add.
     */
    static void setExtension(ExtensionTypes& container,
                             const SubType& value);

    /**
     * @brief Adds (or overwrites) the extension in the container.
     * @param container Container where the extension shall be embedded.
     * @param value The extension to add.
     */
    static void setExtension(ExtensionTypes& container,
                             const SuppressExternalControlAlert& value);
};

template <class ExtensionType_T, class Element_T>
boost::optional<ExtensionType_T> ParticipantModelExtensions::get(
    const Element_T& element)
{
    return get<ExtensionType_T>(element.extensions());
}

template <class ExtensionType_T, class Element_T>
std::vector<ExtensionType_T> ParticipantModelExtensions::getAll(
    const Element_T& element)
{
    return getAll<ExtensionType_T>(element.extensions());
}

}
