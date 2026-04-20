#include "animation.h"
#pragma comment (lib,"MSIMG32.LIB")
#include "util.h"
animation::animation(atlas* srcs, int interval)
	: timer(0)
	, idx_frame(0)
	, image_list(srcs)
	, interval_ms(interval)
	, is_loop(false)
	, callback(nullptr)
{
}
void animation:: on_update(int delta) {
    if (!image_list) return;
    timer += delta;
    if (timer >= interval_ms) {
        timer = timer - interval_ms;
        idx_frame++;
        int sz = image_list->get_size();
        if (sz == 0) {
            idx_frame = 0;
            return;
        }
        if (idx_frame >= sz) {
            idx_frame = is_loop ? 0 : sz - 1;
            if (!is_loop && callback) {
                callback();
            }
        }
    }

}
void animation::on_draw(const camera& Camera ,int x,int y) {
    IMAGE* frame = get_frame();
    if (!frame) return;
    putimage_alpha(Camera, x, y, frame);
}