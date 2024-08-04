#pragma once

#include "AnalyzerBase.hpp"
#include "bogaudio.hpp"

extern Model *modelAnalyzerXL;

namespace bogaudio {

struct AnalyzerXL : AnalyzerBase {
    enum ParamsIds {
        CONTROL_A_PARAM, CONTROL_B_PARAM, CONTROL_C_PARAM, CONTROL_D_PARAM,

        SWITCH_A_DC_PARAM, SWITCH_B_DC_PARAM, SWITCH_C_DC_PARAM, SWITCH_D_DC_PARAM,

        SWITCH_NVG_LIGHTER_PARAM, SWITCH_AVERAGE_PARAM, SWITCH_CABLE_COLOR_PARAM,

        CONTROL_LINE_THICKNESS_PARAM, CONTROL_COLOR_PARAM, CONTROL_XXX_PARAM,

        NUM_PARAMS
    };

    enum InputsIds {
        SIGNAL_A_INPUT, SIGNAL_B_INPUT, SIGNAL_C_INPUT, SIGNAL_D_INPUT, NUM_INPUTS
    };

    enum OutputsIds {
        NUM_OUTPUTS
    };

    float _sampleRate = 1000.0f;
    float _smooth = 0.25f;
    AnalyzerCore::Quality _quality = AnalyzerCore::QUALITY_GOOD;
    AnalyzerCore::Window _window = AnalyzerCore::WINDOW_KAISER;

    AnalyzerXL() :
        AnalyzerBase(4, NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
        _skinnable = false;
        configParam(CONTROL_A_PARAM, -1.0f, 1.0f, 0.0f, "Gain A");
        configParam(CONTROL_B_PARAM, -1.0f, 1.0f, 0.0f, "Gain B");
        configParam(CONTROL_C_PARAM, -1.0f, 1.0f, 0.0f, "Gain C");
        configParam(CONTROL_D_PARAM, -1.0f, 1.0f, 0.0f, "Gain D");

        configSwitch(SWITCH_A_DC_PARAM, 0, 1, 0, "DC Removal", {"ON", "OFF"});
        configSwitch(SWITCH_B_DC_PARAM, 0, 1, 0, "DC Removal", {"ON", "OFF"});
        configSwitch(SWITCH_C_DC_PARAM, 0, 1, 0, "DC Removal", {"ON", "OFF"});
        configSwitch(SWITCH_D_DC_PARAM, 0, 1, 0, "DC Removal", {"ON", "OFF"});

        configSwitch(SWITCH_NVG_LIGHTER_PARAM, 0, 1, 0, "DC Removal", {"ON", "OFF"});
        configSwitch(SWITCH_AVERAGE_PARAM, 0, 1, 0, "Show Average", {"ON", "OFF"});
        configSwitch(SWITCH_CABLE_COLOR_PARAM, 0, 1, 0, "Use Cable Colors", {"ON", "OFF"});


        configParam(CONTROL_LINE_THICKNESS_PARAM, -1.0f, 1.0f, 0.0f, "Line Thickness");
        configParam(CONTROL_COLOR_PARAM, -1.0f, 1.0f, 0.0f, "Color Intensity");
        configParam(CONTROL_XXX_PARAM, -1.0f, 1.0f, 0.0f, "Gain C");
    }

    void reset() override;

    void sampleRateChange() override;

    json_t *dataToJson() override;

    void dataFromJson(json_t *root) override;

    void modulate() override;

    void processAll(const ProcessArgs &args) override;
};
}
