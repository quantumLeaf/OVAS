/*
 * File:   TopologyFeature.h
 * Author: zoizoi
 *
 * Created on 09 February 2011, 20:07
 */

#ifndef TopologyFeature_H
#define	TopologyFeature_H
#include "Feature.h"
#include "CriticalPoint.h"
#include "Volume4D.h"

class TopologyFeature : public Feature{
public:
    
    TopologyFeature(float weight,OVASControl*);
    TopologyFeature(const TopologyFeature& orig);
    virtual ~TopologyFeature();
    void scoreFeature(GeoPoint* view);
    bool closeToCriticalIsoVal(float currentIso,CriticalPoint* point);
     void readyRenderer(vtkSmartPointer<vtkRenderer> _renderer);
    void climbDown();
private:
    float pointIsoThreshold;
    
};

#endif	/* TopologyFeature_H */

