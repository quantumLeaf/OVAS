/* 
 * File:   testOVAS.cpp
 * Author: zoizoi
 *
 * Created on 23 January 2011, 14:19
 */

#include <cstdlib>
#include <vtkCellArray.h>
#include <vtkDataSetAttributes.h>
#include "Analyser4D.h"
#include "ImplicitVolume4D.h"
#include "MetaballsVol4D.h"
#include "ViewPathClusterFinder.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int dim = 3;
    vtkSmartPointer<vtkImageData> vtkVol = vtkSmartPointer<vtkImageData>::New();
    Analyser4D* a4d = new Analyser4D;
    a4d->setFile("./ovas.config");
    
    //a4d->testFunc();
    a4d->init();

    a4d->interactSteps();

//    a4d->analyse();
   // a4d->outputFeatureScores();
    //a4d->inputFeatureScores();
    //a4d->testReebGraph();
    //a4d->testContourTree();


    //a4d->findOptimalPath();
    //a4d->outputPath("outputPath");
    //a4d->findAndOutputPaths();
  //  a4d->findPathClusters();
   // a4d->vizMeanPaths();
    
//    a4d->outputMeanPaths("clusterMeanPath");
    //    
}
