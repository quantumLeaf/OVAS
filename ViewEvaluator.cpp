/* 
 * File:   ViewEvaluator.cpp
 * Author: zoizoi
 * 
 * Created on 03 February 2011, 22:05
 */

#include "ViewEvaluator.h"


ViewEvaluator::ViewEvaluator() {
}

ViewEvaluator::ViewEvaluator(OVASControl* o) {
    oc=o;
    renderer=vtkSmartPointer<vtkRenderer>::New();
    renderWindow=vtkSmartPointer<vtkRenderWindow>::New();
    renderer->SetBackground(0, 0, 0);
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(300, 300);
    camera = vtkSmartPointer<vtkCamera>::New();
    renderer->SetActiveCamera(camera);
    //hack
    renderWindow->SetOffScreenRendering(false);
    renderer->SetBackground(0, 0, 0); // Background color dark red

    camera->SetFocalPoint(0.5, 0.5, 0.5);
    camera->SetParallelProjection(1);
    camera->SetClippingRange(0,8);
}

ViewEvaluator::ViewEvaluator(const ViewEvaluator& orig) {
}

ViewEvaluator::~ViewEvaluator() {
}

void ViewEvaluator::init(){
    renderer->AddActor(oc->volActor);
}
void ViewEvaluator::readyFeatures(){
    vector<Feature*>::iterator it;
    for (it=oc->features->begin();it!=oc->features->end();it++){
        Feature* a=*(it);
        (*it)->readyRenderer(renderer);
     }
}

void ViewEvaluator::climbDownFeatures(){
    oc->currentView=0;
    vector<Feature*>::iterator it;
    for (it=oc->features->begin();it!=oc->features->end();it++){
        (*it)->climbDown();
     }
}
void ViewEvaluator::evaluate(GeoPoint* view){
    vector<Feature*>::iterator it;
    
    for (it=oc->features->begin();it!=oc->features->end();it++){
        (*it)->scoreFeature(view);

        
    }
    oc->currentView++;

   
}


void ViewEvaluator::renderThisView(GeoPoint* view){
    
    float viewRange = 3;
    
//    testVol4D* tv=new testVol4D();
//    tv->testCVal(vol);
//    renderer->AddActor(vol->getVolActor());
    //tv->testActor(vol->getVolActor());
    //cout<<"from "<<view->getx()<<" "<<view->gety()<<" "<<view->getz()<<" "<<endl;
//    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange *  view->getz());
//   // renderWindow->Render();
//    vtkSmartPointer<vtkRenderer> rendere =
//            vtkSmartPointer<vtkRenderer>::New();
//    vtkSmartPointer<vtkRenderWindow> renderWindo =
//            vtkSmartPointer<vtkRenderWindow>::New();
//    rendere->SetBackground(0, 0, 0);
//    renderWindo->AddRenderer(rendere);
//    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//            vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    renderWindowInteractor->SetRenderWindow(renderWindo);
//
//    //Add the actors to the scene
//    rendere->AddActor(oc->volActor);
//    rendere->SetBackground(0.3, 0, 0); // Background color dark red
//
//    //Render and interact
//    renderWindo->Render();
//    renderWindowInteractor->Start();


}