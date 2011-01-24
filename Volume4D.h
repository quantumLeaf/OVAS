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

class Volume4D {
public:
    Volume4D();
    Volume4D(const Volume4D& orig);
    virtual ~Volume4D();
    void setToStep(int Step);
    void setStepConverter(StepToParamConverter* sc);
    
private:
    StepToParamConverter* stepConverter;
///    vtkImageData vtkVol;
    
};

#endif	/* VOLUME4D_H */

