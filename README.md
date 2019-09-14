# BriefRenderer
Making my first own Brief Renderer (for Study OpenGL)
<br>
<br>
<br>
## Day 1 (190901)
* Downloaded the codes from ssloy/tinyrenderer. [Link](https://github.com/ssloy/tinyrenderer)
* Figured out how to run the codes with GNU make.
<br>

### GNU make
<br>
I didn't even know how to make output with these codes.
I googled tga output, makefiles, xcode and finally figured out how they work.
<br>
<br>

#### 1. G++ is a compiler for C++ language.
```
SYSCONF_LINK = g++
```
You can check it out at ./Makefile
<br>
<br>
#### 2. What I installed are not sure to be needed.
I installed *homebrew* and with brew, I installed *arm-gcc-bin* and *coreutils*.
[Brew](https://brew.sh/index_ko)
`brew tap osx-cross/arm` `brew install arm-gcc-bin` `brew install coreutils`.
<br>
<br>
#### 3. And I built the rerderer for the first time.
Move to the directory where *Makefile* is.
![move](https://ifh.cc/g/BThxS.jpg)
<br>
`make`
![make](https://ifh.cc/g/3WhPB.jpg)
<br>
Run the .exe file.
`./main`
![run](https://ifh.cc/g/BqWTJ.jpg)
<br>
Then the output is created.
![output](https://ifh.cc/g/6ugvl.jpg)
<br>
<br>
#### 4. Errors that I've met today.
`
No targets specified and no makefile found. Stop.
`  
I had to move to the exact directory(where *Makefile* is).
<br>

`
missing seperator. Stop.
`  
I had to edit *Makefile*. It requires real tab instead of 4 white spaces. I edited it with text editor.
<br>
<br>
<br>
## Day 2 (190902)
* Bresenham’s Line Drawing Algorithm
<br>

### Line Drawing
<br>
I followed the lecture of ssloy, but before read his code, I wrote my own code.
<br>
<br>

#### 1. I dotted the dots at regular intervals.
Line is a set of dots. So I tried to make dots between the points.
![dots](https://ifh.cc/g/UUNK7.jpg)
<br>
```cpp
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    for(float f=0.; f<1.; f+=0.1)
    {
        int x = x0 + (x1 - x0) * f;
        int y = y0 + (y1 - y0) * f;
        image.set(x, y, color);
    }
}
```
<br>

![output1](https://ifh.cc/g/ZSldo.jpg)
<br>
<br>
#### 2. I dotted the dots as many as pixels.
<br>

Then I figured out that I already know the number of pixels. That means I can get the number of dots between the points.    
This is the code in the lecture:
```cpp
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    for (int x=x0; x<=x1; x++) { 
        float t = (x-x0)/(float)(x1-x0); 
        int y = y0*(1.-t) + y1*t;
        image.set(x, y, color); 
    } 
}
```
Line 3~4 is the way to find Inner Point (a x n + b x m) / (m + n).
I thought it might have some problems.
1) It doesn't care the number of pixels between y0 and y1. It depends on x0 and x1.
2) So, if the distance between x0 and x1 is bigger than y0 and y1, the output looks like stairs.
3) If the distance between x0 and x1 is smaller than y0 and y1, the output has dots, not a connected line.
4) And also, I should think about the case that x1(or y1) is smaller than x0(or y0). (I've thought about this problem since number 1.)
<br>

![output2](https://ifh.cc/g/tOU2G.png) : image from ssloy's wiki
<br>
<br>
    
![sudo1](https://ifh.cc/g/8SKuD.jpg)
*std:: swap* and *std::abs* is in the *cmath*
<br>

```cpp
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
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
    
    for (int x=x0; x<=x1; x++)
    {
        float t = (x-x0)/(float)(x1-x0);
        int y = y0*(1.-t) + y1*t;
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}
```
<br>

![output3](https://ifh.cc/g/uuL9x.jpg)
<br>
<br>
#### 3. Problems that I've met today.
`-`  
It built successfully, but the output had no line(dots).
![nolinecode](https://ifh.cc/g/LBp8f.jpg)
![nolinerun](https://ifh.cc/g/fY2cD.jpg)
![nolineoutput](https://ifh.cc/g/Erp8E.jpg)
<br>
I had to call TGAImage by reference, so that it can remain the set of the function.
<br>

`-`  
I had not thought about de-transpose after I transpoesd x and y.
In the lecture, the code has a steep as a flag.
Before I fixed:
![nosteepcode](https://ifh.cc/g/nSCND.jpg)
![nosteepoutput](https://ifh.cc/g/fqTG9.jpg)
Compared to the output of number 1, the white line is transpoesed.
<br>
<br>
<br>
## Day 3 (190903)
* Optimized the code by removing unnecessary calling and copies.
<br>

### Optimization
<br>

Arccording to the lecture, I can profile the program with gprof.
[gprof](https://users.cs.duke.edu/~ola/courses/programming/gprof.html)  
For this time, let's just see the lecture.
<br>
<br>

#### 1. Reduce the time which is spent on calling line( )
```
%   cumulative   self              self     total 
time   seconds   seconds    calls  ms/call  ms/call  name 
69.16      2.95     2.95  3000000     0.00     0.00  line(int, int, int, int, TGAImage&, TGAColor) 
19.46      3.78     0.83 204000000     0.00     0.00  TGAImage::set(int, int, TGAColor) 
8.91      4.16     0.38 207000000     0.00     0.00  TGAColor::TGAColor(TGAColor const&) 
1.64      4.23     0.07        2    35.04    35.04  TGAColor::TGAColor(unsigned char, unsigned char, unsigned char, unsigned char) 
0.94      4.27     0.04                             TGAImage::get(int, int)
```
<br>

This is the output of gprof from the [lecture](https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham’s-Line-Drawing-Algorithm).
70% of the time is spent on calling line( ).
<br>
```cpp
int dx = x1-x0;
int dy = y1-y0;
float derror = std::abs(dy/float(dx));

float error = 0;
int y = y0;

for (int x=x0; x<=x1; x++) {
    if (steep) {
        image.set(y, x, color);
    } else {
        image.set(x, y, color);
    }
    error += derror;
    if (error>.5) {
        y += (y1>y0?1:-1);
        error -= 1.;
    }
}
```
<br>

So that I can take out the division with the same divisior(`float t = (x-x0)/(float)(x1-x0);  int y = y0*(1.-t) + y1*t;`) of the loop. Now only setters are in the loop.
It was hard to figure out what the algorithm means.
![optmz1](https://ifh.cc/g/lRrRl.jpg)
<br>
The float numbers in the table is the value of *error*.
<br>
But what if I take just the first calculation out of the loop? I wanted to try, but maybe later.
<br>
<br>

#### 2. Remove the floating point
```
%   cumulative   self              self     total 
time   seconds   seconds    calls  ms/call  ms/call  name 
69.16      2.95     2.95  3000000     0.00     0.00  line(int, int, int, int, TGAImage&, TGAColor) 
19.46      3.78     0.83 204000000     0.00     0.00  TGAImage::set(int, int, TGAColor) 
8.91      4.16     0.38 207000000     0.00     0.00  TGAColor::TGAColor(TGAColor const&) 
1.64      4.23     0.07        2    35.04    35.04  TGAColor::TGAColor(unsigned char, unsigned char, unsigned char, unsigned char) 
0.94      4.27     0.04                             TGAImage::get(int, int)
```
<br>

To remove the floating point, let's assign the value which is equal to the origin x  *2* x *dx*.
![optmz2](https://ifh.cc/g/mdF60.jpg)
```cpp
int dx = x1-x0;
int dy = y1-y0;
int derror = std::abs(dy)*2;

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
        y += (y1>y0?1:-1);
        error -= dx*2;
    }
}
```
![optmz3](https://ifh.cc/g/a1NXU.jpg)
<br>
The result:
```
%   cumulative   self              self     total 
time   seconds   seconds    calls  ms/call  ms/call  name 
42.77      0.91     0.91 204000000     0.00     0.00  TGAImage::set(int, int, TGAColor) 
30.08      1.55     0.64  3000000     0.00     0.00  line(int, int, int, int, TGAImage&, TGAColor) 
21.62      2.01     0.46 204000000     0.00     0.00  TGAColor::TGAColor(int, int) 
1.88      2.05     0.04        2    20.02    20.02  TGAColor::TGAColor(unsigned char, unsigned char, unsigned char, unsigned char) 
```
<br>
<br>

![optmz4](https://ifh.cc/g/VIBG9.jpg)
It works really fast now.
<br>
<br>
<br>
## Day 4 (190907)
* Completed the wireframe rendering
<br>

### Wireframe Rendering
<br>

#### 1. I copied the code.
I copied the code below without copy-and-paste, I typed it.
'*main.cpp*'
I copied the code and object below with copy-and-paste.
'*geometry.h*', '*model.h*', '*model.cpp*', './obj'
[Link](https://github.com/ssloy/tinyrenderer/tree/f6fecb7ad493264ecd15e230411bfb1cca539a12)

#### 2. I guessed how this code works.
1) *model.h* and *model.cpp* would contain the class to make objects, models.
2) *main.cpp* draws line using the function I've made, as many as the object (model) needs.

#### 3. Rendering Result
![wireframe](https://ifh.cc/g/dkWBN.jpg)

#### 4. Problems I've met today
`called object type 'int' is not a function or function pointer`    
`'tgaimage.h' file not found`    
I just made some mistakes while I was typing the code.
<br>
<br>

`-`
My first output was a little weird.
![myoutput](https://ifh.cc/g/M4yYu.jpg)
<br>
The left one is mine, and the right one is the origin.

So I found the difference between my code and the code of the lecture.
![mycode](https://ifh.cc/g/jD6vy.jpg)
<br>
It was because the order I swapping x with y, and 0 with 1.
![mysudo](https://ifh.cc/g/T6dPV.jpg)
<bt>
Of course, when I set the color, it transposed the x and y. But before it, when I set the x and y, I need to make sure that they are set in order left-to-right.
So I switched the *if* loops and put *std::abs* to *(x1-x0)* too.
```cpp
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
```
<br>
<br>
<br>

## Day 5 (190909)
* Reversed the code
<br>

### Wireframe Rendering (Reversing)
<br>

#### 1. I analyzed *Model* class.
I didn't get the exact meaning, but I could guess most of it.

#### 2. I analyzed *main.cpp* .
Now I can understand furthermore.

#### 3. Questions I've had today
```cpp
// model.h
class Model {
private:
    std::vector<Vec3f> verts_;
    std::vector<std::vector<int> > faces_;
public:
    ...
};
```
```cpp
// model.cpp
Model::Model(const char *filename) : verts_(), faces_() {  // consturctor of Model
    ...
    char trash;
    if (...) {
        ...
        verts_.push_back(v);
    } else if (...) {
        ...
        faces_.push_back(f);
    }
}
```
I'm guessing verts_ and faces_ is vector variables, and to use them in a class, I have to inherit the constructors of the vectors. But I still don't know why.

```cpp
char trash; 
if (!line.compare(0, 2, "v ")) { 
    iss >> trash;
    Vec3f v;
    for (int i=0;i<3;i++) iss >> v.raw[i];
    verts_.push_back(v);
} else if (!line.compare(0, 2, "f ")) { 
    std::vector<int> f;
    int itrash, idx;
    iss >> trash;
    while (iss >> idx >> trash >> itrash >> trash >> itrash) {
        idx--; // in wavefront obj all indices start at 1, not zero
        f.push_back(idx);
    }
    faces_.push_back(f);
}
```
I'm guessing that it means if it is v, push to verts_, else if it is f, push to faces_. I wish I could open the object file as code so that I can figure out what it means.
<br>
<br>
Other comments are in the code.
<br>
<br>
<br>

## Day 5 (190909)
* Filled triangles
<br>

### Filling Triangles
<br>

#### 1. I got the code for making three empty triangles.
```cpp
// main.cpp
#include <vector>
#include <cmath>
#include "tgaimage.hpp"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const int width  = 200;
const int height = 200;

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

    for (int x=p0.x; x<=p1.x; x++) {
        float t = (x-p0.x)/(float)(p1.x-p0.x);
        int y = p0.y*(1.-t) + p1.y*t;
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
    line(t0, t1, image, color);
    line(t1, t2, image, color);
    line(t2, t0, image, color);
}

int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);

    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};

    triangle(t0[0], t0[1], t0[2], image, red);
    triangle(t1[0], t1[1], t1[2], image, white);
    triangle(t2[0], t2[1], t2[2], image, green);


    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
```
The output of the code is like below.
![emptytriangles](https://ifh.cc/g/9pDBr.jpg)
