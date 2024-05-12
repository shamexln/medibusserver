#pragma once

#include <S31/Safety/Public/Context.h>
#include <S31/Safety/Public/DualChannel.h>

#include <utility>

namespace S31::Safety
{

/**
 * @brief Data container to encapsulate dual channel and safety context information.
 * @ingroup S31Safety
 */
class Information
{
    public:
        /**
         * @brief Constructor.
         */
        Information() = default;

        /**
         * @brief Constructor that accepts both dual channel and safety context information.
         */
        Information(Context safetyContext, DualChannel dualChannel);

        /**
         * @brief Constructor that sets safety context information only.
         */
        explicit Information(Context safetyContext);

        /**
         * @brief Constructor that sets dual channel information only.
         */
        explicit Information(DualChannel dualChannel);

        /**
         * @brief Returns the stored safety context information.
         */
        const Context& context() const;

        /**
         * @brief Returns the stored dual channel information.
         */
        const DualChannel& dualChannel() const;

    private:
        Context m_safetyContext;
        DualChannel m_dualChannel;
};

inline Information::Information(Context safetyContext, DualChannel dualChannel) :
        m_safetyContext(std::move(safetyContext)),
        m_dualChannel(std::move(dualChannel))
{
}

inline Information::Information(Context safetyContext) :
        m_safetyContext(std::move(safetyContext)),
        m_dualChannel()
{
}

inline Information::Information(DualChannel dualChannel) :
        m_safetyContext(),
        m_dualChannel(std::move(dualChannel))
{
}

inline const Context& Information::context() const
{
    return m_safetyContext;
}

inline const DualChannel& Information::dualChannel() const
{
    return m_dualChannel;
}

}
