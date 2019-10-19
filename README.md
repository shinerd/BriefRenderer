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
### Check out the WIKI of this repository for more 'day's! <3
* [Day 1 (190901)](https://github.com/shinerd/BriefRenderer/wiki/Day-1-(190901))
* [Day 2 (190902)](https://github.com/shinerd/BriefRenderer/wiki/Day-2-(190902))
* [Day 3 (190903)](https://github.com/shinerd/BriefRenderer/wiki/Day-3-(190903))
* [Day 4 (190907)](https://github.com/shinerd/BriefRenderer/wiki/Day-4-(190907))
* [Day 5 (190909)](https://github.com/shinerd/BriefRenderer/wiki/Day-5-(190909))
* [Day 6 (190914)](https://github.com/shinerd/BriefRenderer/wiki/Day-6-(190914))
* [Day 7 (190916)](https://github.com/shinerd/BriefRenderer/wiki/Day-7-(190916))
* [Day 8 (191018)](https://github.com/shinerd/BriefRenderer/wiki/Day-8-(191018))
