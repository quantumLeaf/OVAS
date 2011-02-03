/* 
 * File:   MetaballsVol4D.cpp
 * Author: zoizoi
 * 
 * Created on 26 January 2011, 22:10
 */

#include "MetaballsVol4D.h"

MetaballsVol4D::MetaballsVol4D(int xDim, int yDim, int zDim, int numSteps, float twist):ImplicitVolume4D(xDim,yDim,zDim,numSteps),twist(twist) {

}

MetaballsVol4D::MetaballsVol4D(const MetaballsVol4D& orig) {
}

MetaballsVol4D::~MetaballsVol4D() {
}

float MetaballsVol4D::getVoxelValue(int x, int y, int z, int step){
   
    return 1;
}

