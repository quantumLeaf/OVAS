/* 
 * File:   Volume4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:45
 */

#include "Volume4D.h"
#include "testVol4D.h"
Volume4D::Volume4D(){
    
}
Volume4D::Volume4D(OVASControl* o){
    oc=o;
    oc->volActor=vtkSmartPointer<vtkActor>::New();
                
    cout<<"\t>Creating Vol4D"<<endl;
    contourer = vtkSmartPointer<vtkContourFilter>::New();
    vtkVol=vtkSmartPointer<vtkImageData>::New();
    vtkVol->SetDimensions(oc->xDim, oc->yDim, oc->zDim);
    float sp = (float) 1.0 / (oc->xDim - 1);
    vtkVol->SetOrigin(0, 0, 0);
    vtkVol->SetSpacing(sp, sp, sp);
    isoVal=new float(3.1);
    contourer->SetInput(vtkVol);
    contourer->SetValue(0,*isoVal);
    contourer->Update();
    vtkSmartPointer<vtkPolyDataMapper> mapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInput(contourer->GetOutput());
    oc->volActor->SetMapper(mapper);
    oc->volActor->GetProperty()->SetAmbient(1);
    oc->volActor->GetProperty()->SetDiffuse(0); //SetShading(0);
    oc->volActor->GetProperty()->SetSpecular(0); //SetShading(0);
    oc->volActor->GetProperty()->SetInterpolationToFlat();
     
}

Volume4D::Volume4D(const Volume4D& orig) {
}

Volume4D::~Volume4D() {
}

void Volume4D::setToStep(int step){
    cout<<"setting vol to step "<<step<<endl;
    for (int k = 0; k < oc->zDim; k++) {
        for (int j = 0; j < oc->yDim; j++) {
            for (int i = 0; i < oc->xDim; i++) {
                float val=getVoxelValue(i,j,k,step);
               
                vtkVol->SetScalarComponentFromFloat(i, j, k, 0, val);
                
            }
        }
    }
    contourer->Update();
    contourer->Modified();

}

void Volume4D::updateActor(){
    contourer->Update();
    contourer->Modified();
}


