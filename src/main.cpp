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


void featureDetection(cv::Mat img_1, std::vector<cv::Point2f>& points1){ 
    std::vector<cv::KeyPoint> keypoints_1;
    int fast_threshold = 20;
    bool nonmaxSuppression = true;
    cv::FAST(img_1, keypoints_1, fast_threshold, nonmaxSuppression);
    cv::KeyPoint::convert(keypoints_1, points1, std::vector<int>());
}

void featureTracking(cv::Mat img_1, cv::Mat img_2, std::vector<cv::Point2f>& points1, std::vector<cv::Point2f>& points2, std::vector<uchar>& status){ 
    cv::Size winSize = cv::Size(21,21);																								
    cv::TermCriteria termcrit = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, 0.01);
    cv::calcOpticalFlowPyrLK(img_1, img_2, points1, points2, status, err, winSize, 3, termcrit, 0, 0.001);
    int indexCorrection = 0;
    for( int i=0; i<status.size(); i++){ 
            cv::Point2f pt = points2.at(i- indexCorrection);
            if ((status.at(i) == 0)||(pt.x<0)||(pt.y<0)){
                if((pt.x<0)||(pt.y<0)){ status.at(i) = 0; }
                points1.erase (points1.begin() + i - indexCorrection);
                points2.erase (points2.begin() + i - indexCorrection);
                indexCorrection++;
            }
    }
}

int main(){
    utl::ImageLoader color = utl::ImageLoader("/doc/code/LEARN/vodom/dataset/rgbd_dataset_freiburg3_long_office_household/rgb/");
    for(const auto& img : color){
        cv::imshow("img", img);
        spd::info("{}", color.info());
        
        auto key = cv::waitKey(1);
        if(key == 'q'){
            break;
        }
    }
}
