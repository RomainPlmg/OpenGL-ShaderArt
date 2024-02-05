#ifndef OPENGL_HELLO_TRIANGLE_APP_H
#define OPENGL_HELLO_TRIANGLE_APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <cmath>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 450;

class Hello_triangle_App {
private:
    GLFWwindow* _window;
    GLuint _shaderProgram;

    void windowInit();
    void setupTriangle();
    void setupShaders();
    void renderLoop();

    void processInput();

public:
    void run();
    void clearApp();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
const char* readFromFile(const std::string& filePath);

#endif //OPENGL_HELLO_TRIANGLE_APP_H
