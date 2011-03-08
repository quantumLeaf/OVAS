/* 
 * File:   Feature.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 18:28
 */

#include <limits>

#include "Feature.h"
#include "testVol4D.h"



Feature::Feature(){
   
}
Feature::Feature(float weight,OVASControl* o) : weight(weight),oc(o) {
   
    scoreData=ArrayTools::allocate2DArray<float>(oc->numSteps,oc->geoSphere->getNumVs());
    for(int i=0;i<oc->numSteps;i++){
        for(int j=0;j<oc->geoSphere->getNumVs();j++){
            scoreData[i][j]=0;
        }
    }
    cout<<" scd "<<oc->numSteps<<" "<<oc->geoSphere->getNumVs()<<" "<<scoreData<<endl;
    colourB=1;
    colourG=0;
    colourR=0;
    cout<<"created feature w "<<weight<<endl;
 //   Feature();
}

Feature::Feature(const Feature& orig) {
}

Feature::~Feature() {
}

void Feature::readyRenderer(vtkSmartPointer<vtkRenderer> _renderer) {
    //cout<<"ready rend w "<<weight<<endl;
    renderer = _renderer;
    renderWindow = renderer->GetRenderWindow();
    camera = renderer->GetActiveCamera();
    std::vector< vtkSmartPointer<vtkActor> >::iterator it;
    for (it = actors.begin(); it != actors.end(); it++) {
        renderer->AddActor((*it));
    }
    framebuffer = new FrameBuffer(renderer->GetRenderWindow());
}

void Feature::climbDown() {

    std::vector< vtkSmartPointer<vtkActor> >::const_iterator it;
    for (it = actors.begin(); it != actors.end(); it++) {
        renderer->RemoveActor((*it));
    }
    delete framebuffer;
}

void Feature::scoreFeature(GeoPoint* view) {
    
    float viewRange = 3;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange * view->getz());
    renderWindow->Render();
//     vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//    vtkSmartPointer<vtkRenderWindowInteractor>::New();
//  renderWindowInteractor->SetRenderWindow(renderWindow);

  
 // renderWindowInteractor->Start();
    //vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //renderWindowInteractor->SetRenderWindow(renderWindow);

        //renderWindowInteractor->Start();
   
    scoreData[oc->currentStep][oc->currentView]=countColour(framebuffer);
   
}

int Feature::countColour(float r, float g, float b, FrameBuffer* fb) {
    fb->grabData();

    int count = 0;
    int len = fb->getLen();
    float* data = fb->getData();
    for (int i = 0; i < len; i++) {
        int j = i * 4;
        if (data[j] == r && data[j + 1] == g && data[j + 2] == b) {
            count++;
        }
    }
    fb->delData();

    return count;

}

float* Feature::getEvaluatedStepData(int step){
    //cout<<"weight this is "<<weight<<endl;
    float* data=new float[oc->geoSphere->getNumVs()];
    for(int i=0;i<oc->geoSphere->getNumVs();i++){
        float maxValue = log2(300 * 300);
        float value=scoreData[step][i];
        float contribution = 1, dAFactor=1;
        contribution = weight * (log2(value) / maxValue);
        if (value == 0) contribution = 0;
        data[i]=contribution;
    }
    return data;
}