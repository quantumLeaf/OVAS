/* 
 * File:   FrameBuffer.h
 * Author: zoizoi
 *
 * Created on 30 January 2011, 20:29
 */

#ifndef FRAMEBUFFER_H
#define	FRAMEBUFFER_H

class FrameBuffer {
public:
    FrameBuffer();
    FrameBuffer(const FrameBuffer& orig);
    virtual ~FrameBuffer();
  
    int* GetLen() const{
        return len;
    };
    void SetSize(int* size) {
        this->size = size;
    }
    int* GetSize() const {
        return size;
    }
    void SetData(float* data) {
        this->data = data;
    }
    float* GetData() const {
        return data;
    }
private:
    float* data;
    int* len;
    int* size;
};

#endif	/* FRAMEBUFFER_H */

