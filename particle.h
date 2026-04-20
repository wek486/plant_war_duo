#ifndef PARTICLE_H
#define PARTICLE_H
#include "vector1.h"
#include "atlas.h"
#include "util.h"
#include "animation.h"
class particle {
public:
	particle() = default;
	particle(const vector1& position,atlas* atlas,int lifespan):position(position),atlas(atlas),lifespan(lifespan){
	
	
	}
	~particle() = default;
	void set_atlas(atlas* new_atlas) {
		atlas = new_atlas;
	}
	void set_lifespan(int new_lifespan) {
		lifespan = new_lifespan;
	}
	void set_position(float x, float y) {
		position.x = x;
		position.y = y;
	}
	bool is_valid()const {
		return valid;
	}
	void on_update(int delta) {
		timer += delta;
		if (timer >= lifespan) {
			idx_frame++;
			if (idx_frame >= atlas->get_size()) {
				idx_frame = atlas->get_size() - 1;
				valid = false;
			}
		}
	}
	void on_draw(const camera& Camera) {
		putimage_alpha(Camera,(int)position.x, (int)position.y, atlas->get_image(idx_frame));
	}
private:
	int timer = 0;//定时器
	int lifespan = 0;//单帧动画持续时间
	int idx_frame = 0;
	vector1 position ;
	bool valid = true;
	atlas* atlas = NULL;

};




#endif
