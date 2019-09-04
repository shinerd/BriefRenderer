//
//  main.cpp
//  BriefRenderer
//
//  Created by Shine on 31/08/2019.
//  Copyright © 2019 Shinernd. All rights reserved.
//

#include "tgaimage.hpp"
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {  //  call image by reference
    bool steep = false;
    
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    
    if ((x1-x0) < std::abs(y1-y0))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    
    int dx = x1-x0;
    int dy = y1-y0;
    int derror = std::abs(dy)*2;
//    float derror = std::abs(dy/float(dx));
    
    float error = 0;
    int y = y0;
    
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error += derror;
        if (error > dx) {
//        if (error>.5) {
            y += (y1>y0?1:-1);
            error -= dx*2;
//            error -= 1.;
        }
    }
    
//    for (int x=x0; x<=x1; x++)
//    {
//        float t = (x-x0)/(float)(x1-x0);
//        int y = y0*(1.-t) + y1*t;
//        if (steep) {
//            image.set(y, x, color);
//        } else {
//            image.set(x, y, color);
//        }
//    }
}

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    
    line(20, 10, 60, 80, image, white);
    line(10, 50, 40, 20, image, red);
    
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
