//
//  main.cpp
//  BriefRenderer
//
//  Created by Shine on 31/08/2019.
//  Copyright © 2019 Shinernd. All rights reserved.
//

#include <iostream> // for logging
#include <vector>
#include <cmath>
#include "tgaimage.hpp"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const int width  = 200;
const int height = 200;

int boundary_x(Vec2i v0, Vec2i v1, int y){
    float x;
    if (v1.y != v0.y){  // ...
        x = static_cast<float>(v1.x - v0.x) / (v1.y - v0.y) * (y - v0.y) + v0.x;
    }
    return static_cast<int>(x + 0.5);
}

int boundary_y(Vec2i v0, Vec2i v1, int x){
    float y;
    if (v1.x != v0.x){
        y = static_cast<float>(v1.y - v0.y) / (v1.x - v0.x) * (x - v0.x) + v0.y;
    }
    return static_cast<int>(y + 0.5);
}

void line(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(p0.x-p1.x)<std::abs(p0.y-p1.y)) {
        std::swap(p0.x, p0.y);
        std::swap(p1.x, p1.y);
        steep = true;
    }
    if (p0.x>p1.x) {
        std::swap(p0, p1);
    }
    
    if (p0.x != p1.x) {
        for (int x=p0.x; x<=p1.x; x++) {
            float t = (x-p0.x)/(float)(p1.x-p0.x);
            int y = p0.y*(1.-t) + p1.y*t +0.5;
            if (steep) {
                image.set(y, x, color);
            } else {
                image.set(x, y, color);
            }
        }
    } else {
        for (int y=p0.y; y<=p1.y; y++) {
            image.set(p0.x, y, color);
        }
    }
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image) {
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);
    
    Vec2i abp = Vec2i(boundary_x(t0, t2, t1.y), t1.y);  // (the boundary) A boundary point
    Vec2i bbp;
    
    for (abp.y = t0.y; abp.y <= t1.y; abp.y++) {
        abp.x = boundary_x(t0, t2, abp.y);
        bbp = Vec2i(boundary_x(t0, t1, abp.y), abp.y);
        line(abp, bbp, image, white);
    }
        
    for (abp.y = t1.y; abp.y <= t2.y; abp.y++) {
        abp.x = boundary_x(t0, t2, abp.y);
        bbp = Vec2i(boundary_x(t1, t2, abp.y), abp.y);
        line(abp, bbp, image, white);
    }
}

int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);
    
    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
    
    triangle(t0[0], t0[1], t0[2], image);
    triangle(t1[0], t1[1], t1[2], image);
    triangle(t2[0], t2[1], t2[2], image);
    
    
    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}
