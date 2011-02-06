/* 
 * File:   GeoPoint.cpp
 * Author: zoizoi
 * 
 * Created on 19 December 2010, 22:21
 */

#include "GeoPoint.h"

GeoPoint::GeoPoint(int i) {
    index = i;
    neighbourCount = 0;
}
GeoPoint::GeoPoint(int i, float _x, float _y, float _z){
    x=_x;y=_y;z=_z;
    index = i;
    neighbourCount = 0;
    
}
GeoPoint::GeoPoint(const GeoPoint& orig) {
}

GeoPoint::~GeoPoint() {
}

void GeoPoint::addNeighbour(int nei) {
    for (int i = 0; i < neighbourCount; i++) {
        if (neighbours[i] == nei) return;        
    }
    neighbours[neighbourCount++] = nei;
}
