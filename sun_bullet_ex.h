#pragma once
#include "animation.h"
#include "bullet.h"
extern atlas* atlas_sun_ex;
extern atlas* atlas_sun_ex_explode;
extern camera main_camera;
class sun_bullet_ex:public bullet {
public:

	sun_bullet_ex() {
		velocity.x = 0;
		velocity.y = 0;
		size.x = 288;
		size.y = 288;
		damage = 20;
		animation_idle.set_atlas(atlas_sun_ex);
		animation_idle.set_interval(50);
		animation_explode.set_atlas(atlas_sun_ex_explode);
		animation_explode.set_interval(50);
		animation_explode.set_loop(false);
		animation_explode.set_callback([&]() {
			can_delete = true;
			});
		IMAGE* frame_idle = animation_idle.get_frame();
		IMAGE* frame_explode = animation_explode.get_frame();
		explode_render_offset.x = (frame_idle->getwidth() - frame_explode->getwidth()) / 2.0f;
		explode_render_offset.y = (frame_idle->getheight() - frame_explode->getheight()) / 2.0f;
	}
	~sun_bullet_ex(); 
		void on_collide()override {
			bullet::on_collide();
			main_camera.shake(20, 350);//设置摄像机抖动
			mciSendString(_T("play sun_explode_ex from 0"), NULL, 0, NULL);
		}
		bool check_collision(const vector1& position, const vector1& size)override {
			bool is_collide_x = (max(this->position.x + this->size.x, position.x + size.x) - min(this->position.x, position.x)) <= this->size.x + size.x;
			bool is_collide_y= (max(this->position.y + this->size.y, position.y + size.y) - min(this->position.y, position.y)) <= this->size.y + size.y;
			return is_collide_x&&is_collide_y;
		}
		void on_update(int delta) override {
			//和豌豆的打击之后处理位置不同
			if (valid) {
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
	vector1 explode_render_offset;

};