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
    numViews = oc->geoSphere->getNumVs();
    numSteps = oc->numSteps;
    infoSheet = new InfoSheet(oc);
    

    vector<Feature*>::iterator it;
    
    float* featureStepData;
    //cout<<" Feature size: "<<features->size()<<endl;
    for (int step = 0; step < numSteps; step++) {
        float* aggragatedStepData = new float[numViews];
        for (int i = 0; i < numViews; i++) {
            aggragatedStepData[i] = 0;
        }
        
        for (it = features->begin(); it != features->end(); it++) {
            featureStepData = (*it)->getEvaluatedStepData(step);
            
            for (int view = 0; view < numViews; view++) {
                
                aggragatedStepData[view] += featureStepData[view];
                
               
            //    if(view<4) cout<<" for view "<<view<<" data : "<<aggragatedStepData[view]<<endl;
            }
            
            delete [] featureStepData;
        }
        infoSheet->addTimeInfo(aggragatedStepData);
      //  cout<<"added data starting with "<<aggragatedStepData[0]<<" "<<aggragatedStepData[1]<<endl;
    }
}

InfoData::InfoData(const InfoData& orig) {

}

InfoData::~InfoData() {
}

int* InfoData::findOptimalPath() {
    string filename=string("./lastestTempData/info.data");
    
    
    infoSheet->outputInfoData(filename.c_str());
    //infoSheet->loadInfo("thisData.txt");

    //infoSheet->calcMaxInfo();
    int* path=infoSheet->findPath();
    return path;
}


int* InfoData::findBestViews(){
    int* bvs=infoSheet->returnBestViews();
    return bvs;
}