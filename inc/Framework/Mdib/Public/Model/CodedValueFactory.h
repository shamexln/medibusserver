#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/Metric/Annotation.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Factory for coded values (in common coding systems).
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP CodedValueFactory
{
    public:
        /**
         * @brief Creates a ISO/IEEE 11073 %CodedValue.
         */
        static CodedValue create11073cfCode(const std::string& cfCode);

        /**
         * @brief Creates a ISO/IEEE 11073 %CodedValue.
         */
        static CodedValue create11073cfCode(const Locale::Utf8& cfCode);

        /**
         * @brief Creates a ISO/IEEE 11073 %CodedValue.
         */
        static CodedValue create11073cfCode(const CodeId& cfCode);

        /**
         * @brief Creates a ISO/IEEE 11073 %Annotation.
         */
        static Annotation create11073Annotation(const std::string& annotationCode);

};

} /* namespace Mdib */
} /* namespace DFL */
