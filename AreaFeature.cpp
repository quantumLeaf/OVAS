/* 
 * File:   AreaFeature.cpp
 * Author: zoizoi
 * 
 * Created on 27 January 2011, 22:58
 */

#include "AreaFeature.h"

AreaFeature::AreaFeature(float weight,OVASControl* oc):Feature(weight,oc) {
    AreaFeature();
    oc->areaFeature=this;
    
}

AreaFeature::AreaFeature(){
    
    
}
AreaFeature::AreaFeature(const AreaFeature& orig) {
}

AreaFeature::~AreaFeature() {
}

