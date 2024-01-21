#include "utils.hpp"

#include <opencv2/opencv.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <Eigen/Core>
#include <Eigen/Dense>



namespace ei = Eigen;
namespace spd = spdlog;

int main(){
    utl::ImageLoader color = utl::ImageLoader("/doc/code/PROJECTS/vodom/dataset/rgb/");
    
    ei::Matrix<float, 2, 3> matrix_23;

    ei::Vector<float, 3> v_3d;
    ei::Vector<float, 3> vd_3d;

    matrix_23 << 1, 2, 3, 4, 5, 6;

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            fmt::println("matrix_23({},{}) = {}", i, j, matrix_23(i, j));
        }
    }
    

    // for(const auto& img : color){
    //     cv::imshow("img", img);
    //     spd::info("{}", color.info());
        
    //     auto key = cv::waitKey(1);
    //     if(key == 'q'){
    //         break;
    //     }
    // }
}
