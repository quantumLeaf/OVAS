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
    //ImplicitVolume4D iVol4D=new ImplicitVolume4D("implicitVol1.data");
    //a4d->setVolume(iVol4D);
    //a4d->setAreaWeight(1);
    a4d->loadConfig("./ovas.config");
    
    

    
}

