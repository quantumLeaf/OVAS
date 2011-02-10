/* 
 * File:   Analyser4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:51
 */

#include "Analyser4D.h"

Analyser4D::Analyser4D() {
    oc=new OVASControl();
    oc->geoSphere = new GeoSphere();
    oc->geoSequence=new GeoSequence(oc->geoSphere);
    oc->features=new vector<Feature*>();
    oc->viewEvaluator = new ViewEvaluator(oc);
   // oc->volume4D=new Volume4D(oc);
    oc->a3d = new Analyser3D(oc);
    oc->filename = new string("");
}

Analyser4D::Analyser4D(const Analyser4D& orig) {
}

Analyser4D::~Analyser4D() {
}

void Analyser4D::init() {
    cout << "init with fn " << *oc->filename << endl;
    if (*oc->filename != "") {
        loadConfig(*oc->filename);
    }
    oc->a3d->init();

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
                lineStream >> dims >> gsfilename >> screenRend >> wArea >> wbsize >> wTop >> wCurv >> wtChange;
                
                oc->features->push_back(new Feature(wArea,oc));
                oc->features->push_back(new Feature(wTop,oc));
                oc->features->push_back(new Feature(wCurv,oc));
                oc->features->push_back(new TemporalChangeFeature(wtChange,oc));

                if (screenRend == "onScreen") {
                    oc->viewEvaluator->setScreenRenderOn();
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
                oc->geoSphere->loadGeoSphereFile(gsfilename);
            }
            if (command == "iframes") {

                float startParam = 0, endParam = 0;

                lineStream >> startParam >> endParam >> numSteps;
                oc->stepToParamConverter = new StepToParamConverter(startParam, endParam, numSteps);
                cout << "\tiframes start " << startParam << " end " << endParam << " steps " << numSteps << endl;
            }
            if (command == "metaballs") {
                float twist;
                lineStream >> twist;
                cout << "\tNew Metaballs twist:" << twist << endl;
                //MetaballsVol4D*
                 
                oc->numSteps=numSteps;
                oc->xDim=oc->yDim=oc->zDim=dims;
                oc->volume4D = dynamic_cast<Volume4D*> (new MetaballsVol4D(oc,twist));
            }
        }
    }
}

void Analyser4D::analyse() {
    init();
  
    cout << "analysing all " << numSteps << "steps" << endl;
    for (int i = 0; i < numSteps; i++) {
        oc->volume4D->setToStep(i);
        oc->volume4D->updateActor();      
        oc->a3d->evalEachView();
    }
}

void Analyser4D::testDepts() {

}