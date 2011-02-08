/* 
 * File:   testVol4D.h
 * Author: zoizoi
 *
 * Created on 06 February 2011, 14:54
 */

#ifndef TESTVOL4D_H
#define	TESTVOL4D_H

#include "Volume4D.h"


class testVol4D {
public:
    testVol4D();
    testVol4D(const testVol4D& orig);
    virtual ~testVol4D();
    bool testCVal(Volume4D* v);
    bool testActor(vtkSmartPointer<vtkActor> actor);
    bool testRenderWindow(vtkSmartPointer<vtkRenderWindow>);
private:

};

#endif	/* TESTVOL4D_H */

