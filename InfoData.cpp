/* 
 * File:   InfoData.cpp
 * Author: zoizoi
 * 
 * Created on 15 February 2011, 20:56
 */

#include "InfoData.h"
#include "Feature.h"
#include "ImplicitVolume4D.h"

InfoData::InfoData(OVASControl* oc) {
    features = oc->features;
    infoSheet = new InfoSheet(oc);
    numViews = oc->geoSphere->getNumVs();
    numSteps = oc->numSteps;

    vector<Feature*>::iterator it;
    float* aggragatedStepData = new float[numViews];
    float* featureStepData;
    for (int step = 0; step < numSteps; step++) {
        for (int i = 0; i < numViews; i++) {
            aggragatedStepData[i] = 0;
        }
        for (it = features->begin(); it != features->end(); it++) {
            featureStepData = (*it)->getEvaluatedStepData(step);
            for (int view = 0; view < numViews; view++) {
                aggragatedStepData[view] += featureStepData[view];
                
            }
            delete [] featureStepData;
        }
        infoSheet->addTimeInfo(aggragatedStepData);
    }
}

InfoData::InfoData(const InfoData& orig) {

}

InfoData::~InfoData() {
}

int* InfoData::findOptimalPath() {
//    infoSheet->outputInfoData("thisData.txt");
    infoSheet->loadInfo("thisData.txt");

    infoSheet->calcMaxInfo();
    int* path=infoSheet->findPath();
    return path;
}