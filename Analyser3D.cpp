/* 
 * File:   Analyser3D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:45
 */

#include "Analyser3D.h"

Analyser3D::Analyser3D() {
}

Analyser3D::Analyser3D(GeoSphere* gs) {
    geoSequence=new GeoSequence(gs);
}

Analyser3D::Analyser3D(const Analyser3D& orig) {
}

Analyser3D::~Analyser3D() {
}

void Analyser3D::evalEachView(){
    list<GeoPoint*>* viewList=geoSequence->getViewList();
    list<GeoPoint*>::iterator view;
    int i=0;
    
    for(view=viewList->begin();view!=viewList->end();view++){
        viewEvaluator->evaluate((*view));
       

    }
    
}



