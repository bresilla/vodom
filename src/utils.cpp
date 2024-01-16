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
} // namespace utl