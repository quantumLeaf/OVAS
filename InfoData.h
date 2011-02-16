/* 
 * File:   InfoData.h
 * Author: zoizoi
 *
 * Created on 15 February 2011, 20:56
 */

#ifndef INFODATA_H
#define	INFODATA_H
#include "InfoSheet.h"

class InfoData {
public:

    InfoData(OVASControl* oc);
    InfoData(const InfoData& orig);
    int* findOptimalPath();
    virtual ~InfoData();
private:
    InfoSheet* infoSheet;
    vector<Feature*>* features;
    int numViews;
    int numSteps;
};

#endif	/* INFODATA_H */

