/* 
 * File:   AreaFeature.cpp
 * Author: zoizoi
 * 
 * Created on 27 January 2011, 22:58
 */

#include "AreaFeature.h"

AreaFeature::AreaFeature() {
}

AreaFeature::AreaFeature(const AreaFeature& orig) {
}

AreaFeature::~AreaFeature() {
}

float AreaFeature::scoreThisFrame(FrameBuffer* data){

    //TD add logtomax area
    float count=countColour(1,1,1,data);
}