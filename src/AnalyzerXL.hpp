#pragma once

#include "bogaudio.hpp"
#include "analyzer_base.hpp"

extern Model *modelAnalyzerXL;

namespace bogaudio {

struct AnalyzerXL : AnalyzerBase {
    enum ParamsIds {
        CONTROLA_PARAM,
        CONTROLB_PARAM,
        CONTROLC_PARAM,
        CONTROLD_PARAM,
        NUM_PARAMS
    };

    enum InputsIds {
        SIGNALA_INPUT,
        SIGNALB_INPUT,
        SIGNALC_INPUT,
        SIGNALD_INPUT,
        NUM_INPUTS
    };

    enum OutputsIds {
        NUM_OUTPUTS
    };

    float _sampleRate = 1000.0f;
    float _smooth = 0.25f;
    AnalyzerCore::Quality _quality = AnalyzerCore::QUALITY_GOOD;
    AnalyzerCore::Window _window = AnalyzerCore::WINDOW_KAISER;


    AnalyzerXL() : AnalyzerBase(8, NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
        _skinnable = false;
        configParam(CONTROLA_PARAM, 0.0f, 1.0f, 1.0f, "CTRL A");
        configParam(CONTROLB_PARAM, 0.0f, 1.0f, 1.0f, "CTRL B");
        configParam(CONTROLC_PARAM, 0.0f, 1.0f, 1.0f, "CTRL C");
        configParam(CONTROLD_PARAM, 0.0f, 1.0f, 1.0f, "CTRL D");
    }


    /**
     * @brief Converts a linear, normalised, scalar value to a RGB encoded 3-Byte color.
     * @param x 0.f .. 1.f
     * @return NVGcolor
     */
    static inline NVGcolor scalar2color(float x, float alpha) {
        // max colors with 3 byte resolution
        constexpr int MAX_COLOR_VAL = 256 * 256 * 256;

        union {
            unsigned char rgb[3] = { 0, 0, 0 };
            unsigned int color;
        };

        color = uint(x * MAX_COLOR_VAL);
        return nvgRGBA(rgb[0], rgb[1], rgb[2], alpha * 255);
    }


    void reset() override;


    void sampleRateChange() override;


    json_t *toJson(json_t *root) override;


    void fromJson(json_t *root) override;


    void modulate() override;


    void processAll(const ProcessArgs &args) override;
};

} // namespace bogaudio
