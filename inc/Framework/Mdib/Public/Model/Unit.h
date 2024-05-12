#pragma once

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Unit specialization for CodedValues.
 * @details Use this class for unit based coded values.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP Unit: public CodedValue
{
    public:
        /**
         * @brief Explicit constructor with IEEE CF Code
         */
        explicit Unit(std::string const& ieeeCfCode);

        /**
         * @brief Constructor with IEEE CF Code
         */
        explicit Unit(Locale::Utf8 const& ieeeCfCode);

        /**
         * @brief Constructor with IEEE CF Code
         */
        explicit Unit(CodeId const& ieeeCfCode);

        /**
         * @brief Constructor with coding system and code ID
         */
        Unit(const CodingSystem& codingSystem, const CodeId& codeId);

        /**
         * @brief Constructor with coding system, code ID, descriptions and names
         */
        Unit(const std::string& codingSystemId,
             const std::string& codeId,
             const std::string& versionId,
             const LocalizedTexts& codingSystemName,
             const LocalizedTexts& conceptDescription,
             const std::string& symbolicConceptName,
             ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Explicit constructor with Coded Value
         */
        explicit Unit(const CodedValue& codedValue);

        /**
         * @brief Checks if a ISO/IEEE 11073 unit is given.
         */
        bool hasIeeeUnit() const;

        /**
         * @brief Checks if an IEEEE 11073 unit is used or not
         */
        CodeId asIeeeCf10UnitOrUnspecified() const;

        /// @name Unit Constants
        /// @brief These are are constants for some(!) possible units that are either used in tests
        /// or have some product specific special handling.
        /// @{
        static const Unit UNSPECIFIED; ///< MDC_DIM_NOS
        static const Unit DIMLESS; ///< MDC_DIM_DIMLESS
        static const Unit PERCENT; ///< MDC_DIM_PERCENT
        static const Unit MILLI_SEC; ///< MDC_DIM_MILLI_SEC
        static const Unit MILLI_VOLT; ///< MDC_DIM_MILLI_VOLT
        static const Unit MMHG; ///< MDC_DIM_MMHG
        static const Unit KILO_G; ///< MDC_DIM_KILO_G
        static const Unit CENTI_M; ///< MDC_DIM_CENTI_M = cm
        static const Unit X_INCH; ///< MDC_DIM_INCH
        static const Unit X_M; ///< MDC_DIM_X_M = MDC_DIM_M = m = meter
        static const Unit X_G; ///< MDC_DIM_X_G = g = gram
        static const Unit X_LB; ///< MDC_DIM_LB = pound
        static const Unit LITER_PER_MIN; ///< MDC_DIM_X_L_PER_MIN = MDC_DIM_L_PER_MIN = L/min
        static const Unit LITER_PER_SEC; ///< MDC_DIM_X_L_PER_SEC = MDC_DIM_L_PER_SEC = L/s
        static const Unit MILLI_LITER_PER_MIN; ///< MDC_DIM_MILLI_L_PER_MIN = mL/min
        static const Unit HZ; ///< MDC_DIM_HZ = hertz
        static const Unit G_PER_L; ///< MDC_DIM_X_G_PER_L = MDC_DIM_G_PER_L = gram(s) per liter = g/L
        /// @}
};


/**
 * @brief Equal operator compares all members (including descriptive texts).
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case all members equals.
 */
inline bool operator==(const Unit& lhs, const Unit& rhs) noexcept
{
    if (&lhs == &rhs)
    {
        return true;
    }

    return static_cast<const CodedValue&>(lhs) == static_cast<const CodedValue&>(rhs);
}

/**
 * @brief Not equal operator compares all members (including descriptive texts).
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case at least one member does not equal.
 */
inline bool operator!=(const Unit& lhs, const Unit& rhs) noexcept
{
    return !(lhs == rhs);
}

} /* namespace Mdib */
} /* namespace DFL */
