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
    AreaFeature();
    AreaFeature(const AreaFeature& orig);
    virtual ~AreaFeature();
    void initFeature();
    void scoreThisFrame(float* data);
private:

};

#endif	/* AREAFEATURE_H */

