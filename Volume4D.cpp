/* 
 * File:   Volume4D.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 17:45
 */

#include "Volume4D.h"

Volume4D::Volume4D() {

   
}

Volume4D::Volume4D(const Volume4D& orig) {
}

Volume4D::~Volume4D() {
}
void Volume4D::setStepConverter(StepToParamConverter* sc){
    stepConverter=sc;
}

