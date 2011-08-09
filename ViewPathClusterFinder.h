/* 
 * File:   ViewPathClusterFinder.h
 * Author: zoizoi
 *
 * Created on 18 June 2011, 10:15
 */

#ifndef VIEWPATHCLUSTERFINDER_H

#define	VIEWPATHCLUSTERFINDER_H
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkIntArray.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkPoints.h>
#include <vtkTable.h>
#include <vtkDoubleArray.h>
#include <vtkKMeansStatistics.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vector>
#include <sstream>

#include "OVASControl.h"
using namespace std;
class ViewPathClusterFinder {
public:
    ViewPathClusterFinder(int plen, OVASControl* oc);
    ViewPathClusterFinder(const ViewPathClusterFinder& orig);
    void testCluserDetection();
    virtual ~ViewPathClusterFinder();
    void addPath (int* path);
    void outputPathsToFile();
    void loadPathsFromFile();
    int getNumPaths(){
        return viewPaths->size();
    }
    int getNumSteps(){
        return pathLength;
    }
    int getPathViewIndex(int path, int step){
        return viewPaths->at(path)[step];
    }
    vector<int*>* getPathClusterMeans();
    int* getPathClusters(){
        return pathClusters;
    }
    int* pathClusters;
    
    OVASControl* oc;
private:
    vector<int*>* viewPaths;
    int pathLength;

};

#endif	/* VIEWPATHCLUSTERFINDER_H */

