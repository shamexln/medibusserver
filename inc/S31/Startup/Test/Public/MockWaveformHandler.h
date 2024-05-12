#pragma once

#include <S31/UseCases/S31Only/IWaveformHandler.h>

namespace S31::Test
{

class MockWaveformHandler: public IWaveformHandler
{
    public:
        void start() override
        {
        }

        void stop() override
        {
        }

};

}
