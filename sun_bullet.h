#pragma once
#include "animation.h"
#include "bullet.h"
extern atlas* atlas_sun;
extern atlas* atlas_sun_explode;
extern camera main_camera;
class sun_bullet :public bullet {
public:
	sun_bullet() {
		velocity.x = 0;
		velocity.y = 0;
		damage = 20;
		size.x = 96, size.y = 96;
		animation_idle.set_atlas(atlas_sun);
		animation_explode.set_atlas(atlas_sun_explode);
		animation_idle.set_loop(true);
		animation_explode.set_loop(false);
		animation_explode.set_callback([&]() {
			can_delete = true;
			});
		IMAGE* frame_idle = animation_idle.get_frame();
		IMAGE* frame_explode = animation_explode.get_frame();
		explode_render_offset.x = (frame_idle->getwidth() - frame_explode->getwidth()) / 2.0f;
		explode_render_offset.y= (frame_idle->getheight() - frame_explode->getheight()) / 2.0f;
	};
	~sun_bullet() = default;
	void on_collide()override {
		bullet::on_collide();
		main_camera.shake(5, 250);//设置摄像机抖动
		mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);
	}
	void on_update(int delta) override{
		//和豌豆的打击之后处理位置不同
		if (valid) {
			velocity.y += gravity * delta;
			position += velocity * (float)delta;
		}
		if (!valid) {
			animation_explode.on_update(delta);
		}
		else {
			animation_idle.on_update(delta);
		}
		if (check_if_exceeds_screen()) {
			can_delete = true;
		}
	}
	void on_draw(const camera& Camera) {
		if (valid) {
			animation_idle.on_draw(Camera, (int)position.x, position.y);
		}
		else {
			animation_explode.on_draw(Camera, (int)(position.x + explode_render_offset.x), (int)(position.y + explode_render_offset.y));//加位置偏移
		}
	}
private:
	animation animation_idle;
	animation animation_explode;
	vector1 explode_render_offset;//爆炸动画渲染偏移
	const float gravity = 1e-3f;
	
};