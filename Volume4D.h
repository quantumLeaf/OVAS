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
#include "Data.h"
#include "Mesh.h"
extern "C" 
{
#include <tourtre.h>
}

#include <unistd.h>

using std::cin;
using std::cout;
using std::clog;
using std::cerr;
using std::endl;



class Volume4D {
public:
    Volume4D();
    Volume4D(OVASControl* oc);
    Volume4D(const Volume4D& orig);
    virtual ~Volume4D();
    virtual void setToStep(int Step);
    
    virtual float getVoxelValue(int x,int y,int z,int step){ return 0;}
    void updateActor();
    void loadFloatVolume(string fileName);
    
    void testReebGraph();
    void testContourTree();
    int DisplayReebGraph(vtkReebGraph *g);
    int DisplayVolumeSkeleton(vtkUnstructuredGrid* vtkNotUsed(volumeMesh), vtkTable *skeleton);
//    size_t neighbors ( size_t v, size_t * nbrs, void * d );
//    double value ( size_t v, void * d );
    
protected:
    OVASControl* oc;
    vtkSmartPointer<vtkImageData> vtkVol;
    vtkSmartPointer<vtkContourFilter> contourer;
    float* isoVal;
   
    
   
};

#endif	/* VOLUME4D_H */

