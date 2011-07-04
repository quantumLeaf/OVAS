/* 
 * File:   OVASControl.h
 * Author: zoizoi
 *
 * Created on 06 February 2011, 19:52
 */

#ifndef OVASCONTROL_H
#define	OVASCONTROL_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "vtkEssentials.h"
#include <string>
#include <sstream>

class GeoSequence;
class GeoSphere;
class Volume4D;
class Analyser3D;
class Feature;
class AreaFeature;
class StepToParamConverter;
class ViewEvaluator;
class PathVisualiser;


using namespace std;

class OVASControl {
public:

    OVASControl() {
        currentStep = currentView = 0;
        rwiSet=false;
        
    };
    OVASControl(const OVASControl& orig);
    virtual ~OVASControl();

    void setFile(string _filename) {
        filename = new string(_filename);
    }

    void setGeoSequence(GeoSequence* pointer) {
        geoSequence = pointer;
    }

    void setGeoSphere(GeoSphere* pointer) {
        geoSphere = pointer;
    }

    void setVolume4D(Volume4D* pointer) {
        volume4D = pointer;
    }

    void setStepToParamConverter(StepToParamConverter* pointer) {
        stepToParamConverter = pointer;
    }

    void setViewEvaluator(ViewEvaluator* pointer) {
        viewEvaluator = pointer;
    }

    int xDim, yDim, zDim, numSteps;
    vtkSmartPointer<vtkActor> volActor;
    GeoSequence* geoSequence;
    string* filename;
    string* volDataFileName;
    Volume4D* volume4D;
    Analyser3D* a3d;
    vector<Feature*>* features;
    ViewEvaluato        r* viewEvaluator;
    StepToParamConverter* stepToParamConverter;
    GeoSphere* geoSphere;
    PathVisualiser* pathVisualiser;
    string* resultsPath;
   
    float isoStep;
    int currentStep;
    int currentView;
    float currentIso;
    float isoRange;
    float isoRangeThreshold;
    int* path;
    int* bestViews;
    AreaFeature* areaFeature;
    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
    bool rwiSet;
private:

};

template <class T>
inline std::string to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}

#endif	/* OVASCONTROL_H */



