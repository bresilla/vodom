#include "utils.hpp"

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <fmt/format.h>
#include <spdlog/spdlog.h>



// namespace ei = Eigen;
namespace spd = spdlog;

int main(){
    utl::ImageLoader depth = utl::ImageLoader("/doc/code/PROJECTS/vodom/dataset/depth/");
    for(const auto& img : depth){
        cv::imshow("img", depth);
        spd::info("{}", depth.info());
        
        auto key = cv::waitKey(1);
        if(key == 'q'){
            break;
        }
    }
}
