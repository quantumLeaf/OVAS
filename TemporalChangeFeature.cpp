/* 
 * File:   TemporalChangeFeature.cpp
 * Author: zoizoi
 * 
 * Created on 09 February 2011, 20:07
 */

#include "TemporalChangeFeature.h"

TemporalChangeFeature::TemporalChangeFeature(float weight, OVASControl* oc) : Feature(weight, oc) {
    
    intAreaData = ArrayTools::allocate2DArray<int>(oc->numSteps, oc->geoSphere->getNumVs());
     
    for (int i = 0; i < oc->numSteps; i++) {
        for (int j = 0; j < oc->geoSphere->getNumVs(); j++) {
            intAreaData[i][j] = 0;
        }
    }
    intScoreData=ArrayTools::allocate2DArray<int>(oc->numSteps,oc->geoSphere->getNumVs());
    for(int i=0;i<oc->numSteps;i++){
        for(int j=0;j<oc->geoSphere->getNumVs();j++){
            intScoreData[i][j]=0;

        }
    }
    colourB=1;
    colourG=0;
    colourR=0;
}

TemporalChangeFeature::TemporalChangeFeature(const TemporalChangeFeature& orig) {
}

TemporalChangeFeature::~TemporalChangeFeature() {
}

void TemporalChangeFeature::scoreFeature(GeoPoint* view) {
    //    if(oc->AreaDone[oc->currentStep]==false){
    //        Feature::scoreFeature(view);
    //    }
    intScoreData[0][1]=3;
    intAreaData[oc->currentStep][oc->currentView] = countColour(framebuffer);
    
    if (oc->currentStep == 0) {
        intScoreData[oc->currentStep][oc->currentView] = 0;
    } else {
        int dArea = intAreaData[oc->currentStep][oc->currentView] - intAreaData[oc->currentStep - 1][oc->currentView];
        intScoreData[oc->currentStep][oc->currentView] = abs(dArea);
        cout<<" stored scpre "<<dArea<<endl;
    }


}

