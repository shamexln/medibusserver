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
class Decrypter
{
public:
    template <class T>
    /*implicit*/ Decrypter(T dec)
        : m_self{std::make_unique<Model<T>>(std::move(dec))}
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

    Encoding::Bytes decrypted()
    {
        return m_self->decrypted();
    }

private:
    class Concept
    {
    public:
        virtual ~Concept() = default;

        virtual void init() = 0;
        virtual void update(Encoding::BytesView bytes) = 0;
        virtual void final() = 0;
        virtual Encoding::Bytes decrypted() = 0;
    };

    template <class T>
    class Model : public Concept
    {
    public:
        explicit Model(T dec)
            : m_dec{std::move(dec)}
        {
        }

        void init() override
        {
            m_dec.init();
        }

        void update(Encoding::BytesView bytes) override
        {
            m_dec.update(bytes);
        }

        void final() override
        {
            m_dec.final();
        }

        Encoding::Bytes decrypted() override
        {
            return m_dec.decrypted();
        }

    private:
        T m_dec;
    };

    std::unique_ptr<Concept> m_self{};
};
}
}
}
