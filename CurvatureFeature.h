/*
 * File:   CurvatureFeature.h
 * Author: zoizoi
 *
 * Created on 09 February 2011, 20:07
 */

#ifndef CurvatureFeature_H
#define	CurvatureFeature_H
#include "Feature.h"
#include "CriticalPoint.h"
#include "Volume4D.h"
#include "vtkCurvatures.h"
#include "vtkEssentials.h"

class CurvatureFeature : public Feature{
public:
    
    CurvatureFeature(float weight,OVASControl*,string name);
    CurvatureFeature(const CurvatureFeature& orig);
    virtual ~CurvatureFeature();
    void scoreFeature(GeoPoint* view);
     void readyRenderer(vtkSmartPointer<vtkRenderer> _renderer);
    void climbDown();
private:
    
    
};

#endif	/* CurvatureFeature_H */

