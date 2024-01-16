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

    std::string baseapth = "/doc/code/LEARN/vodom/dataset/rgbd_dataset_freiburg3_long_office_household/";

    utl::ImageLoader loader = utl::ImageLoader(baseapth + "rgb/");

    for(const auto& img : loader){
        cv::imshow("image", img);
        cv::waitKey(1);
    }


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

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
