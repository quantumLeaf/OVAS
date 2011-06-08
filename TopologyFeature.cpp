/*
 * File:   TopologyFeature.cpp
 * Author: zoizoi
 *
 * Created on 09 February 2011, 20:07
 */

#include "TopologyFeature.h"


TopologyFeature::TopologyFeature(float weight, OVASControl* oc) : Feature(weight, oc) {
    
    intScoreData=ArrayTools::allocate2DArray<int>(oc->numSteps,oc->geoSphere->getNumVs());
    for(int i=0;i<oc->numSteps;i++){
        for(int j=0;j<oc->geoSphere->getNumVs();j++){
            intScoreData[i][j]=0;

        }
    }
    colourB=0;
    colourG=0;
    colourR=1;
    pointIsoThreshold=0.3;
    cout<<"new topology feature"<<endl;
}

TopologyFeature::TopologyFeature(const TopologyFeature& orig) {
}

TopologyFeature::~TopologyFeature() {
}

void TopologyFeature::scoreFeature(GeoPoint* view) {
   
    float viewRange = 3;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange * view->getz());
    vector<CriticalPoint*>::iterator it;
    for (it=oc->volume4D->criticalPoints->begin();it!=oc->volume4D->criticalPoints->end();it++){
        if (closeToCriticalIsoVal(oc->currentIso,(*it))){
            renderer->AddActor((*it)->getActor());
            cout<<"adding actor for CP at iso "<<oc->currentIso<<" where cp iso is "<<(*it)->value<<endl;
        }
    }
    renderWindow->Render();

    int redPix=countColour(colourR,colourG,colourB,framebuffer);
    //cout<<" counted "<<redPix<<endl;
    
    scoreData[oc->currentStep][oc->currentView]=redPix;
    for (it=oc->volume4D->criticalPoints->begin();it!=oc->volume4D->criticalPoints->end();it++){
        renderer->RemoveActor((*it)->getActor());
    }
    
}

bool TopologyFeature::closeToCriticalIsoVal(float currentIso,CriticalPoint* point){
    if(fabs(point->value-currentIso)<(oc->isoRangeThreshold))   return true;
    return false;
}

