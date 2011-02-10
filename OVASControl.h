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

class GeoSequence;
class GeoSphere;
class Volume4D;
class Analyser3D;
class Feature;
class StepToParamConverter;
class ViewEvaluator;

using namespace std;
class OVASControl {
public:
    OVASControl(){
        currentStep=currentView=0;
    };
    OVASControl(const OVASControl& orig);
    virtual ~OVASControl();

    void setFile(string _filename){
        filename=new string(_filename);
    }

    void setGeoSequence(GeoSequence* pointer){
        geoSequence=pointer;
    }
    void setGeoSphere(GeoSphere* pointer){
        geoSphere=pointer;
    }
    void setVolume4D(Volume4D* pointer){
        volume4D=pointer;
    }
   
    void setStepToParamConverter(StepToParamConverter* pointer){
        stepToParamConverter=pointer;
    }
    void setViewEvaluator(ViewEvaluator* pointer){
        viewEvaluator=pointer;
    }

    int xDim,yDim,zDim,numSteps;
    vtkSmartPointer<vtkActor> volActor;
    GeoSequence* geoSequence;
    string* filename;
    Volume4D* volume4D;
    Analyser3D* a3d;
    vector<Feature*>* features;
    ViewEvaluator* viewEvaluator;
    StepToParamConverter* stepToParamConverter;
    GeoSphere* geoSphere;
    int currentStep;
    int currentView;
private:
    
};

#endif	/* OVASCONTROL_H */

