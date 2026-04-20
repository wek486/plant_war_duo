#pragma once
#include "bullet.h"
#include "animation.h"
#include "util.h"
extern IMAGE* img_pea;
extern atlas* atlas_pea_break;
class peashooter_bullet :public bullet {
public:
	
	peashooter_bullet()
		: bullet(), animation_break()
	{
		valid = true;
		can_delete = false;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		size.x = 64.0f;
		size.y = 64.0f;
		damage = 10;
		animation_break.set_atlas(atlas_pea_break);
		animation_break.set_interval(100);
		animation_break.set_loop(false);
		animation_break.set_callback([this]() {
			this->can_delete = true;
		});
	}
	~peashooter_bullet() = default;
	void on_collide()override {
		bullet::on_collide();
		switch (rand() % 3) {
		case 0:
			mciSendString(_T("play pea_break_1 from 0"),NULL,0,NULL);
			break;
		case 1:
			mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
			break;
		case 2:
			mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
	}
	 void on_update(int delta)override {
		 position += velocity * (float)delta;
		 if (!valid) {
			 animation_break.on_update(delta);
		 }
		 if (check_if_exceeds_screen()) {
			 can_delete = true;
		 }
	 }
	 void on_draw(const camera& Camera) override {
		 if (valid) {
			 if (is_debug) std::cerr << "Drawing pea image: " << img_pea << " at (" << position.x << "," << position.y << ")\n";
			 putimage_alpha(Camera, (int)position.x, (int)position.y, img_pea);
		 }
		 else {
			 if (is_debug) std::cerr << "Drawing pea break animation frame idx=" << animation_break.get_idx_frame() << " atlas=" << atlas_pea_break << "\n";
			 animation_break.on_draw(Camera, (int)position.x,(int) position.y);
		 }
	 }
private:
	animation animation_break;

};