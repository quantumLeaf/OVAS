/* 
 * File:   TemporalChangeFeature.h
 * Author: zoizoi
 *
 * Created on 09 February 2011, 20:07
 */

#ifndef TEMPORALCHANGEFEATURE_H
#define	TEMPORALCHANGEFEATURE_H
#include "Feature.h"

class TemporalChangeFeature : public Feature{
public:
    TemporalChangeFeature(float weight,OVASControl*);
    TemporalChangeFeature(const TemporalChangeFeature& orig);
    virtual ~TemporalChangeFeature();
    int scoreFeature(GeoPoint* view);
private:

};

#endif	/* TEMPORALCHANGEFEATURE_H */

