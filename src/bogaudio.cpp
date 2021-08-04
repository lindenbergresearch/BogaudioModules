
#include "bogaudio.hpp"

#include "Analyzer.hpp"
#include "AnalyzerXL.hpp"
#include "Ranalyzer.hpp"

Plugin *pluginInstance;


void init(rack::Plugin *p) {
    pluginInstance = p;

    p->addModel(modelAnalyzer);
    p->addModel(modelAnalyzerXL);
    p->addModel(modelRanalyzer);
}
