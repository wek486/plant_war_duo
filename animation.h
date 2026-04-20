#ifndef ANIMATION_H
#define ANIMATION_H
#include "atlas.h"
#include <functional>
#include "camera.h"
class animation {
public:
	animation(atlas* srcs,int interval);
	animation():timer(0),idx_frame(0),image_list(nullptr),interval_ms(0),is_loop(false),callback(nullptr){};
	~animation()=default;
	void on_update( int delta);
	void on_draw(const camera& Camera,int x,int y);
	void reset() {
		timer = 0;
		idx_frame = 0;
	}
	void set_atlas(atlas* new_atlas) {
		reset();
	    image_list = new_atlas;
	}
	void set_loop(bool flag) {
		is_loop = flag;
	}
	void set_interval(int ms) {
		interval_ms = ms;
	}
	int get_idx_frame() {
		return idx_frame;
	}
	IMAGE* get_frame() {
		if (!image_list) return nullptr;
		return image_list->get_image(idx_frame);
	}
	bool check_finished() {
		if (is_loop) return false;
		if (!image_list) return true;
		return (idx_frame == image_list->get_size() - 1);
	}
	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}
private:
	int timer;
	int idx_frame;
	atlas* image_list;
	int interval_ms;
	bool is_loop;
	std::function<void()> callback;
};  



#endif
