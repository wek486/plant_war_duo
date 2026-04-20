#ifndef BULLET_H
#define BULLET_H
#include "vector1.h"
#include <functional>
#include "player_id.h"
#include "camera.h"
#include "graphics.h"
class bullet {
public:
	bullet()=default;
	 ~bullet() = default;
	void set_callback(std::function<void()>callback) {
		this->callback = callback;
	}
	void set_damage(int a) {
		damage = a;
	}
	int get_damage() {
		return damage;
	}
	void set_position(float x,float y) {
		position.x = x;
		position.y = y;
	}
	const vector1& get_position() const{
		return position;
	}
	void set_size(float x, float y) {
		size.x = x;
		size.y = y;
	}
	const vector1& get_size()const {
		return size;
	}
	void set_velocity(float x,float y) {
		velocity.x = x;
		velocity.y = y;;
	}
	void set_collide_target(player_id target) {
		target_id = target;
	}
	player_id get_collide_target()const {
		return target_id;
	}
	void set_valid(bool flag) {
		valid = flag;
	}
	bool get_valid() {
		return valid;
	}
	bool check_can_delete() const{
		return can_delete;
	}
	virtual void on_collide() {
		valid = false;
		if (callback) {
			callback();
		}
	}
	virtual bool check_collision(const vector1 &position,const vector1& size) {
		bool is_collision_x = ((this->position.x + this->size.x / 2 )>= position.x) && ((this->position.x + this->size.x / 2) <= position.x + size.x);
		bool is_collision_y= ((this->position.y + this->size.y / 2 )>= position.y) &&((this-> position.y + this->size.y / 2 )<= position.y + size.y);
		return is_collision_x && is_collision_y;

	}
	bool check_if_exceeds_screen(){
		return position.x + size.x <= 0 || position.x >= getwidth() || position.y + size.y <= 0 || position.y >= getheight();

	}
	virtual void on_update(int delta){}
	virtual void on_draw(const camera& Camera){}
protected:
	bool valid = true;
	bool can_delete = false;
	vector1 size;
	vector1 position;
	vector1 velocity;
	int damage=0;
	std::function<void()>callback;//能量
	player_id target_id = player_id::P1;//碰撞玩家对象检测，避免自己打自己

};





#endif
