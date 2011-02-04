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
    Analyser3D(GeoSphere* gs);
    Analyser3D(const Analyser3D& orig);
    virtual ~Analyser3D();
    void initFeatures();
    void evalEachView();
    
    void setViewEvaluator(ViewEvaluator* ve){
        viewEvaluator=ve;
    }

    
private:
    Feature* listOfFeatures;
    GeoSequence* geoSequence;
    
    ViewEvaluator* viewEvaluator;

};

#endif	/* ANALYSER3D_H */

