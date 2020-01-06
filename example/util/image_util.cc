#include "image_util.h"
// dirent.h 是linux的系统调用
// see https://pubs.opengroup.org/onlinepubs/009695399/basedefs/dirent.h.html
#include <dirent.h>
#include <algorithm>
#include <stdexcept>

image_sequence::image_sequence(const std::string& img_dir_path, const double fps)
    : fps_(fps) {
    DIR* dir;
    if ((dir = opendir(img_dir_path.c_str())) == nullptr) {
        throw std::runtime_error("directory " + img_dir_path + " does not exist");
    }
    dirent* dp;
    // 这一部分代码可以在 gcc/mingw 通用
    // ≈跨平台, 只要Windows是用mingw环境的话。
    for (dp = readdir(dir); dp != nullptr; dp = readdir(dir)) {
        const std::string img_file_name = dp->d_name;
        if (img_file_name == "." || img_file_name == "..") {
            continue;
        }
        img_file_paths_.push_back(img_dir_path + "/" + img_file_name);
    }
    closedir(dir);

    std::sort(img_file_paths_.begin(), img_file_paths_.end());
}

std::vector<image_sequence::frame> image_sequence::get_frames() const {
    std::vector<frame> frames;
    for (unsigned int i = 0; i < img_file_paths_.size(); ++i) {
        // emplace_back 与 push_back 的区别
        // push_back = 构造函数+拷贝构造
        // emplace_back = 原地构造, 不拷贝
        frames.emplace_back(frame{img_file_paths_.at(i), (1.0 / fps_) * i});
    }
    return frames;
}
