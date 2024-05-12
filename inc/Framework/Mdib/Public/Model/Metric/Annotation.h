#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief %Annotation of a metric state value.
 * @details
 * The coded value that describes the annotation of the element.
 * Example: Attach trigger events in waveform curves.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP Annotation: public CodedValue
{
    public:

        /**
         * @brief Explicit constructor with IEEE CF Code
         */
        explicit Annotation(const CodeId& ieeeCfCode);

        /**
         * @brief Constructor with coding system and code ID
         */
        Annotation(const CodingSystem& codingSystem, const CodeId& codeId);

        /**
         * @brief Constructor with coding system, code ID, description and name
         * @note Two extensions parameters are provided since the annotation must initialize both
         * the extensions from its \ref DFL::Mdib::CodedValue "Type" field and its own set of
         * extensions.
         */
        Annotation(const CodingSystem& codingSystem,
                   const CodeId& codeId,
                   const LocalizedTexts& conceptDescription,
                   const Locale::Utf8& symbolicCodeName,
                   CodedValueTranslations translations = {},
                   ExtensionTypes extensions = ExtensionTypes {},
                   ExtensionTypes annotationExtensions = ExtensionTypes {});

        /**
         * @brief Explicit constructor with Coded Value
         */
        explicit Annotation(const CodedValue& cv,
                            ExtensionTypes annotationExtensions = ExtensionTypes {});

        /**
         * @brief Accessor for annotation extensions
         * @details In addition to the \ref DFL::Mdib::ExtensionType "Extensions" from
         * the \ref DFL::Mdib::CodedValue "Type" field, an annotation has its own set
         * of extensions.
         */
        const ExtensionTypes& annotationExtensions() const;

        /**
         * @brief Invalid waveform sample
         * @details Draeger private code maintained in DOORS: /Standards/Dräger medical/Common Draeger Code List
         */
        static const Annotation MDC_EVT_FLAG_INVALID;

        /**
         * @brief Start of inspiration
         */
        static const Annotation MDC_EVT_VENT_CYC_INSP_START;

        /**
         * @brief FLAG_START_OF_EXP
         * @details Draeger private maintained in DOORS: /Standards/Dräger medical/Common Draeger Code List
         */
        static const Annotation MDC_EVT_START_OF_EXP;

        /**
         * @brief FLAG_START_OF_MAN_INSP
         * @details Draeger private code maintained in DOORS: /Standards/Dräger medical/Common Draeger Code List
         */
        static const Annotation MDC_EVT_START_OF_MAN_INSP;

        /**
         * @brief Synchronization event for synchronization of different processes.
         */
        static const Annotation MDC_EVT_SYNCH;

        /**
         * @brief FLAG_START_OF_TRIGGERED
         * @details Draeger private code maintained in DOORS: /Standards/Dräger medical/Common Draeger Code List
         */
        static const Annotation MDC_EVT_START_OF_TRIGGERED;

        /**
         * @brief FLAG_START_OF_SUPPORTED
         * @details Draeger private code maintained in DOORS:/Standards/Dräger medical/Common Draeger Code List
         */
        static const Annotation MDC_EVT_START_OF_SUPPORTED;

        /**
         * @brief Pacer pulse sensed by heart
         */
        static const Annotation MDC_EVT_ECG_PACED_BEAT;

        /**
         * @brief ECG QRS Wave Synchronization
         * @details Draeger private code maintained in DOORS: /Standards/Dräger medical/Common Draeger Code List
         */
        static const Annotation MDC_ECG_WAVC_QRSWAVE_SYNCH;

    private:
         ExtensionTypes m_annotationExtensions;
};

/**
 * @brief Sequence of \ref Annotation.
 * @ingroup Mdib
 */
using Annotations = std::vector<Annotation>;

} /* namespace Mdib */
} /* namespace DFL */
