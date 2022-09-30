// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

// a resize window function
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {

    // initialize GLFW
    glfwInit();

    // setting OPENGL version to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // setting the OPENGL profile to core-profile only gives us a subset of OPENGL's features
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creating a window (width, height, name, yada, yada)
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // initializing GLAD, returning if it failed
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // giving the size of the rendering window so that OPENGL knows how we want the data & coordinates wrt the window
    glViewport(0, 0, 1920, 1080);

    // 'registering' the function to be called when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // vertices for the triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // creating a vertex buffer object; stores vertices in GPU mem
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // binding the buffer to the GL_ARRAY_BUFFER, the type of a vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //copy the defined buffer to the buffer's mem
    // the 4th param tells how we want the graphics card to manage the data 
    // there's 3 options: 
    // GL_STREAM_DRAW: set once used rarely
    // GL_STATIC_DRAW: set once used frequenty
    // GL_DYNAMIC_DRAW: set multiple and used frequently)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // so now we have stored the vertex data in GPU memory, mananged by a vertex buffer object called VBO

    // the vertex shader

    // vec3 is a vector that stores 3 floats (hence the suffix 3)
    // the input vertex is declared in the vec3 vector
    // To set the output of the vertex shader we have to assign the position data to the predefined gl_Position

    // this shader does no processing on the input; it simply forwards the input vector to the output
    // the 4th param in the vec$ argument is the position of the vertex attribute in the shader
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    // to compile the shader, we call a function to create a 'vertex' kind of shader, then attach the code for th shaer to it and compile
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(shader obj, # of strings, strings, NULL);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // checking to see if the compilation was successful
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader

    // very similar to the vertex shader

    // source for the fragment shader
    // the point of this basic fragment shader is simply setting the colors of the pixels, we choose orange
    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    // create fragment shader obejct, attach code for our frag shader, compile
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // shader program: the final linked version of multiple shaders, we activate this program to render objects

    // creating a program obj
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // attaching our shaders to the program and then linking the program
    // note that the order in which we attach is important, vertex, followed by fragment
    // improper order will give a linking error
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    // checking to see if the linking was successful
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // since we linked the vertex and fragment shaders to the program object, we can discard them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // by now, we have sent the input vertex data to the GPU, along with instructions on how to process the vertex data
    // within the shaders. 
    // We still need to instruct openGL how to interpret vertex data in memory, connect data to the shader attributes

    // we will create a Vertex Array Object (VAO)
    // stores the configs to draw an object into a container. Precisely
    // 1. Calls to glEnableVertexAttribArray or glDisableVertexAttribArray.
    // 2. Vertex attribute configurations via glVertexAttribPointer.
    // 3. Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer.
    // can be bound like the VBO 
    // allows us to just configure the vertex attribute pointers once, subsequent calls are replaced by binding the VAO

    // creating a VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // binding the VAO
    glBindVertexArray(VAO);
    
    // copy vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 2. then set the vertex attributes pointers
    /*
    * the arguments to glVertexAttribPointer are
    * a. the location of the position vertex attribute in the shader (the 4th argument in instantiating the vec4 in the vertex shader
    * b. size of the vertex attribute
    * c. type of data
    * d. to normalize or not; if datatype is int, byte, then true; else false
    * e. offset for telling where the position data begins in the buffer (it's at the start, so offset is 0)
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // the code that renders and draws the triangle will be in the render loop


    
    // render loop

    /*
    * The pseudocode for the render loop
    * while (windowNotAskedToClose) {
    *   
    *   get user input and process it
    *   
    *   rendering commands
    * 
    *   check and call events
    *   swap buffers
    * }
    */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // triangle drawing
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clear off all of GLFW's allocated resources
    glfwTerminate();
    return 0;
}