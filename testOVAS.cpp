/* 
 * File:   testOVAS.cpp
 * Author: zoizoi
 *
 * Created on 23 January 2011, 14:19
 */

#include <cstdlib>
#include <vtkCellArray.h>
#include <vtkDataSetAttributes.h>
#include "Analyser4D.h"
#include "ImplicitVolume4D.h"
#include "MetaballsVol4D.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int dim=3;
    vtkSmartPointer<vtkImageData> vtkVol=vtkSmartPointer<vtkImageData>::New();
//    vtkVol->SetDimensions(dim,dim,dim);
//    float sp = (float) 1.0 / (dim - 1);
//    vtkVol->SetOrigin(0, 0, 0);
//    vtkVol->SetSpacing(sp, sp, sp);
//    cout<<" num points "<<vtkVol->GetNumberOfPoints()<<" cells "<<vtkVol->GetNumberOfCells()<<endl;
//    for (int k = 0; k < dim; k++) {
//        for (int j = 0; j < dim; j++) {
//            for (int i = 0; i < dim; i++) {
//                float val=2;
//                //cout<<" got val "<<val<<endl;
//                vtkVol->SetScalarComponentFromFloat(i, j, k, 0, val);
//            }
//        }
//    }
//    vtkSmartPointer<vtkAppendFilter> appendFilter =
//    vtkSmartPointer<vtkAppendFilter>::New();
//  appendFilter->AddInput(vtkVol);
//vtkSmartPointer<vtkUnstructuredGrid> volumeMesh=appendFilter->GetOutput();
//appendFilter->Update();
//    cout<<" vtkug num cells "<<volumeMesh->GetNumberOfCells()<<endl;
//    cout<<" imagedata num cells "<<vtkVol->GetNumberOfCells()<<endl;
//    double* data=vtkVol->GetPointData()->GetScalars()->GetTuple(0);
//    cout<<" vmesh "<<*data<<endl;



    Analyser4D* a4d=new Analyser4D;
    a4d->setFile("./ovas.config");
    a4d->init();
//a4d->interactSteps();
    
    a4d->analyse();
//a4d->testReebGraph();
//a4d->testContourTree();


    a4d->findOptimalPath();
    a4d->outputPath("outputPath");
    //a4d->findAndOutputPaths();
//    
}

