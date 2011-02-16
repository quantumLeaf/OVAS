/* 
 * File:   InfoSheet.h
 * Author: zoizoi
 *
 * Created on 14 February 2011, 07:17
 */

#ifndef INFOSHEET_H
#define	INFOSHEET_H
#include "arraytools.h"
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <stdio.h>
#include "GeoSphere.h"
#include "OVASControl.h"

using namespace std;

class InfoSheet {
public:
    //InfoSheet();
    InfoSheet(const InfoSheet& orig);
    virtual ~InfoSheet();
    InfoSheet(OVASControl* o);

     bool validTransition(GeoPoint* fromView,GeoPoint* toView,GeoPoint* prevV);

    void loadInfo(const char* filename);
    void outputInfoData(const char* filename);
    void calcMaxInfo();
    void addTimeInfo(float* timeInfo);
    int lookupNeighbourIndex(int,int);
    int getNeighbour(int,int);
   int* findPath();
   int* returnBestViews();
private:
    const static int numRegions=36;
    int currentInfoTs;

    float** info;
    float*** maxInfo;
    float*** nextViewIndex;
    int* path;
    OVASControl* oc;

};

#endif	/* INFOSHEET_H */

