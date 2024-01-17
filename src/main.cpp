#include "utils.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <fmt/format.h>
#include <spdlog/spdlog.h>



namespace ei = Eigen;
namespace spd = spdlog;


int main(){
    utl::ImageLoader color = utl::ImageLoader("/doc/code/LEARN/vodom/dataset/rgbd_dataset_freiburg3_long_office_household/rgb/");
    for(const auto& img : color){
        cv::imshow("img", img);
        spd::info("{}", color.info());
        auto key = cv::waitKey(0);
        if(key == 'q'){
            break;
        }
    }
}
