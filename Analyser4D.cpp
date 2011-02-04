/* 
 * File:   Analyser4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:51
 */

#include "Analyser4D.h"
#include "GeoSphere.h"
#include "Analyser3D.h"
#include "ViewEvaluator.h"

Analyser4D::Analyser4D() {
    
    geoSphere=new GeoSphere();
    featureWeights=new FeatureWeights();
    viewEvaluator=new ViewEvaluator(featureWeights,vol4D);
    
}

Analyser4D::Analyser4D(const Analyser4D& orig) {
}

Analyser4D::~Analyser4D() {
}

void Analyser4D::initFeatures() {

}

void Analyser4D::initAnalyser3D(int step) {

}

void Analyser4D::evalEach3D() {

}

void Analyser4D::loadConfig(string filename) {
    cout << "loading config file " << filename << endl;

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

                float wCurv,wtChange;
                string gsfilename;
                string screenRend;
                string showInterest;
                string ignoreAreaOnCriticalFrameStr;
                float wArea = 1;
                float wbsize = 0; //.25;
                float wTop = 0; //.75;
                lineStream >> dims >> gsfilename >> screenRend >> showInterest >> ignoreAreaOnCriticalFrameStr >> wArea >> wbsize >> wTop >> wCurv >> wtChange;

                featureWeights->areaWeight=wArea;
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
                    //frame->showInterestInOutput = true;
                } else {
                    //frame->showInterestInOutput = false;
                }
                gsfilename="./sphereData/"+gsfilename;
                geoSphere->loadGeoSphereFile(gsfilename);
                //frame->initFrame(dims, rsphere);

                //move to init
                a3d=new Analyser3D(geoSphere);
                a3d->setViewEvaluator(viewEvaluator);

            }
             if (command == "iframes") {
                 
                 float startParam=0,endParam=0;
                 
                lineStream >> startParam >> endParam >> numSteps;
                stepConverter=new StepToParamConverter(startParam,endParam,numSteps);
                cout<<"iframes start "<<startParam<<" end "<<endParam<<" steps "<<numSteps<<endl;
            }
            if (command == "metaballs") {
                float twist;
                lineStream >>twist;
                cout<<"New Metaballs twist:"<<twist<<endl;
                 MetaballsVol4D* vol=new MetaballsVol4D(dims,dims,dims,numSteps,twist);
                 vol->setStepConverter(stepConverter);
                 setVolume(vol);
             }
        }
    }
}

void Analyser4D::setVolume(Volume4D* vol){
    vol4D=vol;
}

void Analyser4D::analyse(){
   
    cout<<"analysing all "<<numSteps<<"steps"<<endl;
    for(int i=0;i<numSteps;i++){
        vol4D->setToStep(i);
        
        vol4D->updateActor();

        a3d->evalEachView();
    }
}