/* 
 * File:   StepToParamConverter.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 18:18
 */

#ifndef STEPTOPARAMCONVERTER_H
#define	STEPTOPARAMCONVERTER_H

//make static?
class StepToParamConverter {
public:
    StepToParamConverter(float start, float end, int number);
    StepToParamConverter(const StepToParamConverter& orig);
    virtual ~StepToParamConverter();
    float getParamForStep(int step);
private:
    float start;
    float end;
    int numSteps;
};

#endif	/* STEPTOPARAMCONVERTER_H */

