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
    gsp=gs;

}

GeoSequence::GeoSequence(const GeoSequence& orig) {
}

GeoSequence::~GeoSequence() {
}

void GeoSequence::init(){
    viewList=new std::list<GeoPoint*>();
    for(int i=0;i<gsp->getNumVs();i++){
        GeoPoint* view=gsp->getView(i);
        //cout<<"getting from spere "<<view->getx()<<" "<<view->gety()<<" "<<view->getz()<<" "<<endl;
        viewList->push_back(gsp->getView(i));
    }
}


