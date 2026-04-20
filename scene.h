#ifndef SCENE_H
#define SCENE_H
#include "camera.h"
#include<graphics.h> 
class Scene {
public:
	Scene() {}
	virtual ~Scene() = default;
	virtual void on_enter() = 0;
	virtual void on_update(int delta) = 0;
	virtual void on_draw(const camera& Camera) = 0;
	virtual void on_input(const ExMessage& msg) = 0;
	virtual void on_exit() = 0;
private:

};

#endif
