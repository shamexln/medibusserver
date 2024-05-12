#pragma once

#include <S31/UseCases/S31Only/IWaveformHandler.h>

namespace S31::Test
{

class WaveformHandlerMock: public IWaveformHandler
{
    public:
        void start() override {}

        void stop() override {}

};

}
