#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Operation/AbstractOperationDescriptor.h>
#include <cstddef>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines the static part of a \ref SetStringOperation.
 * @ingroup Mdib
 */
class SetStringOperationDescriptor: public AbstractOperationDescriptor
{
    DFL_MDIB_IMMUTABLE(SetStringOperationDescriptor)

    public:
        /**
         * @brief Type for the max length member.
         */
        using MaxLength = uint64_t;

        /**
         * @brief Default constructor that set the \ref SetStringOperationDescriptor::maxLength() "maximum length" to none.
         *
         * \note Also applies defaults from \ref AbstractOperationDescriptor.
         */
        SetStringOperationDescriptor();

        /**
         * @brief Full constructor with extensions.
         */
        SetStringOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                     const boost::optional<CodedValue>& type,
                                     const Handle& operationTarget,
                                     const boost::optional<Duration>& maxTimeToFinish,
                                     const boost::optional<Duration>& invocationEffectiveTimeout,
                                     Retriggerable retriggerable,
                                     AccessLevel accessLevel,
                                     const boost::optional<MaxLength>& maxLength,
                                     ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief An optional parameter that gives the maximum length of the input string that is supported by the operation.
         * @return Max string length number or \c boost::none if not defined
         */
        const boost::optional<MaxLength>& maxLength() const;

    private:
        boost::optional<MaxLength> m_maxLength;
};

inline SetStringOperationDescriptor::SetStringOperationDescriptor():
        AbstractOperationDescriptor(),
        m_maxLength(boost::none)
{
}

inline SetStringOperationDescriptor::SetStringOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                                                  const boost::optional<CodedValue>& type,
                                                                  const Handle& operationTarget,
                                                                  const boost::optional<Duration>& maxTimeToFinish,
                                                                  const boost::optional<Duration>& invocationEffectiveTimeout,
                                                                  Retriggerable retriggerable,
                                                                  AccessLevel accessLevel,
                                                                  const boost::optional<MaxLength>& maxLength,
                                                                  ExtensionTypes extensions) :
        AbstractOperationDescriptor(safetyClassification,
                                    type,
                                    operationTarget,
                                    maxTimeToFinish,
                                    invocationEffectiveTimeout,
                                    retriggerable,
                                    accessLevel,
                                    std::move(extensions)),
        m_maxLength(maxLength)
{
}

inline const boost::optional<SetStringOperationDescriptor::MaxLength>& SetStringOperationDescriptor::maxLength() const
{
    return m_maxLength;
}

/**
 * @brief Definition of shared pointer type \ref SetStringOperationDescriptorSharedPtr for descriptor \ref SetStringOperationDescriptor.
 * @ingroup Mdib
 */
using SetStringOperationDescriptorSharedPtr = SharedPtr<SetStringOperationDescriptor>;

} /* namespace Mdib */
} /* namespace DFL */
