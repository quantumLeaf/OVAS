/* 
 * File:   Volume4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:45
 */

#include "Volume4D.h"

Volume4D::Volume4D(int x,int y,int z, int s):xDim(x),yDim(y),zDim(z){
    contourer = vtkSmartPointer<vtkContourFilter>::New();
    vtkVol=vtkSmartPointer<vtkImageData>::New();
    vtkVol->SetDimensions(xDim, yDim, zDim);
    float sp = (float) 1.0 / (xDim - 1);
    vtkVol->SetOrigin(0, 0, 0);
    vtkVol->SetSpacing(sp, sp, sp);
    isoVal=new float(5);
   
}

Volume4D::Volume4D(const Volume4D& orig) {
}

Volume4D::~Volume4D() {
}
void Volume4D::setStepConverter(StepToParamConverter* sc){
    stepConverter=sc;
}

void Volume4D::setToStep(int step){
    cout<<"setting vol to step "<<step<<endl;
    for (int k = 0; k < zDim; k++) {
        for (int j = 0; j < yDim; j++) {
            for (int i = 0; i < xDim; i++) {
                float val=getVoxelValue(i,j,k,step);
                //cout<<i<<" "<<j<<" "<<k<<" "<<endl;
                vtkVol->SetScalarComponentFromFloat(i, j, k, 0, val);
                
            }
        }
    }
    
}

vtkSmartPointer<vtkActor> Volume4D::getCurrentVolActor(){

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    contourer->SetInput(vtkVol);
    contourer->SetValue(0,*isoVal);
    contourer->Update();
    
    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();

    mapper->SetInput(contourer->GetOutput());
    
    actor->SetMapper(mapper);
    
    return actor;
}



