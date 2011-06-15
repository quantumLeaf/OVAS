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
void TopologyFeature::readyRenderer(vtkSmartPointer<vtkRenderer> _renderer) {
    //cout<<" called readyREND!"<<endl;
    //cout<<"ready rend w "<<weight<<endl;
    renderer = _renderer;
    renderWindow = renderer->GetRenderWindow();
    camera = renderer->GetActiveCamera();
    
//    for (it = actors.begin(); it != actors.end(); it++) {
//        renderer->AddActor((*it));
//    }
    framebuffer = new FrameBuffer(renderer->GetRenderWindow());
    
    int redBallCount=0;
    vector<CriticalPoint*>::iterator it;
    for (it=oc->volume4D->criticalPoints->begin();it!=oc->volume4D->criticalPoints->end();it++){
        
      //  if (closeToCriticalIsoVal(oc->currentIso,(*it))){
            redBallCount++;
            renderer->AddActor((*it)->getActor());
            actors->push_back((*it)->getActor());
            cout<<"adding actor for CP at iso "<<oc->currentIso<<" where cp iso is "<<(*it)->value<<" step "<<oc->currentStep<<endl;
      //  }
    }
    cout<<"redball count is "<<redBallCount<<endl;
    
}

void TopologyFeature::climbDown() {
   // vector<CriticalPoint*>::iterator it;
    std::vector< vtkSmartPointer<vtkActor> >::const_iterator it;
    for (it = actors->begin(); it != actors->end(); it++) {
        renderer->RemoveActor((*it));
    }
    delete framebuffer;
    
//    for (it=oc->volume4D->criticalPoints->begin();it!=oc->volume4D->criticalPoints->end();it++){
//        renderer->RemoveActor((*it)->getActor());
//    }
} 

void TopologyFeature::scoreFeature(GeoPoint* view) {
   
    if(weight==0) {
        scoreData[oc->currentStep][oc->currentView]=0;
        return;
    }
    float viewRange = 3;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange * view->getz());
    
    
    //cout<<" active redballs "<<redBallCount<<endl;
    renderWindow->Render();

    int redPix=countColour(colourR,colourG,colourB,framebuffer);
    //cout<<" counted "<<redPix<<endl;
    
    scoreData[oc->currentStep][oc->currentView]=redPix;
    
    
}

bool TopologyFeature::closeToCriticalIsoVal(float currentIso,CriticalPoint* point){
    if(fabs(point->value-currentIso)<(oc->isoStep/2))   return true;
    return false;
}

