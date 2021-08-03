
#include "bogaudio.hpp"

#include "Analyzer.hpp"
#include "AnalyzerXL.hpp"
#include "Ranalyzer.hpp"


#include "Test.hpp"
#include "Test2.hpp"
#include "TestExpander.hpp"
#include "TestGl.hpp"
#include "TestVCF.hpp"

//NEW_INCLUDES_HERE

Plugin *pluginInstance;


void init(rack::Plugin *p) {
    pluginInstance = p;
    p->addModel(modelAnalyzer);
    p->addModel(modelAnalyzerXL);
    p->addModel(modelRanalyzer);


#ifdef EXPERIMENTAL
    p->addModel(modelLag);
    p->addModel(modelPEQ14XR);
    p->addModel(modelPEQ14XV);
#endif

#ifdef TEST
    p->addModel(modelTest);
    p->addModel(modelTest2);
    p->addModel(modelTestExpanderBase);
    p->addModel(modelTestExpanderExtension);
    p->addModel(modelTestGl);
    p->addModel(modelTestVCF);
#endif

    //NEW_MODELS_HERE
}
