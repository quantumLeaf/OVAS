/* 
 * File:   Analyser4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:51
 */

#include "Analyser4D.h"

Analyser4D::Analyser4D() {

    geoSphere = new GeoSphere();
    featureWeights = new FeatureWeights(this);
    viewEvaluator = new ViewEvaluator(this);
    vol4D=new Volume4D(this);
    a3d = new Analyser3D(this);
    filename = new string("");
    cout<<"vol is "<<vol4D<<endl;
    cout<<"vevol is "<<viewEvaluator->vol<<endl;



}

Analyser4D::Analyser4D(const Analyser4D& orig) {
}

Analyser4D::~Analyser4D() {
}

void Analyser4D::init() {
    cout << "init with fn " << *filename << endl;
    if (*filename != "") {
        loadConfig(*filename);
    }
    a3d->init();

}

void Analyser4D::initFeatures() {

}

void Analyser4D::initAnalyser3D(int step) {

}

void Analyser4D::evalEach3D() {

}

void Analyser4D::loadConfig(string filename) {
    cout << "\tloading config file " << filename << endl;

    ifstream inf;

    inf.open(filename.c_str());
    string line;

    while (getline(inf, line)) {

        if (line.length() != 0) {
            istringstream lineStream(line);
            string command;
            lineStream >> command;
            if (command == "new") {
                cout << " new" << endl;
                float wCurv, wtChange;
                string gsfilename;
                string screenRend;
                string showInterest;
                string ignoreAreaOnCriticalFrameStr;
                float wArea = 1;
                float wbsize = 0; //.25;
                float wTop = 0; //.75;
                lineStream >> dims >> gsfilename >> screenRend >> showInterest >> ignoreAreaOnCriticalFrameStr >> wArea >> wbsize >> wTop >> wCurv >> wtChange;

                featureWeights->areaWeight = wArea;
                featureWeights->topologyWeight = wTop;
                featureWeights->curvatureWeight = wCurv;
                featureWeights->temporalChangeWeight = wtChange;

                if (screenRend == "onScreen") {
                    viewEvaluator->setScreenRenderOn();
                }
                if (ignoreAreaOnCriticalFrameStr == "ignoreAreaOnCriticalFrame") {
                    //frame->ignoreAreaOnCriticalFrame = true;
                    cout << "TODOignoreAreaOnCriticalFrame is On" << endl;
                } else {
                    //frame->ignoreAreaOnCriticalFrame = false;
                }

                if (showInterest == "showInterest") {
                }
                gsfilename = "./sphereData/" + gsfilename;
                geoSphere->loadGeoSphereFile(gsfilename);
            }
            if (command == "iframes") {

                float startParam = 0, endParam = 0;

                lineStream >> startParam >> endParam >> numSteps;
                stepConverter = new StepToParamConverter(startParam, endParam, numSteps);
                cout << "\tiframes start " << startParam << " end " << endParam << " steps " << numSteps << endl;
            }
            if (command == "metaballs") {
                float twist;
                lineStream >> twist;
                cout << "\tNew Metaballs twist:" << twist << endl;
                //MetaballsVol4D*
                Volume4D* vol = dynamic_cast<Volume4D*> (new MetaballsVol4D(dims, dims, dims, numSteps, twist));
                vol->setStepConverter(stepConverter);
                setVolume(vol);
                cout<<"v is "<<a3d->viewEvaluator->vol<<endl;
    cout<<"v is "<<viewEvaluator->vol<<endl;
               
                
            }
        }
    }
}

void Analyser4D::setVolume(Volume4D* vol) {
    vol4D = vol;

//    cout<<"vol is "<<vol4D<<endl;
//    cout<<"set vol in a3dvevol is "<<a3d->viewEvaluator->vol<<endl;
//    cout<<"vevol is "<<viewEvaluator->vol<<endl;

}

void Analyser4D::analyse() {
    init();
    cout << "analysing all " << numSteps << "steps" << endl;
    for (int i = 0; i < numSteps; i++) {
        vol4D->setToStep(i);
        vol4D->updateActor();
        
        a3d->evalEachView();
    }
}

void Analyser4D::testDepts() {

}