/* 
 * File:   FrameBuffer.h
 * Author: zoizoi
 *
 * Created on 30 January 2011, 20:29
 */

#ifndef FRAMEBUFFER_H
#define	FRAMEBUFFER_H
#include "vtkEssentials.h"

class FrameBuffer {
public:
    FrameBuffer(vtkSmartPointer<vtkRenderWindow> renderWindow);
    FrameBuffer(const FrameBuffer& orig);
    virtual ~FrameBuffer(){
        delete data;
    };

    void grabData(){
        data = renderWindow->GetRGBAPixelData(0, 0, (size[0] - 1), (size[1] - 1), 0);
    }
    
    float* getData(){
        return data;
    }

    int getLen(){
        return len;
    }

private:
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    float* data;
    int* size;
    int len;
};

#endif	/* FRAMEBUFFER_H */

