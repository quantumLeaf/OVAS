/* 
 * File:   testOVAS.cpp
 * Author: zoizoi
 *
 * Created on 23 January 2011, 14:19
 */

#include <cstdlib>
#include "Analyser4D.h"
#include "ImplicitVolume4D.h"
#include "MetaballsVol4D.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    
    Analyser4D* a4d=new Analyser4D;
    a4d->setFile("./ovas.config");
    a4d->init();
    //a4d->analyse();
    a4d->testReebGraph();
    //a4d->findOptimalPath();
    //a4d->outputPath("outputPath");
   // a4d->findAndOutputPaths();
    
}

