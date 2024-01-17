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
            cv::Mat curr();
            bool has_next();
            int len();
            void reset();
            std::string info();
            int indexy(){ return index_;}

            class Iterator : public std::iterator<std::input_iterator_tag, cv::Mat> {
                public:
                    explicit Iterator(ImageLoader* loader, int index);
                    void reset();
                    Iterator& operator++();
                    cv::Mat operator*() const;
                    bool operator!=(const Iterator& other) const;
                    bool operator==(const Iterator& other) const;
                private:
                    friend class ImageLoader;
                    ImageLoader* loader_;
                    int index_ = loader_->index_;
            };

            Iterator begin() { return Iterator(this, this->index_); }
            Iterator end() { return Iterator(this, len()); }
        
        private:
            friend class Iterator;
            Iterator* iterator_;
            cv::Mat _get(int index);
            std::vector<std::string> paths;
            int index_ = 0;
    };

}

#endif // UTILS_H