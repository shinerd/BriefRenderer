//
//  main.cpp
//  BriefRenderer
//
//  Created by Shine on 31/08/2019.
//  Copyright © 2019 Shinernd. All rights reserved.
//

#include <vector>
#include <cmath>
#include "tgaimage.hpp"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

Model *model = NULL;  // model.cpp model.h

const int width = 800;
const int height = 800;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    
    if (std::abs(x1-x0) < std::abs(y1-y0))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

//    int dx = x1-x0;
//    int dy = y1-y0;
//    int derror = std::abs(dy)*2;
//
//    float error = 0;
//    int y = y0;
    
    for (int x=x0; x<=x1; x++) {
        float t = (x-x0)/(float)(x1-x0);
        int y = y0 * (1.-t) + y1 * t;
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
//        error += derror;
//        if (error > dx) {
//            y += (y1>y0?1:-1);
//            error -= dx*2;
//        }
    }
    
}

int main(int argc, char** argv) {
    if (argc==2) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }
    
    TGAImage image(width, height, TGAImage::RGB);
    
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0.x + 1.) * width / 2.;
            int y0 = (v0.y + 1.) * height / 2.;
            int x1 = (v1.x + 1.) * width / 2.;
            int y1 = (v1.y + 1.) * height / 2.;
            line(x0, y0, x1, y1, image, white);
        }
    }
    
    image.flip_vertically();
    image.write_tga_file("output.tga");
    
    delete model;
    return 0;
}
