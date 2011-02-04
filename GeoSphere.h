/* 
 * File:   GeoSphere.h
 * Author: zoizoi
 *
 * Created on 17 December 2010, 23:17
 */

#ifndef _GEOSPHERE_H
#define	_GEOSPHERE_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "GeoPoint.h"
using namespace std;

class GeoSphere {
public:
    GeoSphere();
    GeoSphere(const GeoSphere& orig);
    virtual ~GeoSphere();
    bool loadGeoSphereFile(string filename);
    void outputInfo();
    int getNumVs(){
        return n_vertices;
    }
    GeoPoint* getView(int i){
        return views[i];
    }

   
private:
    int n_vertices;
    int n_faces;
    int n_edges;
    float *vertices;
    int *faces;
    int** neighbours;
    GeoPoint** views;

};

#endif	/* _GEOSPHERE_H */

