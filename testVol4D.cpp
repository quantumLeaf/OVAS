/* 
 * File:   testVol4D.cpp
 * Author: zoizoi
 * 
 * Created on 06 February 2011, 14:54
 */

#include "testVol4D.h"

testVol4D::testVol4D() {
}

testVol4D::testVol4D(const testVol4D& orig) {
}

testVol4D::~testVol4D() {
}

bool testVol4D::testCVal(Volume4D* v){
    float x=v->getVoxelValue(32,32,32,0);
    cout<<"cval is "<<x<<endl;
    return true;
}

bool testVol4D::testActor(vtkSmartPointer<vtkActor> actor){
    vtkSmartPointer<vtkConeSource> coneSource =
    vtkSmartPointer<vtkConeSource>::New();
  coneSource->Update();

  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(coneSource->GetOutputPort());

  actor->SetMapper(mapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .2, .1); // Background color dark red

  //Render and interact
      renderWindow->Render();
      renderWindowInteractor->Start();

  return EXIT_SUCCESS;

}