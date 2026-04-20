#include "atlas.h"
atlas::atlas(std::string path1,int num1){
    num = num1;
	for (size_t i = 0; i < num; i++) {
		IMAGE* frame = new IMAGE();
        path = path1 + std::to_string(i + 1) + ".png";

		loadimage(frame, path.c_str());
		frame_list.push_back(frame);
	}
}
atlas::atlas(atlas* src) {
    if (!src) return;
    int n = src->frame_list.size();
    frame_list.clear();
    frame_list.reserve(n);
    this->num = n;
    for (int i = 0; i < n; ++i) {
        IMAGE* srcFrame = src->frame_list[i];
        if (!srcFrame) {
            frame_list.push_back(nullptr);
            continue;
        }

        int width = srcFrame->getwidth();
        int height = srcFrame->getheight();
        IMAGE* current_frame = new IMAGE();
        Resize(current_frame, width, height);

        DWORD* color_frame_left = GetImageBuffer(srcFrame);
        DWORD* color_frame_right = GetImageBuffer(current_frame);
        if (color_frame_left && color_frame_right) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int idx_frame_left = y * width + x;
                    int idx_frame_right = y * width + (width - x - 1);
                    color_frame_right[idx_frame_right] = color_frame_left[idx_frame_left];
                }
            }
        }
        frame_list.push_back(current_frame);
    }
}
 
atlas::~atlas() {
    for (auto img : frame_list) {
        if (img) delete img;
    }
    frame_list.clear();
}