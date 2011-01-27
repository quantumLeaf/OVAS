/* 
 * File:   Analyser4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:51
 */

#include "Analyser4D.h"
#include "GeoSphere.h"

Analyser4D::Analyser4D() {
    areaWeight = 0;
    topologyWeight = 0;
    curvatureWeight = 0;
    temporalChangeWeight = 0;
    geoSphere=new GeoSphere();
    
    
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

void Analyser4D::setAreaWeight(float weight) {
    areaWeight = weight;
}

void Analyser4D::setTemporalChangeWeight(float weight) {
    temporalChangeWeight = weight;
}

void Analyser4D::setTopologyWeight(float weight) {
    topologyWeight = weight;
}

void Analyser4D::setCurvatureWeight(float weight) {
    curvatureWeight = weight;

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
                int dims;
                string gsfilename;
                string screenRend;
                string showInterest;
                string ignoreAreaOnCriticalFrameStr;
                float wArea = 1;
                float wbsize = 0; //.25;
                float wTop = 0; //.75;
                lineStream >> dims >> gsfilename >> screenRend >> showInterest >> ignoreAreaOnCriticalFrameStr >> wArea >> wbsize >> wTop;
                areaWeight = wArea;
                topologyWeight = wTop;


                if (screenRend == "onScreen") {
                    //frame->screenRendOn = true;
                } else {
                    //frame->screenRendOn = false;
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
            }
             if (command == "iframes") {
                 
                 float startParam=0,endParam=0;
                 int numSteps=0;
                lineStream >> startParam >> endParam >> numSteps;
                stepConverter=new StepToParamConverter(startParam,endParam,numSteps);
                cout<<"iframes start "<<startParam<<" end "<<endParam<<" steps "<<numSteps<<endl;
            }
        }
    }
}
