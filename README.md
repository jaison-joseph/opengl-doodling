# OpenGL drawing 

## Some things you should know

* OpenGL is just a spec
* This code is based on https://learnopengl.com/Getting-started/OpenGL
* We're using OpenGL version 3.3
* OpenGL is a state machine, it has a bunch of variables to tell how OpenGL should currently operate
* The state of OpenGL is called the 'OpenGL context'
* State is changed by setting options, manipulating buffers and rendering using the current context
* You will see state-changing functions and state-using functions
* Everything in OpenGL is 3D. Transforming the 3D coordinates to 2D pixels is done by the graphics pipeline
* The pipeline has seversl stages, each one requiring as input the result of the previous part. The parts are parallelizable, so they run on GPU cores, each one called a shader.
* We can write our own shader using the OpenGL shading language(GLSL)
* There's 6 stages to the pipeline:
    * Vertex shader
        * Vertex is a collection of data for a 3D coordinates
        * input: a single vertex
        * does: transforms 3D coordinates (Normalized Device Coordinates to screen space coordinates) and basic processing on vertex attributes?
    * Shape assembly
        * input: all the vertices form vertex shader
        * does: assembles in the given "primitive shape"
    * Geometry shader:
        * input: vertices that form a primitive
        * does: createe new shapes by emitting new vertices, forming new primitives
    * Rasterization
        * input: result from geo. shader
        * does: 
            * map the primitives to screen pixels, creating 'fragments' for the fragment shader
            * clipping: remove fragments outside screen view, for better performance
    * Fragment shader
        * frag shader contains info about scene to calculate pixel color like light, shadow, light color, etc. 
        * does: 
            * calculate final color of a pixel
    * Tests & blending?
        * checks depth (stencil) value of a fragment, discards if it is behind another fragment
        * checks 'alpha values' (opacity) and blends the objects accordingly
* For most cases we only work with vertex and fragment shader
* The geometry shader is optional and usually left to its default shader. 
* In modern OpenGL, we need to define a vertex and fragment shader

## How to get this working on your machine

* For all platforms: refer [this](https://learnopengl.com/Getting-started/Creating-a-window)
* For a summary of what I installed on my machine to start writing OpenGL, here's a list:
    * [GLFW](https://www.glfw.org/): multi-platform library to create an OpenGL context, receive user input
    * [CMake](https://cmake.org/): We will use this to build solutions files for Visual Studio of the GLFW source code
    * [Visual Studio](https://visualstudio.microsoft.com/): nice powerful C++ editor. For this, we use it to build the solution file built by CMake into a library that can be linked by our OpenGL application. Also using it as the editor for this project.
    * [GLAD](): a library that finds the OpenGL functions that are used and stores them as function pointers. As for why this needs to be done, refer the GLAD section of [this](https://learnopengl.com/Getting-started/Creating-a-window)

## How to OpenGL

* The explanation is left as comments in **`ConsoleApplication1.cpp`**

## Things I've drawn

* Look at the images directory in the repo