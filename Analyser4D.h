/* 
 * File:   Analyser4D.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 17:51
 */

#ifndef ANALYSER4D_H
#define	ANALYSER4D_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "GeoSphere.h"
#include "MetaballsVol4D.h"
#include "FlyingSaucersVol4D.h"
#include "Analyser3D.h"
#include "FeatureWeights.h"
#include "OVASControl.h"
#include "TemporalChangeFeature.h"
#include "TemporalChangeFeature2.h"

using namespace std;

class Analyser4D {
public:
    Analyser4D();
    Analyser4D(const Analyser4D& orig);
    virtual ~Analyser4D();
    void init();
    void initFeatures();
    void initAnalyser3D(int step);
    void evalEach3D();
    void setVolume(Volume4D* vol);
    void setAreaWeight(float weight);
    void setTopologyWeight(float weight);
    void setTemporalChangeWeight(float weight);
    void setCurvatureWeight(float weight);
    void analyse();
    void findOptimalPath();
    void findAndOutputPaths();
    void testReebGraph();
    void outputView(int view, char* filename);
    void outputPath(string filestem);
    void outputBVs(string filestem);
    void outputPathVis(string filename);
    void setFile(string _filename) {
        oc->filename = new string(_filename);
    }


private:
    int step;
    OVASControl* oc;
    int dims, numSteps;
    void loadConfig(string filename);

};

#endif	/* ANALYSER4D_H */

