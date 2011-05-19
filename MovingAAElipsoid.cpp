/* 
 * File:   MovingAAElipsoid.cpp
 * Author: zoizoi
 * 
 * Created on 23 March 2011, 18:54
 */

#include "MovingAAElipsoid.h"
#include "StepToParamConverter.h"

MovingAAElipsoid::MovingAAElipsoid(OVASControl* o, float _px, float _py, float _pz, float _vx, float _vy, float _vz, float _sx, float _sy, float _sz, float _w)
: oc(o), px(_px), py(_py), pz(_pz), vx(_vx), vy(_vy), vz(_vz), sx(_sx), sy(_sy), sz(_sz), weight(_w) {
    //cout<<"new px "<<px<<" "<<py<<" "<<pz<<" "<<vx<<" "<<vy<<" "<<vz<<" "<<sx<<" "<<sy<<" "<<sz<<" "<<endl;
}

MovingAAElipsoid::MovingAAElipsoid(const MovingAAElipsoid& orig) {
}

MovingAAElipsoid::~MovingAAElipsoid() {
}

float MovingAAElipsoid::getContribAt(int x, int y, int z, int step) {
    float xv = (float) x / oc->xDim;
    float yv = (float) y / oc->yDim;
    float zv = (float) z / oc->zDim;
    float t = oc->stepToParamConverter->getParamForStep(step);

    float posx, posy, posz;
    //cout<<" px "<<px<<endl;
    posx = px + (vx * t);
    posx -= floor(posx);
//    posx *= 0.8;
//    posx += 0.1;
    posy = py + (vy * t);
    posy -= floor(posy);
//    posy *= 0.5;
//    posy += 0.25;
    posz = pz + (vz * t);
    posz -= floor(posz);
//    posz *= 0.5;
//    posz += 0.25;

    float fieldVal = (exp(-1 * (pow(xv - posx, 2) * sx + pow(yv - posy, 2) * sy + pow(zv - posz, 2) * sz))) * weight;
    if (x == y && y == z && z == 16) {
        // cout<<"here t "<<t<<" fv "<<fieldVal<<" posx "<<posx<<" posy "<<posy<<" posz "<<posz<<endl;
    }

    return fieldVal;
}
