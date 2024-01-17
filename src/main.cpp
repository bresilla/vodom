#include "utils.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>



namespace ei = Eigen;
namespace spd = spdlog;


void glfw_error_callback(int error, const char* description){
    spd::error("GLFW error: {}", description);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) || (key == GLFW_KEY_Q && action == GLFW_PRESS)){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    // keycode in ASCII
    if (action == GLFW_PRESS){
        spd::info("Key pressed: {}", (char)key);
    }
}

int main(){
    if(!glfwInit()){
        spd::error("Failed to initialize GLFW");
        return -1;
    }
    spd::info("GLFW initialized");
    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window){
        spd::error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    spd::info("GLFW window created");

    glfwMakeContextCurrent(window);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSwapInterval(1);


    utl::ImageLoader loader = utl::ImageLoader("/doc/code/LEARN/vodom/dataset/rgbd_dataset_freiburg3_long_office_household/rgb/");
    cv::Mat img = loader.next();


    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int vao, vbo, ebo;

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    const char* vertex_shader_source = R"GLSL(
        #version 330 core
        layout (location = 0) in vec3 vs_pos;
        layout (location = 1) in vec2 vs_uv;
        out vec2 uv;
        void main(){
            gl_Position = vec4(vs_pos, 1.0);
            uv  = vs_uv;
        }
    )GLSL";

    const char* image_fs_source = R"GLSL(
        #version 330 core
        out vec4 fragment_color;
        in vec2 uv;
        void main(){
            fragment_color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )GLSL";


    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
