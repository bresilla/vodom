#include <iostream>
#include <opencv2/opencv.hpp>
#include "Eigen/Dense"
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ei = Eigen;
namespace msg = spdlog;


void glfw_error_callback(int error, const char* description){
    msg::error("GLFW error: {}", description);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) || (key == GLFW_KEY_Q && action == GLFW_PRESS)){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    // keycode in ASCII
    msg::info("Key pressed: {}", (char)key);
}

int main(){
    if(!glfwInit()){
        msg::error("Failed to initialize GLFW");
        return -1;
    }
    msg::info("GLFW initialized");
    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window){
        msg::error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    msg::info("GLFW window created");

    glfwMakeContextCurrent(window);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
