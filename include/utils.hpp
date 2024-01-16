// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

namespace utl {
    std::string timestring(long long timestamp);
    std::vector<std::pair<std::string, long long>> get_image_paths(const std::string& file_path_string);

    class ImageLoader{
        public:
            ImageLoader(const std::string& file_path_string);
            cv::Mat next();
            void reset();
            std::string path();

            class Iterator : public std::iterator<std::input_iterator_tag, cv::Mat> {
                public:
                    explicit Iterator(ImageLoader* loader, int index);
                    Iterator& operator++();
                    cv::Mat operator*() const;
                    bool operator!=(const Iterator& other) const;
                    bool operator==(const Iterator& other) const;
                private:
                    ImageLoader* loader_;
                    int index_;
            };

            Iterator begin() { return Iterator(this, 0); }
            Iterator end() { return Iterator(this, _len()); }
        
        private:
            int _len();
            cv::Mat _get(int index);
            std::vector<std::pair<std::string, long long>> paths;
            int index_;
    };

}

#endif // UTILS_H