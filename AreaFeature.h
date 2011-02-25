/* 
 * File:   AreaFeature.h
 * Author: zoizoi
 *
 * Created on 27 January 2011, 22:58
 */

#ifndef AREAFEATURE_H
#define	AREAFEATURE_H

#include "Feature.h"


class AreaFeature : public Feature {
public:
    AreaFeature(float weight,OVASControl* oc);
    AreaFeature(const AreaFeature& orig);   
    AreaFeature();

    virtual ~AreaFeature();
    
    void scoreFeature(GeoPoint* View){
        Feature::scoreFeature(View);
        
    }
private:
    
};

#endif	/* AREAFEATURE_H */

