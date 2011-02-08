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
#include "OVASControl.h"
class Analyser3D {
public:
    Analyser3D();
    Analyser3D(OVASControl* o){
        oc=o;
    };
    Analyser3D(const Analyser3D& orig);
    virtual ~Analyser3D();
    void init();
    void initFeatures();
    void evalEachView();

    
private:
    Feature* listOfFeatures;
    OVASControl* oc;

    

};

#endif	/* ANALYSER3D_H */

