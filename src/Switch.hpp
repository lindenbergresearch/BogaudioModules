#pragma once

#include "bogaudio.hpp"
#include "save_latch_to_patch.hpp"

extern Model *modelSwitch;

namespace bogaudio {

struct Switch : SaveLatchToPatchModule {
    enum ParamsIds {
        GATE_PARAM,
        LATCH_PARAM,
        NUM_PARAMS
    };

    enum InputsIds {
        GATE_INPUT,
        HIGH1_INPUT,
        LOW1_INPUT,
        HIGH2_INPUT,
        LOW2_INPUT,
        NUM_INPUTS
    };

    enum OutputsIds {
        OUT1_OUTPUT,
        OUT2_OUTPUT,
        NUM_OUTPUTS
    };

    enum LightsIds {
        HIGH1_LIGHT,
        LOW1_LIGHT,
        HIGH2_LIGHT,
        LOW2_LIGHT,
        NUM_LIGHTS
    };

    Trigger _trigger[maxChannels];
    int _high1LightSum = 0;
    int _low1LightSum = 0;
    int _high2LightSum = 0;
    int _low2LightSum = 0;


    Switch() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configParam(GATE_PARAM, 0.0f, 10.0f, 0.0f, "Gate");
        configParam(LATCH_PARAM, 0.0f, 1.0f, 0.0f, "Latch");
    }


    void reset() override;
    int channels() override;
    void channelsChanged(int before, int after) override;
    void modulate() override;
    void processAlways(const ProcessArgs &args) override;
    void processChannel(const ProcessArgs &args, int _c) override;
    void postProcessAlways(const ProcessArgs &args) override;
};

} // namespace bogaudio
