#pragma once

#include "bogaudio.hpp"
#include "disable_output_limit.hpp"

extern Model *modelOffset;

namespace bogaudio {

struct Offset : DisableOutputLimitModule {
    enum ParamIds {
        OFFSET_PARAM,
        SCALE_PARAM,
        NUM_PARAMS
    };

    enum InputIds {
        OFFSET_INPUT,
        SCALE_INPUT,
        IN_INPUT,
        NUM_INPUTS
    };

    enum OutputIds {
        OUT_OUTPUT,
        NUM_OUTPUTS
    };

    bool _offsetFirst = false;


    Offset() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
        configParam(OFFSET_PARAM, -1.0f, 1.0f, 0.0f, "Offset", " V", 0.0f, 10.0f);
        configParam<TenXSquaringParamQuantity>(SCALE_PARAM, -1.0f, 1.0f, 0.31623f, "Scale", "x");
    }


    json_t *toJson(json_t *root) override;
    void fromJson(json_t *root) override;
    int channels() override;
    void processChannel(const ProcessArgs &args, int c) override;
    float knobValue(Param &knob, Input &cv, int c) const;
};

} // namespace bogaudio
