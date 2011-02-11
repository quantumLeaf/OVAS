/* 
 * File:   Analyser3D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:45
 */

#include "Analyser3D.h"

Analyser3D::Analyser3D() {
}

Analyser3D::Analyser3D(const Analyser3D& orig) {
}

Analyser3D::~Analyser3D() {
}

void Analyser3D::init() {
      
        oc->geoSequence->init();
        oc->viewEvaluator->init();
}

void Analyser3D::evalEachView() {
    list<GeoPoint*>* viewList = oc->geoSequence->getViewList();
    list<GeoPoint*>::iterator view;
    int i = 0;
    view = viewList->begin();
     oc->viewEvaluator->readyFeatures();

    for (view = viewList->begin(); view != viewList->end(); view++) {
        oc->viewEvaluator->evaluate((*view));
        
    }
     oc->viewEvaluator->climbDownFeatures();
     

}



