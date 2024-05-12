#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Private/HasExtensions.h>

#include <boost/optional/optional.hpp>

namespace DFL::Mdib
{

/**
 * @brief Possesses a handle name that uniquely identifies the state, which is required if the relation to a descriptor is ambiguous.
 * @ingroup Mdib
 */
class AbstractMultiState: public Impl::HasExtensions
{
    DFL_MDIB_IMMUTABLE(AbstractMultiState)

    public:
        /**
         * @brief A \ref CodedValue that allows to categorize a multi state inside the set of multi states that belong to a descriptor of a certain type.
         * @return Multi-state category or \c boost::none if there is no category available.
         */
        const boost::optional<CodedValue>& category() const noexcept;

    protected:
        /**
         * @brief Default constructor.
         * @details Defaults
         * - \ref AbstractMultiState::category() to none.
         * - \ref AbstractMultiState::extensions() to empty sequence.
         */
        AbstractMultiState();

        /**
         * @brief Full constructor.
         */
        AbstractMultiState(const boost::optional<CodedValue>& category,
                           ExtensionTypes&& extensions);

        /**
         * @brief Protected dtor.
         * @details
         * This data type is used for composition of members only.
         */
        ~AbstractMultiState() = default;
    private:
        boost::optional<CodedValue> m_category;
};

inline AbstractMultiState::AbstractMultiState() :
        m_category(boost::none)
{
}

inline AbstractMultiState::AbstractMultiState(const boost::optional<CodedValue>& category, // NOLINT(modernize-pass-by-value)
                                              ExtensionTypes&& extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_category(category)
{
}

inline const boost::optional<CodedValue>& AbstractMultiState::category()
    const noexcept
{
    return m_category;
}

} /* namespace DFL */
