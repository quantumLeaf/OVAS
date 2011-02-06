/* 
 * File:   Analyser3D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:45
 */

#include "Analyser3D.h"

Analyser3D::Analyser3D() {
}

Analyser3D::Analyser3D(Analyser4D* a) {
    
}

Analyser3D::Analyser3D(const Analyser3D& orig) {
}

Analyser3D::~Analyser3D() {
}
void Analyser3D::init(){
    geoSequence->init();
}
void Analyser3D::evalEachView(){
    list<GeoPoint*>* viewList=geoSequence->getViewList();
    list<GeoPoint*>::iterator view;
    int i=0;
    view=viewList->begin();
    cout<<"v is "<<viewEvaluator->vol<<endl;
    viewEvaluator->renderThisView((*view));
    testVol4D* r=new testVol4D();
                r->testActor(viewEvaluator->vol->getVolActor());
    for(view=viewList->begin();view!=viewList->end();view++){

        viewEvaluator->evaluate((*view));
    }
    
}



