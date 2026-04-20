#ifndef PLATFORM_H
#define PLATFORM_H
#include "camera.h"
#include "graphics.h"
#include "util.h"
extern bool is_debug;
class Platform {
public:
	Platform() = default;
	~Platform() = default;

	typedef struct {
		float y;
		float left, right;
	}CollisonShape;

	CollisonShape shape;
	IMAGE* img = NULL;
	POINT render_position;
	void on_draw(const camera& Camera) const{
		putimage_alpha(render_position.x, render_position.y, img);
		if (is_debug) {
			setlinecolor(RGB(255, 0, 0));
			line(Camera, shape.left, shape.y, shape.right, shape.y);
		}

	}
private:




};








#endif
