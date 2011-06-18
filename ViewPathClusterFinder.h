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
 
#include <sstream>

class ViewPathClusterFinder {
public:
    ViewPathClusterFinder();
    ViewPathClusterFinder(const ViewPathClusterFinder& orig);
    void testCluserDetection();
    virtual ~ViewPathClusterFinder();
private:

};

#endif	/* VIEWPATHCLUSTERFINDER_H */

