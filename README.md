# OpenGL drawing 

## Some things you should know

* OpenGL is just a spec
* This code is based on https://learnopengl.com/Getting-started/OpenGL
* We're using OpenGL version 3.3
* OpenGL is a state machine, it has a bunch of variables to tell how OpenGL should currently operate
* The state of OpenGL is called the 'OpenGL context'
* State is changed by setting options, manipulating buffers and rendering using the current context
* You will see state-changing functions and state-using functions

## How to get this working on your machine

* For all platforms: refer [this](https://learnopengl.com/Getting-started/Creating-a-window)
* For a summary of what I installed on my machine, here's a list:
    * [GLFW](https://www.glfw.org/): multi-platform library to create an OpenGL context, receive user input
    * [CMake](https://cmake.org/): We will use this to build solutions files for Visual Studio of the GLFW source code
    * [Visual Studio](https://visualstudio.microsoft.com/): nice powerful C++ editor. For this, we use it to build the solution file built by CMake into a library that can be linked by our OpenGL application. Also using it as the editor for this project.
    * [GLAD](): a library that finds the OpenGL functions that are used and stores them as function pointers. As for why this needs to be done, refer the GLAD section of [this](https://learnopengl.com/Getting-started/Creating-a-window)

