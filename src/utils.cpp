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
        std::string timestring = fmt::format("{:010d}", timestamp);
        return timestring;
    }

    std::vector<std::string> get_paths_from_dir(fs::path file_path){
        std::vector<std::string> paths;
        for(const auto& entry : fs::directory_iterator(file_path)){
            if(!fs::is_regular_file(entry)){
                spd::warn("Skipping non-regular file: {}", entry.path().string());
                continue;
            }
            if(entry.path().extension() != ".png"){
                spd::warn("Skipping non-png file: {}", entry.path().string());
                continue;
            }
            paths.push_back(entry.path().string());
        }
        std::sort(paths.begin(), paths.end(), [](const auto& a, const auto& b){
            return a < b;
        });
        return paths;
    }

    std::vector<std::string> get_paths_from_txt(fs::path file_path){
        spd::error("Not implemented");
    }

    std::vector<std::string> get_paths(std::string file_path_string){
        std::vector<std::string> paths;
        fs::path file_path = file_path_string;
        if(!fs::exists(file_path)){
            spd::error("Path does not exist: {}", file_path_string);
            return paths;
        }
        if(!fs::is_directory(file_path)){
            spd::info("Getting paths from txt file: {}", file_path_string);
            return get_paths_from_txt(file_path);
        } else {
            spd::info("Getting paths from directory: {}", file_path_string);
            return get_paths_from_dir(file_path);
        }
    }

    ImageLoader::ImageLoader(const std::string& file_path_string){
        paths = get_paths(file_path_string);
        index_ = 0;
    }

    bool ImageLoader::has_next(){
        return index_ < len();
    }

    cv::Mat ImageLoader::next(){
        if(!has_next()){
            spd::error("No more images");
            return cv::Mat();
        }
        index_++;
        return _get(index_ - 1);
    }

    cv::Mat ImageLoader::curr(){
        if(index_ == 0){
            spd::error("No current image, please call next() first");
            return cv::Mat();
        }
        return _get(index_);
    }

    void ImageLoader::reset(){
        index_ = 0;
        iterator_->index_ = index_;
    }

    int ImageLoader::len(){
        return paths.size();
    }

    std::string ImageLoader::info(){
        return fmt::format("path: {}", paths[index_]);
    }

    cv::Mat ImageLoader::_get(int index){
        if(index < 0 || index >= len()){
            spd::error("Index out of range: {}", index);
            return cv::Mat();
        }
        
        fs::path image_path = paths[index];
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
        loader_->index_ = index_;
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

    void ImageLoader::Iterator::reset(){
        index_ = 0;
        loader_->index_ = index_;
    }

    
} // namespace utl