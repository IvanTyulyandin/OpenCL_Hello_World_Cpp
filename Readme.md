# OpenCL "Hello, world" with C++ 
This is the implementation of OpenCL "Hello, world" using C++ as the language for the host program.

## Details
I used OpenCL version 2.1.
Error checking is missed in some places — you can add it if needed.

Since some functionality from elder versions of OpenCL is deprecated in that version, I replaced ```cl::CommandQueue::enqueueTask``` with ```cl::CommandQueue::enqueueNDRangeKernel```.
I did not found any example of such replacement, that is why I publish code.

If you wish to build using Clang in release mode and in a separate folder, run
```compileClangRelease.sh``` and then ```runInBuildDir.sh```.

## Requirements
1. Build tools and CMake
```bash
$ sudo apt-get install build-essentials cmake
```
2. OpenCL
```bash 
$ sudo apt-get install ocl-icd-opencl-dev opencl-headers
```
3. Package that enables runnig openCL on most modern Intel CPUs
```bash 
sudo apt install beignet
```
