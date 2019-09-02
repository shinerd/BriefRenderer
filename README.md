# BriefRenderer
Making my first own Brief Renderer (for Study OpenGL)   
   

## Day 1 (190901)
* Downloaded the codes from ssloy/tinyrenderer. [Link](https://github.com/tinyrenderer)
* Figured out how to run the codes with GNU make.
     
    
### GNU make
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
   
   
#### 4. Errors that I met
```
No targets specified and no makefile found. Stop.
```
I had to move to the exact directory(where *Makefile* is).
   
```
missing seperator. Stop.
```
I had to edit *Makefile*. It requires real tab instead of 4 white spaces. I edited it with text editor.
