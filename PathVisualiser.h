/* 
 * File:   PathVisualiser.h
 * Author: zoizoi
 *
 * Created on 07 March 2011, 06:55
 */

#ifndef PATHVISUALISER_H
#define	PATHVISUALISER_H

#include "OVASControl.h"
#include "GeoSphere.h"
#include "vtkEssentials.h"
#include "ViewPathClusterFinder.h"



class PathVisualiser {
public:
    PathVisualiser(OVASControl* oc);
    PathVisualiser(const PathVisualiser& orig);
    virtual ~PathVisualiser();
    void VisualisePath(int* path, int len);
    void vizMeanPaths();
private:
    OVASControl* oc;
    vtkSmartPointer<vtkCamera> camera;
    vtkSmartPointer<vtkActor> dataActor;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
    float sphereRadius;

};

#endif	/* PATHVISUALISER_H */

