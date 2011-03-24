/* 
 * File:   MovingAAElipsoid.cpp
 * Author: zoizoi
 * 
 * Created on 23 March 2011, 18:54
 */

#include "MovingAAElipsoid.h"

MovingAAElipsoid::MovingAAElipsoid(OVASControl* o,float _px,float _py,float _pz,float _vx,float _vy,float _vz,float _sx,float _sy,float _sz,float _w)
:oc(o),px(_px),py(_py),pz(_pz),vx(_vx),vy(_vy),vz(_vz),sx(_sx),sy(_sy),sz(_sz){
   
}

MovingAAElipsoid::MovingAAElipsoid(const MovingAAElipsoid& orig) {
}

MovingAAElipsoid::~MovingAAElipsoid() {
}

float MovingAAElipsoid::getContribAt(int x, int y, int z, int step){
        float xv = (float) x / oc->xDim;
        float yv = (float) y / oc->yDim;
        float zv = (float) z / oc->zDim;
        float fieldVal = (exp(-1 * (pow(xv - px, 2) * sx + pow(yv - py, 2) * sy + pow(zv - pz, 2) * sz))) * weight;
    return 0;
}
