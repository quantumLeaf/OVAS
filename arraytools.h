/*
 * File:   arraytools.h
 * Author: zoizoi
 *
 * Created on 05 March 2009, 11:04
 */

#ifndef _ARRAYTOOLS_H
#define	_ARRAYTOOLS_H

class ArrayTools {
public:
    ArrayTools();
    ArrayTools(const ArrayTools& orig);
    virtual ~ArrayTools();
    
    template < typename T >
    static T** allocate2DArray(int nRows, int nCols) {
        //(step 1) allocate memory for array of elements of column
        T **ppi = new T*[nRows];

        //(step 2) allocate memory for array of elements of each row
        T *curPtr = new T [nRows * nCols];

        // Now point the pointers in the right place
        for (int i = 0; i < nRows; ++i) {
            ppi[i] = curPtr;
            curPtr += nCols;
        }
        return ppi;
    }

    template < typename T >
    static T ***allocate3DArray(int nRows, int nCols, int nPlanez) {
        T ***ppp = new T**[nRows];

        for (int i = 0; i < nRows; ++i) {
                ppp[i]=allocate2DArray<T>(nCols,nPlanez);
        }
        return ppp;
    }
    template < typename T >
    static T ***allocate3DArrayB(int nRows, int nCols, int nPlanez) {
        T ***ppp = new T**[nPlanez];
        T* alloc = new T[nPlanez*nCols*nRows];
        for (int i = 0; i < nPlanez; ++i) {
                ppp[i]=alloc;
                alloc+=nCols*nRows;
        }
        return ppp;
    }

    template < typename T >
    static void free2DArray(T** Array) {
        delete [] * Array;
        delete [] Array;
    }

    template < typename T >
    static void free3DArray(T*** Array) {
        delete [] **Array;
        delete [] * Array;
        delete [] Array;
    }


private:

};



#endif	/* _ARRAYTOOLS_H */

