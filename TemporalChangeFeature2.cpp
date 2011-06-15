/*
 * File:   TemporalChangeFeature2.cpp
 * Author: zoizoi
 *
 * Created on 09 February 2011, 20:07
 */

#include "TemporalChangeFeature2.h"

TemporalChangeFeature2::TemporalChangeFeature2(float weight, OVASControl* oc) : Feature(weight, oc) {
    prevFrameData=new float*[oc->geoSphere->getNumVs()]();
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

TemporalChangeFeature2::TemporalChangeFeature2(const TemporalChangeFeature2& orig) {
}

TemporalChangeFeature2::~TemporalChangeFeature2() {
}

void TemporalChangeFeature2::scoreFeature(GeoPoint* view) {
    //    if(oc->AreaDone[oc->currentStep]==false){
    //        Feature::scoreFeature2(view);
    //    }

    float viewRange = 3;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange * view->getz());
    renderWindow->Render();

    int changePix;
    if (oc->currentStep == 0) {
        changePix=0;
        framebuffer->grabData();
        prevFrameData[oc->currentView]=framebuffer->getData();
    } else {
        framebuffer->grabData();
        float* currentData=framebuffer->getData();
        changePix=0;
        
        for(int i=0;i<framebuffer->getLen();i++){
            if(prevFrameData[oc->currentView][i*4]!=currentData[i*4]||prevFrameData[oc->currentView][i*4+1]!=currentData[i*4+1]||prevFrameData[oc->currentView][i*4+2]!=currentData[i*4+2]) changePix++;
        }
        delete prevFrameData[oc->currentView];
        prevFrameData[oc->currentView]=currentData;
        
       //cout<<" elevated "<<dArea<<" from "<< oc->currentStep <<" " << oc->currentView  <<" "<<area<< " "<<prevArea<<endl;
     }
    scoreData[oc->currentStep][oc->currentView]=changePix;
//    if(oc->currentView<4){
//        cout<<oc->currentView<<" recorded changepix "<<changePix<<endl;
//    }


}

