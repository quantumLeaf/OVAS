/* 
 * File:   FrameBuffer.cpp
 * Author: zoizoi
 * 
 * Created on 30 January 2011, 20:29
 */

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() {
}

FrameBuffer::FrameBuffer(const FrameBuffer& orig) {
}

FrameBuffer::~FrameBuffer() {
}
void FrameBuffer::SetLen(int* len) {
    this->len = len;
}
int* FrameBuffer::GetLen() const {
    return len;
}

