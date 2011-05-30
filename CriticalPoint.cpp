/* 
 * File:   CriticalPoint.cpp
 * Author: zoizoi
 * 
 * Created on 22 May 2011, 11:13
 */

#include "CriticalPoint.h"

CriticalPoint::CriticalPoint(int _x,int _y, int _z,int _step, float _value, int _xDim, int _yDim, int _zDim):x(_x),y(_y),z(_z),step(_step),value(_value),xDim(_xDim) ,yDim(_yDim),zDim(_zDim){
    actor=vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    float interestRadius=0.03;
     sphereSource->SetCenter(getXFloat(), getYFloat(), getZFloat());
    sphereSource->SetRadius(interestRadius);
    sphereSource->SetPhiResolution(20);
    sphereSource->SetThetaResolution(20);
    
    sphereSource->Update();
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetAmbient(1); //SetShading(0);
    actor->GetProperty()->SetDiffuse(0); //SetShading(0);
    actor->GetProperty()->SetSpecular(0); //SetShading(0);
    actor->GetProperty()->SetInterpolationToFlat(); //actor->GetProperty()->SetOpacity(0.5);
    actor->GetProperty()->SetColor(1, 0, 0);
}

CriticalPoint::CriticalPoint(const CriticalPoint& orig) {
}

CriticalPoint::~CriticalPoint() {
}

vtkSmartPointer<vtkActor> CriticalPoint::getActor(){
 
    return actor;
}