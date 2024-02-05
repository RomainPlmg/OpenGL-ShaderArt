#include "Hello_triangle_App.h"

void Hello_triangle_App::run() {
    windowInit();
    setupTriangle();
    setupShaders();
    renderLoop();
    clearApp();
}

void Hello_triangle_App::windowInit() {
    /* Initialize the library */
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialized GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(WIDTH, HEIGHT , "Shader Art", NULL, NULL);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    /* Initialize GLAD after created the window context */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialized GLAD");
    }

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

void Hello_triangle_App::setupTriangle() {
    /******************/
    /* Hello Triangle */
    /******************/
    // float vertices[] = {
    //     // Position             // Color
    //     -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
    //      0.0f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
    //      0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f
    // };

    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
}

void Hello_triangle_App::setupShaders() {
    // Variables to debug shaders compilation
    int compileSuccess;
    char infoLog[512];

    // Vertex shader configuration
    std::cout << "Loading vertex shader... ";
    GLuint vertexShader;
    const GLchar* vertexShaderSource = readFromFile("../Shaders/Vertex.glsl");
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileSuccess);
    if (!compileSuccess) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR:SHADER:VERTEX:COMPILATION_FAILED" << std::endl;
        throw std::runtime_error(infoLog);
    }
    std::cout << "OK" << std::endl;

    // Fragment shader configuration
    std::cout << "Loading fragment shader... ";
    GLuint fragmentShader;
    const GLchar* fragmentShaderSource = readFromFile("../Shaders/Fragment.glsl");
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileSuccess);
    if (!compileSuccess) {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR:SHADER:FRAGMENT:COMPILATION_FAILED" << std::endl;
        throw std::runtime_error(infoLog);
    }
    std::cout << "OK" << std::endl;

    // Shader program creation
    std::cout << "Create shader program... ";
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &compileSuccess);
    if(!compileSuccess) {
        glGetProgramInfoLog(_shaderProgram, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR:SHADER:PROGRAM::LINK_FAILED" << std::endl;
        throw std::runtime_error(infoLog);
    }
    std::cout << "OK" << std::endl;

    // After creating shader program, delete shaders to save memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}

void Hello_triangle_App::renderLoop() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glUseProgram(_shaderProgram);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(_window)) {
        processInput();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        int timeUniformLocation = glGetUniformLocation(_shaderProgram, "iTime");
        int resolutionUniformLocation = glGetUniformLocation(_shaderProgram, "iResolution");
        glUniform1f(timeUniformLocation, glfwGetTime());

        int width, height;
        glfwGetWindowSize(_window, &width, &height);
        glUniform3f(resolutionUniformLocation, width, height, 0.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(_window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void Hello_triangle_App::clearApp() {
    glfwTerminate();
}

void Hello_triangle_App::processInput() {
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, true);
    }
}

/* Function definitions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

const char* readFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::string runtimeErrorMsg = "Unable to open file \'" + filePath + "\'";
        throw std::runtime_error(runtimeErrorMsg.c_str());
    }

    std::string fileStr;

    char carac = file.get();
    for (int i = 0; carac != EOF; i++) {
        fileStr.push_back(carac);
        carac = file.get();
    }

    file.close();
    const char* fileStrChar = fileStr.c_str();
    

    return fileStrChar;
}