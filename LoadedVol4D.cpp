/* 
 * File:   LoadedVol4D.cpp
 * Author: zoizoi
 * 
 * Created on 21 May 2011, 16:32
 */

#include "LoadedVol4D.h"

LoadedVol4D::LoadedVol4D(OVASControl* oc, string* filename) : ImplicitVolume4D(oc) {
    oc->volDataFileName=filename;
    
}

LoadedVol4D::LoadedVol4D(const LoadedVol4D& orig) {
}

LoadedVol4D::~LoadedVol4D() {
}
float LoadedVol4D::getVoxelValue(int x, int y, int z, int step) {
    
//    float time = oc->stepToParamConverter->getParamForStep(step);
//    float tFraction = oc->stepToParamConverter->getParamFractionForStep(step);
//    
    return vtkVol->GetScalarComponentAsFloat(x,y,z,0);
    
    


}
