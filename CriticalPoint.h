/* 
 * File:   CriticalPoint.h
 * Author: zoizoi
 *
 * Created on 22 May 2011, 11:13
 */

#ifndef CRITICALPOINT_H
#define	CRITICALPOINT_H
#include "vtkSmartPointer.h"
#include "vtkActor.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
class CriticalPoint {
public:
    CriticalPoint(int x,int y, int z,int step, float value, int,int,int);
    CriticalPoint(const CriticalPoint& orig);
    virtual ~CriticalPoint();
    vtkSmartPointer<vtkActor> getActor();
    float getXFloat(){
        return ((float)(x))/((float)xDim);
    }
    float getYFloat(){
        return ((float)(y))/((float)yDim);
    }
    float getZFloat(){
        return ((float)(z))/((float)zDim);
    }
    int xDim,yDim,zDim;
    int x,y,z;
    int step;
    float value;
    vtkSmartPointer<vtkActor> actor;
private:

};

#endif	/* CRITICALPOINT_H */

