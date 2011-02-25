/*
 * File:   AAGaussian.cpp
 * Author: zoizoi
 *
 * Created on 08 June 2010, 22:51
 */

#include "AAGaussian.h"

AAGaussian::AAGaussian(float _x,float _y,float _z,float _sx, float _sy, float _sz,float _w) {
    x=_x;
    y=_y;
    z=_z;
    w=_w;
    sx=_sx;
    sy=_sy;
    sz=_sz;

}

AAGaussian::AAGaussian(const AAGaussian& orig) {
}

AAGaussian::~AAGaussian() {
}

