# Dont forget folowing

-  Sample code was taken from https://github.com/MicrocontrollersAndMore/OpenCV_3_Windows_10_Installation_Tutorial

- you need to Install the OpenCV 3.1.0.0 library on your system

And fter that you need to place files "opencv_world310.dll" and "opencv_world310d.dll"
to the folder "..\OpenCvX64ConsApp\OpenCvX64ConsApp" to launch and debug the aookication

- Add some lines in the Project Properties:

Configuration Properties->VC++ Directories
Include Directories = C:\C_Libraries\opencv - 3 - 1\build\include;
Library Directories = C:\C_Libraries\opencv - 3 - 1\build\x64\vc12\lib;

- I also had a problem with debuging the project, after I have set the Properties of the Solution Configuration to x64.

I was able to build and launch the project, BUT breakpoints were ignored and I got such Error 
"debugging information cannot be found or does not match. No symbols loaded."
Here is the Solution for that isue:

To enable debugging :
1) Project->HelloWorld Properties
2) "Configuration Properties -> C/C++ -> General"
3) On the right, change "Debug Information Format" to "Program Database For Edit And Continue (/ZI)"
4) "Configuration Properties -> C/C++ -> Optimization"
5) On the right, change "Optimization" to "Disabled (/Od)"
6) "Configuration Properties -> C/C++ -> Linker"
7) On the left, select "Debugging"
8) On the right, change "Generate Debug Info" to "Yes"
9) Click ok
10) Set your breakpoints
11) Rebuild your application

Also when running your application use Ctrl + F5 to build and run it, this keeps the console window open long enough for you to see your output.

