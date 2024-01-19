#include "utils.hpp"

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <fmt/format.h>
#include <spdlog/spdlog.h>



// namespace ei = Eigen;
namespace spd = spdlog;

int main(){
    utl::ImageLoader color = utl::ImageLoader("/doc/code/PROJECTS/vodom/dataset/rgb/");
    for(const auto& img : color){
        cv::imshow("img", img);
        spd::info("{}", color.info());
        
        auto key = cv::waitKey(1);
        if(key == 'q'){
            break;
        }
    }
}
