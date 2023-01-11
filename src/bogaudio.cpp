
#include "bogaudio.hpp"
#include "AnalyzerXL.hpp"

Plugin *pluginInstance;


void init(rack::Plugin *p) {
    pluginInstance = p;
    p->addModel(modelAnalyzerXL);
}
