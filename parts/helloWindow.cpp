// should create a blank window
// source: https://learnopengl.com/Getting-started/Hello-Window

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

// a resize window function
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clear off all of GLFW's allocated resources
    glfwTerminate();
    return 0;
}