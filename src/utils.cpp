#include "utils.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>

#include <opencv2/opencv.hpp>
#include "Eigen/Dense"
#include <fmt/format.h>
#include <spdlog/spdlog.h>



namespace ei = Eigen;
namespace spd = spdlog;
namespace fs = std::filesystem;

namespace utl {
    std::string timestring(long long timestamp){
        std::time_t t = timestamp;
        std::tm* tm = std::localtime(&t);
        char buf[32];
        std::strftime(buf, 32, "%Y-%m-%d %H:%M:%S", tm);
        return std::string(buf);
    }

    std::vector<std::pair<std::string, long long>> get_image_paths(const std::string& file_path_string){
        std::vector<std::pair<std::string, long long>> paths;
        fs::path file_path = file_path_string;
        if(!fs::exists(file_path)){
            spd::error("Path does not exist: {}", file_path_string);
            return paths;
        }
        if(!fs::is_directory(file_path)){
            spd::error("Path is not a directory: {}", file_path_string);
            return paths;
        }
        for(const auto& entry : fs::directory_iterator(file_path)){
            if(!fs::is_regular_file(entry)){
                spd::warn("Skipping non-regular file: {}", entry.path().string());
                continue;
            }
            if(entry.path().extension() != ".png"){
                spd::warn("Skipping non-png file: {}", entry.path().string());
                continue;
            }
            std::string filename = entry.path().filename().string();
            std::string timestamp_string = filename.substr(0, filename.find("."));
            long long timestamp = std::stoll(timestamp_string);
            paths.push_back(std::make_pair(entry.path().string(), timestamp));
        }
        std::sort(paths.begin(), paths.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });
        return paths;
    }

    ImageLoader::ImageLoader(const std::string& file_path_string){
        paths = get_image_paths(file_path_string);
        index_ = 0;
    }

    cv::Mat ImageLoader::next(){
        return _get(index_++);
    }

    void ImageLoader::reset(){
        index_ = 0;
    }

    int ImageLoader::_len(){
        return paths.size();
    }

    std::string ImageLoader::path(){
        return paths[index_].first;
    }

    cv::Mat ImageLoader::_get(int index){
        if(index < 0 || index >= _len()){
            spd::error("Index out of range: {}", index);
            return cv::Mat();
        }
        
        fs::path image_path = paths[index].first;
        if(!fs::exists(image_path)){
            spd::error("Path does not exist: {}", image_path.string());
            return cv::Mat();
        }

        if(!fs::is_regular_file(image_path)){
            spd::error("Path is not a regular file: {}", image_path.string());
            return cv::Mat();
        }

        if(image_path.extension() != ".png"){
            spd::error("Path is not a png file: {}", image_path.string());
            return cv::Mat();
        }
        
        cv::Mat image = cv::imread(image_path.string(), cv::IMREAD_UNCHANGED);
        if(image.empty()){
            spd::error("Failed to read image: {}", image_path.string());
            return cv::Mat();
        }
        return image;
    }

    ImageLoader::Iterator::Iterator(ImageLoader* loader, int index){
        loader_ = loader;
        index_ = index;
    }

    ImageLoader::Iterator& ImageLoader::Iterator::operator++(){
        index_++;
        return *this;
    }

    cv::Mat ImageLoader::Iterator::operator*() const{
        return loader_->_get(index_);
    }

    bool ImageLoader::Iterator::operator!=(const Iterator& other) const{
        return index_ != other.index_;
    }

    bool ImageLoader::Iterator::operator==(const Iterator& other) const{
        return index_ == other.index_;
    }


    
} // namespace utl