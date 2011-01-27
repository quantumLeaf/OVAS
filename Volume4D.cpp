/* 
 * File:   Volume4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:45
 */

#include "Volume4D.h"

Volume4D::Volume4D(int x,int y,int z, int s):xDim(x),yDim(y),zDim(z) {

   
}

Volume4D::Volume4D(const Volume4D& orig) {
}

Volume4D::~Volume4D() {
}
void Volume4D::setStepConverter(StepToParamConverter* sc){
    stepConverter=sc;
}

void Volume4D::setToStep(int step){

    for (int k = 0; k < zDim; k++) {
        for (int j = 0; j < yDim; j++) {
            for (int i = 0; i < xDim; i++) {
                float val=getVoxelValue(i,j,k,step);
                vtkVol->SetScalarComponentFromFloat(i, j, k, 0, val);
            }
        }
    }
    
}



