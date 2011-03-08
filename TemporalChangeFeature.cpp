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
    cout<<"new tc feature"<<endl;
}

TemporalChangeFeature::TemporalChangeFeature(const TemporalChangeFeature& orig) {
}

TemporalChangeFeature::~TemporalChangeFeature() {
}

void TemporalChangeFeature::scoreFeature(GeoPoint* view) {
    //    if(oc->AreaDone[oc->currentStep]==false){
    //        Feature::scoreFeature(view);
    //    }

    float viewRange = 3;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange * view->getz());
    renderWindow->Render();
        
    int result,dArea;
    if (oc->currentStep == 0) {
        result=0;
    } else {

        //#TD does not recycle area calc #inefficiency
        int area=countColour(framebuffer);
        intAreaData[oc->currentStep][oc->currentView]=area;
        int prevArea=intAreaData[oc->currentStep-1][oc->currentView];
        dArea = area-prevArea;
        result = abs(dArea);
       //cout<<" elevated "<<dArea<<" from "<< oc->currentStep <<" " << oc->currentView  <<" "<<area<< " "<<prevArea<<endl;
     }
    scoreData[oc->currentStep][oc->currentView]=result;
        

}

