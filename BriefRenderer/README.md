# BriefRenderer
Making my first own Brief Renderer (for Study OpenGL)   
   

## Day 1 (190901)
* Downloaded the codes from ssloy/tinyrenderer. [Link](https://github.com/ssloy/tinyrenderer)
* Figured out how to run the codes with GNU make.
     
    
### GNU make

I even didn't know how to make output with these codes.
I googled tga output, makefiles, xcode and finally figured out how day works.

#### 1. G++ is a compiler for C++ language.
```
SYSCONF_LINK = g++
```
You can check it out at ./Makefile
    
    
#### 2. What I installed are not sure to be needed.
I installed *homebrew* and with brew, I installed *arm-gcc-bin* and *coreutils*.
[Brew](https://brew.sh/index_ko)
`brew tap osx-cross/arm` `brew install arm-gcc-bin` `brew install coreutils`.
   
   
#### 3. And I built the rerderer for the first time.
Move to the directory where *Makefile* is.
![move](https://ifh.cc/g/BThxS.jpg)
    
`make`
![make](https://ifh.cc/g/3WhPB.jpg)
    
Run the .exe file.
`./main`
![run](https://ifh.cc/g/BqWTJ.jpg)
    
Then the output is created.
![output](https://ifh.cc/g/6ugvl.jpg)
   
   
#### 4. Errors that I met today.
`
No targets specified and no makefile found. Stop.
`
    
I had to move to the exact directory(where *Makefile* is).
   
    
`
missing seperator. Stop.
`
    
I had to edit *Makefile*. It requires real tab instead of 4 white spaces. I edited it with text editor.


## Day 2 (190902)
* Bresenham’s Line Drawing Algorithm
    
### Line Drawing

I followed the lecture of ssloy, but before read his code, I wrote my own code.

#### 1. I dotted the dots at regular intervals.
Line is a set of dots. So I tried to make dots between the points.
![dots](https://ifh.cc/g/UUNK7.jpg)
    
```
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    for(float f=0.; f<1.; f+=0.1)
    {
        int x = x0 + (x1 - x0) * f;
        int y = y0 + (y1 - y0) * f;
        image.set(x, y, color);
    }
}
```
    
![output1](https://ifh.cc/g/ZSldo.jpg)
    
    
#### 2. I dotted the dots as many as pixels.

Then I figured out that I already know the number of pixels. That means I can get the number of dots between the points.    
This is the code in the lecture:
```
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

![output2](https://ifh.cc/g/tOU2G.png) : image from ssloy's wiki

    
*std:: swap* and *std::abs* is in the *<cmath>*
```
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
![output3](https://ifh.cc/g/uuL9x.jpg)


#### 3. Problems that I met today.
`-`
    
It built successfully, but the output had no line(dots).
![nolinecode](https://ifh.cc/g/LBp8f.jpg)
![nolinerun](https://ifh.cc/g/fY2cD.jpg)
![nolineoutput](https://ifh.cc/g/Erp8E.jpg)
    
I had to call TGAImage by reference, so that it can remain the set of the function.
    
    
`-`

I had not thought about de-transpose after I transpoesd x and y.
In the lecture, the code has a steep as a flag.
Before I fixed:
![nosteepcode](https://ifh.cc/g/nSCND.jpg)
![nosteepoutput](https://ifh.cc/g/fqTG9.jpg)
Compared to the output of number 1, the white line is transpoesed.
