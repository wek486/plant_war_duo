#pragma once
#include "atlas.h"
#include "vector1.h"
#pragma comment (lib,"MSIMG32.LIB")
inline void fill_image(IMAGE* dst, IMAGE* src) {
    if (!dst || !src) return; // 防御性检查
    int width = src->getwidth();
    int height = src->getheight();
    Resize(dst, width, height);
    DWORD* color_frame_left = GetImageBuffer(src);
    DWORD* color_frame_right = GetImageBuffer(dst);
    if (!color_frame_left || !color_frame_right) return;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx_frame_left = y * width + x;
            int idx_frame_right = y * width + (width - x - 1);
            color_frame_right[idx_frame_right] = color_frame_left[idx_frame_left];
        }
    }
} 
inline void putimage_alpha(const camera& Camera,int x, int y, IMAGE* img) {
    if (!img) return;
    const vector1& camera_position = Camera.get_camera_position();
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(GetWorkingImage()), x - (int)camera_position.x, y - (int)camera_position.y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });

}
inline void putimage_alpha( int x, int y, IMAGE* img) {
    if (!img) return;
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });

}
inline void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y) {
    if (!img) return;
    int w = width > 0 ? width : img->getwidth();
    int h = height > 0 ? height : img->getheight();
    AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h, GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });

}
inline void line(const camera& Camera, int x1, int y1, int x2, int y2) {
    const vector1& camera_position = Camera.get_camera_position();
    ::line((int)(x1 - camera_position.x), (int)(y1 - camera_position.y), (int)(x2 - camera_position.x), (int)(y2 - camera_position.y));
}
inline void sketch_image(IMAGE* src, IMAGE* dst) {
    if (!src || !dst) return;
    int w = src->getwidth();
    int h = src->getheight();
    Resize(dst, w, h);
    DWORD* src_buffer = GetImageBuffer(src);
    DWORD* dst_buffer = GetImageBuffer(dst);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int src_idx = y * w + x;
            
            dst_buffer[src_idx] = BGR(RGB(255, 255, 255)) | (src_buffer[src_idx] & 0xFF000000);//实现闪白
        }
    }

}