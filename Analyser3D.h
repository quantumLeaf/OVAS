/* 
 * File:   Analyser3D.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 17:45
 */

#ifndef ANALYSER3D_H
#define	ANALYSER3D_H
#include "Feature.h"
#include "GeoSequence.h"
#include "GeoSphere.h"
#include "ViewEvaluator.h"
class Analyser3D {
public:
    Analyser3D();
    Analyser3D(Analyser4D* a);
    Analyser3D(const Analyser3D& orig);
    virtual ~Analyser3D();
    void init();
    void initFeatures();
    void evalEachView();
    
    void setViewEvaluator(ViewEvaluator* ve){
        viewEvaluator=ve;
        
    }

    ViewEvaluator* viewEvaluator;
private:
    Feature* listOfFeatures;
    GeoSequence* geoSequence;
    
    

};

#endif	/* ANALYSER3D_H */

