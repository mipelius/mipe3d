# Mipe3D
Mipe3D is a skeletal animation demo.
# Dependencies
Mipe3D uses low level C++ libraries which are not included in the repo. In order to build the project you need to download [SDL2-2.0.9](https://www.libsdl.org/release/SDL2-devel-2.0.9-VC.zip) and [glew-2.1.0](https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download) and put them into following folders:
`path/to/mipe3d/external/SDL2-2.0.9`
`path/to/mipe3d/external/glew-2.1.0`
# Build and run
If additional depencies were installed properly, you can build the project by opening the project in visual studio and selecting `Build/Build Solution`. For running the project, you need to copy `.dll`files from external libraries into runtime working directories. For example if you wish to run `Debug/x64` you need to copy following files into `path/to/mipe3d/x64/Debug/`:
* `SDL2-2.0.9/lib/x64/SDL2.dll`
* `glew-2.1.0/bin/Release/x64/glew32.dll` 
