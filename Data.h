#ifndef DATA_H
#define DATA_H

#include <vector>
#include <iostream>
#include <cmath>
#include "Global.h"

struct Data {
    DataType * data; //the data array
    uint size[3]; //dimensions
    uint totalSize; //product of the above 3 integers

    DataType maxValue, minValue; //max and min values occuring in the data
    size_t maxId;
    std::vector< DataType > saddles; //we will fill this up with all of the saddles that exist in the data

    Data() : data(0), totalSize(0) {
        size[0] = size[1] = size[2] = 0;
    }

    ~Data() {
       // if (data) delete[] data;
    }

    //1 dimensional referencing

    DataType & operator[](uint i) {
        if (i < totalSize) return data[i];
        else return saddles[i - totalSize];
    }

    uint convertIndex(uint i, uint j, uint k) {
        return (k * size[1] + j) * size[0] + i;
    }

    void convertIndex(uint id, uint & x, uint & y, uint & z) {

        if (id >= totalSize) {
            std::cerr << "Error: trying to convert the index of a saddle into xyz" << std::endl;
            x = y = z = 0xffffffff;
            return;
        }

        int size01 = size[0] * size[1];

        z = id / size01;
        y = (id - z * size01) / size[0];
        x = id - z * size01 - y * size[0];
    }

    bool greater(uint a, uint b);
    bool less(uint a, uint b);
    bool load(const char * filename, char * prefix, bool * compressed); //prefix and compressed are written to
    bool loadVol(const char * filename, int size); //prefix and compressed are written to
    bool initData(float* rawData, int totSize, int size); //prefix and compressed are written to
    bool initData(unsigned char* rawData, int totSize, int size); //prefix and compressed are written to

    
    inline void endian_byte_swapper (char* dest, char const* src) {
        // Use bit manipulations instead of accessing individual bytes from memory, much faster.
        uint* p_dest = reinterpret_cast<uint*> (dest);
        uint const* const p_src = reinterpret_cast<uint const*> (src);
        *p_dest = (*p_src >> 24) | ((*p_src & 0x00ff0000) >> 8) | ((*p_src & 0x0000ff00) << 8) | (*p_src << 24);
    }
};





#endif
