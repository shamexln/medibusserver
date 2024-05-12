#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/Operation/AbstractOperationDescriptor.h>
#include <Framework/Mdib/Public/Model/Operation/XPathExpressions.h>
#include <string>
#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Abstract description of an operation that is exposed on the \ref Sco and is intended to be used to set a complete state.
 * @ingroup Mdib
 */
class AbstractSetStateOperationDescriptor: public AbstractOperationDescriptor
{
    DFL_MDIB_IMMUTABLE(AbstractSetStateOperationDescriptor)

    public:
        /**
         * @brief Describes a list of members the underlying operation modifies on invocation by means of XPath expressions.
         * @details Semantics:
         *
         * - If the modifiable data list is empty, then all members of the target state shall be modifiable.
         * - The root element of the XPath expressions is the state referenced by \ref AbstractOperationDescriptor::operationTarget
         */
        const XPathExpressions& modifiableData() const;

    protected:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AbstractSetStateOperationDescriptor::modifiableData() "Modifiable data" to empty sequence.
         *
         * \note Also applies defaults from \ref AbstractOperationDescriptor.
         */
        AbstractSetStateOperationDescriptor();

        /**
         * @brief Full constructor with extensions.
         */
        AbstractSetStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                            const boost::optional<CodedValue>& type,
                                            const Handle& operationTarget,
                                            const boost::optional<Duration>& maxTimeToFinish,
                                            const boost::optional<Duration>& invocationEffectiveTimeout,
                                            Retriggerable retriggerable,
                                            AccessLevel accessLevel,
                                            XPathExpressions modifiableData,
                                            ExtensionTypes&& extensions);

    private:
        XPathExpressions m_modifiableData;
};

inline AbstractSetStateOperationDescriptor::AbstractSetStateOperationDescriptor():
        AbstractOperationDescriptor(),
        m_modifiableData(XPathExpressions())
{
}

inline AbstractSetStateOperationDescriptor::AbstractSetStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                                                                const boost::optional<CodedValue>& type,
                                                                                const Handle& operationTarget,
                                                                                const boost::optional<Duration>& maxTimeToFinish,
                                                                                const boost::optional<Duration>& invocationEffectiveTimeout,
                                                                                Retriggerable retriggerable,
                                                                                AccessLevel accessLevel,
                                                                                XPathExpressions modifiableData,
                                                                                ExtensionTypes&& extensions) :
        AbstractOperationDescriptor(safetyClassification,
                                    type,
                                    operationTarget,
                                    maxTimeToFinish,
                                    invocationEffectiveTimeout,
                                    retriggerable,
                                    accessLevel,
                                    std::move(extensions)),
        m_modifiableData(std::move(modifiableData))
{
}

inline const XPathExpressions& AbstractSetStateOperationDescriptor::modifiableData() const
{
    return m_modifiableData;
}

} /* namespace Mdib */
} /* namespace DFL */
