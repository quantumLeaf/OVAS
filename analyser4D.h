/* 
 * File:   Analyser4D.h
 * Author: zoizoi
 *
 * Created on 23 January 2011, 14:18
 */

#ifndef ANALYSER4D_H
#define	ANALYSER4D_H
#include <pthread.h>

class Analyser4D {
public:
    Analyser4D();
    Analyser4D(const Analyser4D& orig);
    virtual ~Analyser4D();
    int loadVolume4D(string filename);
private:

};

#endif	/* ANALYSER4D_H */

