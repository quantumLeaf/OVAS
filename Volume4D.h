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
#include <vector>
#include "CriticalPoint.h"
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
    void loadFloatVolume(string* fileName);
    void createCharVolume();
    
    void testReebGraph();
    void testContourTree();
    void findCritcalPoints();
    float evalPersistence(Data* data,ctBranch* b);
    void addPersistentBranches(Data*,ctBranch*,float thresh);     
   // void outputTree(std::ofstream & out, ctBranch * b,Data* d);
    int DisplayReebGraph(vtkReebGraph *g);
    int DisplayVolumeSkeleton(vtkUnstructuredGrid* vtkNotUsed(volumeMesh), vtkTable *skeleton);
    vector<CriticalPoint*>* criticalPoints;
//    size_t neighbors ( size_t v, size_t * nbrs, void * d );
//    double value ( size_t v, void * d );
    unsigned char* charVol;
protected:
    OVASControl* oc;
    vtkSmartPointer<vtkImageData> vtkVol;
    vtkSmartPointer<vtkContourFilter> contourer;
    float* isoVal;
    
    
    
   
};

#endif	/* VOLUME4D_H */

