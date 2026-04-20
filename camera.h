#ifndef CAMERA_H
#define CAMERA_H
#include "vector1.h"
#include "timer.h"
class camera {
public:
	camera() {
		timer_shake.set_one_shot(true);
		timer_shake.set_callback([&]() {
			is_shaking = false;
			reset();
			});
	};

	~camera() = default;
	const vector1& get_camera_position()const {
		return camera_position;
	}
	void reset() {
		camera_position.x = 0;
		camera_position.y = 0;
	}
	void on_update(int delta) {
		timer_shake.on_update(delta);
		if (is_shaking) {
			camera_position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
			camera_position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
		}
	}
	void shake(float strength, int duration) {
		is_shaking = true;
		shaking_strength = strength;
		timer_shake.set_wait_time(duration);
		timer_shake.restart();
	}
private://如果报错就是权限这里有点问题
	vector1 camera_position;
	Timer timer_shake;
	bool is_shaking = false;
	float shaking_strength = 0;//抖动幅度


};




#endif
