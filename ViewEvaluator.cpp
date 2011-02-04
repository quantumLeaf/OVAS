/* 
 * File:   ViewEvaluator.cpp
 * Author: zoizoi
 * 
 * Created on 03 February 2011, 22:05
 */

#include "ViewEvaluator.h"
#include "FeatureWeights.h"
#include "Volume4D.h"

ViewEvaluator::ViewEvaluator() {
}

ViewEvaluator::ViewEvaluator(FeatureWeights* fw,Volume4D* v) {
    featureWeights=fw;
    vol=v;
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
    camera->SetFocalPoint(0.5, 0.5, 0.5);
    camera->SetParallelProjection(1);
    camera->SetClippingRange(0,8);
    float viewRange = 3;
    camera->SetPosition(viewRange * view->getx(), viewRange * view->gety(), viewRange *  view->getz());
    renderWindow->Render();
    
}

