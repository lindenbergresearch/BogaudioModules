#pragma once

#include "bogaudio.hpp"
#include "dsp/signal.hpp"

using namespace bogaudio::dsp;

extern Model *modelMute8;

namespace bogaudio {

struct Mute8 : BGModule {
    enum ParamsIds {
        MUTE1_PARAM,
        MUTE2_PARAM,
        MUTE3_PARAM,
        MUTE4_PARAM,
        MUTE5_PARAM,
        MUTE6_PARAM,
        MUTE7_PARAM,
        MUTE8_PARAM,
        NUM_PARAMS
    };

    enum InputsIds {
        INPUT1_INPUT,
        INPUT2_INPUT,
        INPUT3_INPUT,
        INPUT4_INPUT,
        INPUT5_INPUT,
        INPUT6_INPUT,
        INPUT7_INPUT,
        INPUT8_INPUT,
        MUTE1_INPUT,
        MUTE2_INPUT,
        MUTE3_INPUT,
        MUTE4_INPUT,
        MUTE5_INPUT,
        MUTE6_INPUT,
        MUTE7_INPUT,
        MUTE8_INPUT,
        NUM_INPUTS
    };

    enum OutputsIds {
        OUTPUT1_OUTPUT,
        OUTPUT2_OUTPUT,
        OUTPUT3_OUTPUT,
        OUTPUT4_OUTPUT,
        OUTPUT5_OUTPUT,
        OUTPUT6_OUTPUT,
        OUTPUT7_OUTPUT,
        OUTPUT8_OUTPUT,
        NUM_OUTPUTS
    };

    enum LightsIds {
        MUTE1_LIGHT,
        MUTE2_LIGHT,
        MUTE3_LIGHT,
        MUTE4_LIGHT,
        MUTE5_LIGHT,
        MUTE6_LIGHT,
        MUTE7_LIGHT,
        MUTE8_LIGHT,
        NUM_LIGHTS
    };

    static const float maxDecibels;
    static const float minDecibels;
    static const float slewTimeMS;

    Amplifier _amplifiers[8][maxChannels];
    bogaudio::dsp::SlewLimiter _slewLimiters[8][maxChannels];
    Trigger _triggers[8][maxChannels];
    bool _latches[8][maxChannels]{};
    bool _latchingCVs = false;


    Mute8() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configParam(MUTE1_PARAM, 0.0f, 3.0f, 0.0f, "Mute 1");
        configParam(MUTE2_PARAM, 0.0f, 3.0f, 0.0f, "Mute 2");
        configParam(MUTE3_PARAM, 0.0f, 3.0f, 0.0f, "Mute 3");
        configParam(MUTE4_PARAM, 0.0f, 3.0f, 0.0f, "Mute 4");
        configParam(MUTE5_PARAM, 0.0f, 3.0f, 0.0f, "Mute 5");
        configParam(MUTE6_PARAM, 0.0f, 3.0f, 0.0f, "Mute 6");
        configParam(MUTE7_PARAM, 0.0f, 3.0f, 0.0f, "Mute 7");
        configParam(MUTE8_PARAM, 0.0f, 3.0f, 0.0f, "Mute 8");
    }


    json_t *toJson(json_t *root) override;
    void fromJson(json_t *root) override;
    void reset() override;
    void sampleRateChange() override;
    void processAll(const ProcessArgs &args) override;
    void stepChannel(int i, bool solo);
};

} // namespace bogaudio
