/* 
 * File:   GeoSphere.cpp
 * Author: zoizoi
 * 
 * Created on 17 December 2010, 23:17
 */

#include "GeoSphere.h"


GeoSphere::GeoSphere() {
}

GeoSphere::GeoSphere(const GeoSphere& orig) {
}

GeoSphere::~GeoSphere() {

}


bool GeoSphere::loadGeoSphereFile(string filename){

    cout<<"loading sphere file "<<filename<<endl;
    ifstream inf;
    inf.open(filename.c_str());
    if(!inf.is_open()){
     cout<<"cant load file "<<filename<<endl;
     return false;
    }
   
        inf >> this->n_vertices >> this->n_faces >> this->n_edges;
        
    vertices = new float[n_vertices * 3];
    faces = new int[n_faces * 3];
    for (int i = 0; i < n_vertices; i++) {
        inf >> vertices[3 * i] >> vertices[3 * i + 1] >> vertices[3 * i + 2];
    }
    for (int i = 0; i < n_faces; i++) {
        inf >> faces[3 * i] >> faces[3 * i + 1] >> faces[3 * i + 2];
    }

    views = new GeoPoint*[n_vertices];
    GeoPoint** extdNbrs = new GeoPoint*[n_vertices];

   
    //extend to second-order neighbours

    //for each vertex
    for (int i = 0; i < n_vertices; i++) {

        views[i] = new GeoPoint(i,vertices[3 * i],vertices[3 * i+1],vertices[3 * i+2]);
        
        extdNbrs[i] = new GeoPoint(i,vertices[3 * i],vertices[3 * i+1],vertices[3 * i+2]);
    	//TD convert to use vtk cells?
        

        //and for each face add neighbours to geopoint for that vertex
        for (int j = 0; j < n_faces - 1; j++) {
            if (faces[3 * j] == i) {
                views[i]->addNeighbour(faces[3 * j + 1]);
                views[i]->addNeighbour(faces[3 * j + 2]);
            }
            if (faces[3 * j + 1] == i) {
                views[i]->addNeighbour(faces[3 * j]);
                views[i]->addNeighbour(faces[3 * j + 2]);
            }
            if (faces[3 * j + 2] == i) {
                views[i]->addNeighbour(faces[3 * j]);
                views[i]->addNeighbour(faces[3 * j + 1]);
            }
        }
        
    }
   
    for (int i = 0; i < n_vertices; i++) {

        for (int i2 = 0; i2 < views[i]->neighbourCount; i2++) {
            extdNbrs[i]->addNeighbour(views[i]->neighbours[i2]);
            int neib1 = views[i]->neighbours[i2];
            for (int i3 = 0; i3 < views[neib1]->neighbourCount; i3++) {
                extdNbrs[i]->addNeighbour(views[neib1]->neighbours[i3]);
            }
        }
    }
     
    //delete []views;
    views = extdNbrs;
    cout<<"created Geophere with nv:"<<n_vertices<<endl;
    
     
}

void GeoSphere::outputInfo(){
    cout<<"Info "<<n_vertices<<" "<<n_edges<<" "<<n_faces<<endl;
}


