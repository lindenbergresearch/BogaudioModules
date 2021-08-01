#pragma once

#include "bogaudio.hpp"
#include "dsp/filters/utility.hpp"
#include "dsp/signal.hpp"

using namespace bogaudio::dsp;

extern Model *modelLmtr;

namespace bogaudio {

struct Lmtr : BGModule {
    enum ParamsIds {
        THRESHOLD_PARAM,
        OUTPUT_GAIN_PARAM,
        KNEE_PARAM,
        NUM_PARAMS
    };

    enum InputsIds {
        LEFT_INPUT,
        RIGHT_INPUT,
        THRESHOLD_INPUT,
        OUTPUT_GAIN_INPUT,
        NUM_INPUTS
    };

    enum OutputsIds {
        LEFT_OUTPUT,
        RIGHT_OUTPUT,
        NUM_OUTPUTS
    };


    struct Engine {
        float thresholdDb = 0.0f;
        float outGain = -1.0f;
        float outLevel = 0.0f;
        float lastEnv = 0.0f;

        bogaudio::dsp::SlewLimiter attackSL;
        bogaudio::dsp::SlewLimiter releaseSL;
        RootMeanSquare detector;
        Compressor compressor;
        Amplifier amplifier;
        Saturator saturator;

        void sampleRateChange();
    };


    static constexpr float defaultAttackMs = 150.0f;
    static constexpr float maxAttackMs = 5000.0f;
    static constexpr float defaultReleaseMs = 600.0f;
    static constexpr float maxReleaseMs = 20000.0f;

    Engine *_engines[maxChannels]{};
    bool _softKnee = true;
    float _attackMs = defaultAttackMs;
    float _releaseMs = defaultReleaseMs;
    float _thresholdRange = 1.0f;


    struct ThresholdParamQuantity : ParamQuantity {
        float getDisplayValue() override;
        void setDisplayValue(float v) override;
    };


    Lmtr() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
        configParam<ThresholdParamQuantity>(THRESHOLD_PARAM, 0.0f, 1.0f, 0.8f, "Threshold", " dB");
        configParam(OUTPUT_GAIN_PARAM, 0.0f, 1.0f, 0.0f, "Output gain", " dB", 0.0f, 24.0f);
        configParam(KNEE_PARAM, 0.0f, 1.0f, 0.0f, "Knee");
    }


    void sampleRateChange() override;
    json_t *toJson(json_t *root) override;
    void fromJson(json_t *root) override;
    bool active() override;
    int channels() override;
    void addChannel(int c) override;
    void removeChannel(int c) override;
    void modulate() override;
    void modulateChannel(int c) override;
    void processChannel(const ProcessArgs &args, int c) override;
};

} // namespace bogaudio
