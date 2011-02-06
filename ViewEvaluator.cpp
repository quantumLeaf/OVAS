/* 
 * File:   ViewEvaluator.cpp
 * Author: zoizoi
 * 
 * Created on 03 February 2011, 22:05
 */

#include "ViewEvaluator.h"


ViewEvaluator::ViewEvaluator() {
}

ViewEvaluator::ViewEvaluator(Analyser4D* a) {
    a4d=a;
    renderer=vtkSmartPointer<vtkRenderer>::New();
    renderWindow=vtkSmartPointer<vtkRenderWindow>::New();
    renderer->SetBackground(0, 0, 0);
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(300, 300);
    camera = vtkSmartPointer<vtkCamera>::New();
    renderer->SetActiveCamera(camera);
    //hack
    renderWindow->SetOffScreenRendering(false);
}

ViewEvaluator::ViewEvaluator(const ViewEvaluator& orig) {
}

ViewEvaluator::~ViewEvaluator() {
}

void ViewEvaluator::evaluate(GeoPoint* view){
   
}


void ViewEvaluator::renderThisView(GeoPoint* view){
    camera->SetFocalPoint(0.5, 0.5, 0.5);
    camera->SetParallelProjection(1);
    camera->SetClippingRange(0,8);
    float viewRange = 3;
    
//    testVol4D* tv=new testVol4D();
//    tv->testCVal(vol);
//    renderer->AddActor(vol->getVolActor());
    //tv->testActor(vol->getVolActor());
    //cout<<"from "<<view->getx()<<" "<<view->gety()<<" "<<view->getz()<<" "<<endl;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange *  view->getz());
   // renderWindow->Render();
}