#pragma once

#include <S31/BicepsXml/S31Only/Report.h>

#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/EnumClass.h>

#include <memory>

namespace S31::Sdc::Impl::Report
{

/**
 * @brief Validity of the %MDIB version of a report in respect to the last already known version.
 * @ingroup S31SdcCommon
 */
enum class ReportVersionValidity
{
    Newer, ///< this should be the normal case: a new incoming report has new %MDIB version
    Older, ///< older version than already known, shall not be applied
    SameOk, ///< same version in allowed cases, can be ignored (description report + state reports)
    SameInvalid, ///< same version, invalid cases
    OtherSequence ///< other %MDIB sequence, cannot be applied
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ReportVersionValidity, (Newer)(Older)(SameOk)(SameInvalid)(OtherSequence))

/**
 * @brief Validity of a %MDIB sequence/instance in respect to the already known reports sequence.
 * @ingroup S31SdcCommon
 */
enum class SequenceValidity
{
    Ok, ///< same sequence, or no sequence known so far
    OtherSequence ///< other %MDIB sequence, cannot be applied
};
DFL_ENUM_CLASS_STREAM_OPERATOR(SequenceValidity, (Ok)(OtherSequence))

/**
 * @brief holds a validity and a reason (text)
 * @details
 * For returning an enum and an explaination.
 * @ingroup S31SdcCommon
 */
template <typename Validity>
class ValidityAndReason
{
    public:
        // NOLINTNEXTLINE(google-explicit-constructor)
        /* implicit */ ValidityAndReason(Validity validity);
        ValidityAndReason(Validity validity, DFL::Locale::Utf8&& reason);

        [[nodiscard]] Validity validity() const noexcept;
        [[nodiscard]] const DFL::Locale::Utf8& reason() const noexcept;

        bool operator==(Validity validity) const noexcept;
        bool operator!=(Validity validity) const noexcept;

    private:
        Validity m_validity;
        DFL::Locale::Utf8 m_reason;
};

/**
 * @brief Result of invoking version tracking.
 * @ingroup S31SdcCommon
 */
using ApplyResult = ValidityAndReason<ReportVersionValidity>;

/**
 * @brief Result of invoking version tracking.
 * @ingroup S31SdcCommon
 */
using ApplySequenceResult = ValidityAndReason<SequenceValidity>;

/**
 * @brief Tracks the MDIB versions of the incoming reports (and initial Mdib for sequence).
 * @details
 * Used to determine for versions of incoming report whether they are new, old, same,...
 *
 * Only for MDIB versions not for other versioning (like descriptor version).
 *
 * This class is not thread-safe.
 *
 * @ingroup S31SdcCommon
 */
class ReportVersionTracker
{
    public:
        ReportVersionTracker();
        ~ReportVersionTracker();

        /**
         * @brief Apply an incoming report.
         * @details
         * The internal version is moved forward if the report is new and has no changed sequence.
         */
        ///@{
        [[nodiscard]] ApplyResult apply(const DescriptorModifications& modifications);
        [[nodiscard]] ApplyResult apply(const StateModifications& modifications);
        ///@}

        /**
         * @brief Applies a the sequence/instance of a Mdib (given by a @ref DFL::Mdib::MdibVersion "version").
         * @details
         * Checks the sequence against already known reports or sets initial sequence.
         * This is used for the initial Mdib sequence/instance or the initially requested constext states' sequence/instance.
         * The @ref DFL::Mdib::MdibVersion given here is only relevant for the MDIB sequence - it has no influence on report version tracking (regarding
         * newer, older, same...).
         * @returns either @c OK or @c OtherSequence.
         */
        [[nodiscard]] ApplySequenceResult applyMdibSequence(const DFL::Mdib::MdibVersion& version);

    private:
        class Impl;
        DFL::NotNull<std::unique_ptr<Impl>> m_impl;
};

template <typename Validity>
ValidityAndReason<Validity>::ValidityAndReason(Validity validity):
    m_validity(validity)
{
}

template <typename Validity>
ValidityAndReason<Validity>::ValidityAndReason(Validity validity, DFL::Locale::Utf8&& reason):
    m_validity(validity),
    m_reason(std::move(reason))
{
}

template <typename Validity>
Validity ValidityAndReason<Validity>::validity() const noexcept
{
    return m_validity;
}

template <typename Validity>
const DFL::Locale::Utf8& ValidityAndReason<Validity>::reason() const noexcept
{
    return m_reason;
}

template <typename Validity>
bool ValidityAndReason<Validity>::operator==(Validity validity) const noexcept
{
    return m_validity == validity;
}

template <typename Validity>
bool ValidityAndReason<Validity>::operator!=(Validity validity) const noexcept
{
    return m_validity != validity;
}

}
