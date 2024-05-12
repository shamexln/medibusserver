#pragma once

#include <S31/Safety/Public/Context.h>
#include <S31/Safety/Public/DualChannelHash.h>

#include <utility>

namespace S31::Safety
{

/**
 * @brief Version of \ref S31::Safety::Information in serializable form.
 * @details Instead of having a \ref S31::Safety::DualChannelComparator for
 * the second channel, it is encoded in a vendor independent format (hash)
 * as specified in MDPWS (IEEE 11073-20702-2016).
 * @ingroup S31Safety
 */
class SerializableInformation
{
    public:
        SerializableInformation() = default;

        explicit SerializableInformation(DualChannelHashes dualChannel);
        explicit SerializableInformation(Context context);
        SerializableInformation(Context context, DualChannelHashes dualChannel);

        /**
         * @brief Returns the stored safety context information.
         */
        const Context& context() const;

        /**
         * @brief Returns the stored dual channel information.
         */
        const DualChannelHashes& dualChannel() const;

        /**
         * @brief Checks if there are no context or dual channel information.
         */
        bool empty() const;

    private:
        Context           m_safetyContext;
        DualChannelHashes m_dualChannel;

};

inline SerializableInformation::SerializableInformation(DualChannelHashes dualChannel):
        m_dualChannel(std::move(dualChannel))
{
}

inline SerializableInformation::SerializableInformation(Context context)
    : m_safetyContext(std::move(context))
{
}

inline SerializableInformation::SerializableInformation(Context context, DualChannelHashes dualChannel)
    : m_safetyContext(std::move(context))
    , m_dualChannel(std::move(dualChannel))
{
}

inline bool SerializableInformation::empty() const
{
    return m_safetyContext.empty() && m_dualChannel.empty();
}

inline const Context& SerializableInformation::context() const
{
    return m_safetyContext;
}

inline const DualChannelHashes& SerializableInformation::dualChannel() const
{
    return m_dualChannel;
}

}
