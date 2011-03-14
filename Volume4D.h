/* 
 * File:   Volume4D.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 17:45
 */

#ifndef VOLUME4D_H
#define	VOLUME4D_H
#include "StepToParamConverter.h"
#include "vtkEssentials.h"
#include "OVASControl.h"

class Volume4D {
public:
    Volume4D();
    Volume4D(OVASControl* oc);
    Volume4D(const Volume4D& orig);
    virtual ~Volume4D();
    virtual void setToStep(int Step);
    
    virtual float getVoxelValue(int x,int y,int z,int step){ return 0;}
    void updateActor();
    void testReebGraph();
   
protected:
    OVASControl* oc;
    vtkSmartPointer<vtkImageData> vtkVol;
    vtkSmartPointer<vtkContourFilter> contourer;
    float* isoVal;
   
    
   
};

#endif	/* VOLUME4D_H */

