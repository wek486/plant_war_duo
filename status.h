#ifndef STATUS_H
#define STATUS_H
#include <windows.h>
#include <graphics.h>
#include "util.h"
class status {
public:
	status() = default;
	~status() = default;
	void set_hp(int new_hp) {
		hp = new_hp;
	}
	void set_mp(int new_mp) {
		mp = new_mp;
	}
	void set_position(int x, int y) {
		position.x = x;
		position.y = y;
	}
	POINT get_position() const {
		return position;
	}
	void set_img_avatar(IMAGE* new_img) {
		img_avatar = new_img;
	}
	IMAGE* get_img_avatar()const {
		return img_avatar;
}
	void on_draw() {
		putimage_alpha(position.x, position.y, img_avatar);
		setfillcolor(RGB(5, 5, 5));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3 * 2, position.y + 36, 8, 8);
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3 * 2, position.y + 71, 8, 8);
		setcolor(RGB(67, 47, 47));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3 , position.y + 33, 8, 8);
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3 , position.y + 68, 8, 8);
		float hp_bar_width = width * max(0, hp) / 100.0f;
		float mp_bar_width = width * min(100, mp) / 100.0f;
		setfillcolor(RGB(197, 61, 67));
		solidroundrect(position.x + 100, position.y + 10,position.x+100+ (int)hp_bar_width + 3, position.y + 33, 8, 8);
		setfillcolor(RGB(83, 131, 195));
		solidroundrect(position.x + 100, position.y + 45,position.x+100+ (int)mp_bar_width + 3, position.y + 68, 8, 8);
	}
private:
	int hp = 0;
	int mp = 0;
	POINT position = { 0 };
	IMAGE* img_avatar = NULL;
	const int width = 275;

};
#endif