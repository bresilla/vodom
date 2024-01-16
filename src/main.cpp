#include <iostream>
#include <opencv2/opencv.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void glfw_error_callback(int error, const char* description){
    spdlog::error("GLFW error: {}", description);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    // keycode in ASCII
    spdlog::info("Key pressed: {}", (char)key);
}

int main(){
    if(!glfwInit()){
        spdlog::error("Failed to initialize GLFW");
        return -1;
    }
    spdlog::info("GLFW initialized");

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    glfwSetErrorCallback(glfw_error_callback);
    glfwSetKeyCallback(window, glfw_key_callback);

    if(!window){
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    spdlog::info("GLFW window created");

    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
