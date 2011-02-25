/* 
 * File:   StepToParamConverter.cpp
 * Author: zoizoi
 * 
 * Created on 23 January 2011, 18:18
 */

#include "StepToParamConverter.h"

StepToParamConverter::StepToParamConverter(float start, float end, int number) {
    numSteps=number;
    this->start=start;
    this->end=end;
}

StepToParamConverter::StepToParamConverter(const StepToParamConverter& orig) {
}

StepToParamConverter::~StepToParamConverter() {
}
float StepToParamConverter::getParamForStep(int step){
    float distance=end-start;
    float fraction=(float)step/(numSteps-1);
    return (distance*fraction+start);
}

float StepToParamConverter::getParamFractionForStep(int step){
    float distance=end-start;
    float fraction=(float)step/(numSteps-1);
    return fraction;
}

