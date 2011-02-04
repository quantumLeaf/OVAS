/* 
 * File:   GeoSequence.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 18:30
 */

#include "GeoSequence.h"

GeoSequence::GeoSequence() {
}

GeoSequence::GeoSequence(GeoSphere* gs){
    viewList=new std::list<GeoPoint*>();

    
    for(int i=0;i<gs->getNumVs();i++){
        viewList->push_back(gs->getView(i));
    }
}

GeoSequence::GeoSequence(const GeoSequence& orig) {
}

GeoSequence::~GeoSequence() {
}



