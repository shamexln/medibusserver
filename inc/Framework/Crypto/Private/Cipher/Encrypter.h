#pragma once

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

#include <memory>
#include <utility>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
class Encrypter
{
public:
    template <class T>
    /*implicit*/ Encrypter(T enc)
        : m_self{std::make_unique<Model<T>>(std::move(enc))}
    {
    }

    void init()
    {
        m_self->init();
    }

    void update(Encoding::BytesView bytes)
    {
        m_self->update(bytes);
    }

    void final()
    {
        m_self->final();
    }

    Encoding::Bytes encrypted()
    {
        return m_self->encrypted();
    }

private:
    class Concept
    {
    public:
        virtual ~Concept() = default;

        virtual void init() = 0;
        virtual void update(Encoding::BytesView bytes) = 0;
        virtual void final() = 0;
        virtual Encoding::Bytes encrypted() = 0;
    };

    template <class T>
    class Model : public Concept
    {
    public:
        explicit Model(T enc)
            : m_enc{std::move(enc)}
        {
        }

        void init() override
        {
            m_enc.init();
        }

        void update(Encoding::BytesView bytes) override
        {
            m_enc.update(bytes);
        }

        void final() override
        {
            m_enc.final();
        }

        Encoding::Bytes encrypted() override
        {
            return m_enc.encrypted();
        }

    private:
        T m_enc;
    };

    std::unique_ptr<Concept> m_self{};
};
}
}
}
