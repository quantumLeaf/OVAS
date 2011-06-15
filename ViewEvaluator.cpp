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
    oc = o;
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
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
    camera->SetClippingRange(0, 8);
    upSet = false;
    upV = new double[3]();
}

ViewEvaluator::ViewEvaluator(const ViewEvaluator& orig) {
}

ViewEvaluator::~ViewEvaluator() {
}

void ViewEvaluator::init() {
    renderer->AddActor(oc->volActor);
}

void ViewEvaluator::readyFeatures() {
    vector<Feature*>::iterator it;
    for (it = oc->features->begin(); it != oc->features->end(); it++) {
        Feature* a = *(it);
        (*it)->readyRenderer(renderer);
    }
}

void ViewEvaluator::climbDownFeatures() {
    oc->currentView = 0;
    vector<Feature*>::iterator it;
    for (it = oc->features->begin(); it != oc->features->end(); it++) {
        (*it)->climbDown();
    }
}

void ViewEvaluator::evaluate(GeoPoint* view) {
   
    vector<Feature*>::iterator it;
    
    for (it = oc->features->begin(); it != oc->features->end(); it++) {
        (*it)->scoreFeature(view);
    }
    oc->currentView++;


}

void ViewEvaluator::renderThisView(GeoPoint* view) {

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

void ViewEvaluator::outputView(GeoPoint* view, string filename) {
    readyFeatures();
    oc->volActor->GetProperty()->SetAmbient(0.3);
    oc->volActor->GetProperty()->SetDiffuse(0.7); //SetShading(0);
    oc->volActor->GetProperty()->SetSpecular(0.7); //SetShading(0);
    oc->volActor->GetProperty()->SetInterpolationToPhong();

    vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
    windowToImageFilter->SetInput(renderWindow);
    vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetInput(windowToImageFilter->GetOutput());
    float viewRange = 3;
    vnl_vector<float> pos(3);
    double* upV = new double[3]();
    pos[0] = viewRange * view->getx();
    pos[1] = viewRange * view->gety();
    pos[2] = viewRange * view->getz();
    camera->SetPosition(pos[0], pos[1], pos[2]);

    //cout << "outputing angle " << view << "with interest " << OVAData[view][2] << " and area " << OVAData[view][3] << " " << OVAData[view][1] << " : " << OVAData[view][0] << endl;
    if (!upSet) {
        upSet = true;
        upV = camera->GetViewUp();
    }
    //upV[0]=0;upV[1]=1;upV[2]=0;
    camera->SetViewUp(upV);
    vnl_vector<float> northPole(3);
    northPole[0] = 0.0001;
    northPole[1] = 1;
    northPole[2] = 0;
    vnl_vector<float> north(3);
    vnl_vector<float> here(3);
    here[0] = pos[0];
    here[1] = pos[1];
    here[2] = pos[2];
    north = northPole - here;
    // camera->SetViewUp(north[0], north[1], north[2]);
    camera->OrthogonalizeViewUp();
    upV = camera->GetViewUp();
    cout << " up is " << upV[0] << " " << upV[1] << " " << upV[2] << endl;
    cout << " view is " << pos[0] << " " << pos[1] << " " << pos[2] << endl;
    renderWindow->Render();
    // if (view == 275) cout << " the worst is " << 275 << " OVA " << OVAData[275][0] << OVAData[275][1] << endl;
    windowToImageFilter->Update();
    filename = *(oc->resultsPath) + filename;
    cout << "OUTPUTTING to " << filename << endl;
    writer->SetFileName(filename.c_str());
    writer->Write();


    renderWindow->Render();
    climbDownFeatures();
}

void ViewEvaluator::interact() {



    if (oc->rwiSet == false) {
        oc->rwi =
                vtkSmartPointer<vtkRenderWindowInteractor>::New();
        oc->rwi->SetRenderWindow(renderWindow);
        oc->rwiSet = true;
    }

    //Add the actors to the scene
    renderer->AddActor(oc->volActor);
    renderer->SetBackground(0.3, 0, 0); // Background color dark red

    //Render and interact
    renderWindow->Render();

    oc->rwi->Start();
  
    

}
