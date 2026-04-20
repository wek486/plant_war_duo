#ifndef PLAYER_H
#define PLAYER_H
#include "camera.h"
#include <graphics.h>
#include "player_id.h"
#include "vector1.h"
#include "animation.h"
#include <cmath>
#include "timer.h"
#include "bullet.h"
#include "util.h"
#include "particle.h"
class bullet;
extern std::vector<bullet*> bullet_list;
extern std::vector<Platform> Platform_list;
extern atlas* atlas_run_effect;//奔跑特效动画图集
extern atlas* atlas_jump_effect;//跳跃特效动画图集
extern atlas* atlas_land_effect;//落地特效动画图集
extern IMAGE* img_1p_cursor;
extern IMAGE* img_2p_cursor;
class player {
public:
	
	player(bool facing_right=true): is_facing_right(facing_right){ current_animation = idle_animation_right;
	 idle_animation_left->set_loop(true);
	 idle_animation_right->set_loop(true);
	 run_animation_left->set_loop(true);
	 run_animation_right->set_loop(true);
	 timer_attack_cd.set_wait_time(attack_cd);
	 timer_attack_cd.set_one_shot(true);
	 timer_attack_cd.set_callback([&]() {
		 can_attack = true;

		 });
	 timer_invulnerable.set_wait_time(750);
		 timer_invulnerable.set_one_shot(true);
		 timer_invulnerable.set_callback([&]() {
			 is_invulnerable = false;
			 is_showing_sketch_frame = false;//无敌结束后确保不显示剪映f
			 });
		 timer_invulnerable_blink.set_wait_time(75);
		 timer_invulnerable_blink.set_one_shot(false);
		 timer_invulnerable_blink.set_callback([&]() {
			 is_showing_sketch_frame = !is_showing_sketch_frame;
			 });//这样自己就能实现隔着时间的闪烁
		 timer_run_effect_generation.set_wait_time(75);
		 timer_run_effect_generation.set_callback([&]() {
			 vector1 particle_position;
			 IMAGE* frame = atlas_run_effect->get_image(0);
			 particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
			 particle_position.y = position.y + size.y - frame->getheight();
			 particle_list.emplace_back(particle_position, atlas_run_effect, 45);
			 });
		 timer_die_effect_generation.set_wait_time(35);
		 timer_die_effect_generation.set_callback([&]() {
			 vector1 particle_position;        
			 IMAGE* frame = atlas_run_effect->get_image(0);
			 particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
			 particle_position.y = position.y + size.y - frame->getheight();
			 particle_list.emplace_back(particle_position, atlas_run_effect, 150);
			 });
		 animation_jump_effect->set_atlas(atlas_jump_effect);
		 animation_jump_effect->set_interval(35);
		 animation_jump_effect->set_loop(false);
		 animation_jump_effect->set_callback([&]() {
			 is_jump_effect_visible = false;
			 });
		 animation_land_effect->set_atlas(atlas_jump_effect);
		 animation_land_effect->set_interval(35);
		 animation_land_effect->set_loop(false);
		 animation_land_effect->set_callback([&]() {
			 is_land_effect_visible = false;
			 });
		 timer_cursor_visibility.set_wait_time(2500);
		 timer_cursor_visibility.set_one_shot(true);
		 timer_cursor_visibility.set_callback([&]() {
			 is_cursor_visible = false;
			 });


	};
	~player() = default; 

	virtual void on_update(int delta) {
		//大招动画的优先级最高，攻击动画的优先级其次，最后才是移动和待机动画
		if (is_attacking_ex) {
			current_animation = is_facing_right ? attack_ex_animation_right : attack_ex_animation_left;
		}
		else {
			int	direction = is_right_key_down - is_left_key_down;//方向这里不定义为全局变量是因为已经用了布尔型来做差了
			//方向的巧妙设计，两组动画的播放，相交提瓦特，多了一组，常态的动画，奔跑动画	
			if (direction != 0) {
				is_facing_right = direction > 0;
				current_animation = is_facing_right ? run_animation_right : run_animation_left;
				float move_distance = direction * run_speed * delta;
				on_run(move_distance);
			}
			else {
				current_animation = is_facing_right ? idle_animation_right : idle_animation_left;
				timer_run_effect_generation.pause();//停止
			}
		}
		if (hp <= 0) {
			current_animation = last_hurt_direction.x < 0 ? die_animation_left : die_animation_right;
		}
	current_animation->on_update(delta);
	timer_invulnerable.on_update(delta);
	timer_invulnerable_blink.on_update(delta);
	timer_run_effect_generation.on_update(delta);
	timer_cursor_visibility.on_update(delta);
	if (is_showing_sketch_frame) {
		sketch_image(current_animation->get_frame(), &img_sketch);
	}
	move_and_collide(delta);
	timer_attack_cd.on_update(delta);
	if (hp <= 0)timer_die_effect_generation.on_update(delta);
	particle_list.erase(std::remove_if(particle_list.begin(), particle_list.end(), [&](const particle& particle) {
		return !particle.is_valid();
		}), particle_list.end());
	for ( particle& particle : particle_list) {
		particle.on_update(delta);
	}
	animation_jump_effect->on_update(delta);
	animation_land_effect->on_update(delta);
	};
	//此处有坑，记住要在子类重写一下，这里父类是虚函数，子类重写了父类的on_draw函数，如果在父类的on_draw函数里调用current_animation->on_draw(Camera, position.x, position.y；
	virtual void on_draw(const camera& Camera) {
		for (particle& particle : particle_list) {
			particle.on_draw(Camera);
		}
		if (hp >= 0 && is_invulnerable && is_showing_sketch_frame) {
			putimage_alpha(Camera, (int)position.x, (int)position.y,&img_sketch);
		}//if加上is_showing_sketch_frame实现闪白
		else { current_animation->on_draw(Camera, position.x, position.y); }
		if (is_jump_effect_visible) {
			animation_jump_effect->on_draw(Camera,(int)position_jump.x,(int)position_jump.y);
		}
		if (is_land_effect_visible) {
			animation_land_effect->on_draw(Camera, (int)position_land.x, (int)position_land.y);
		}
		if (is_cursor_visible) {
			switch (id) {
			case player_id::P1:
				putimage_alpha(Camera, (int)(position.x + (size.x - img_1p_cursor->getwidth()) / 2), (int)(position.y - img_1p_cursor->getheight()), img_1p_cursor);
				break;
			case player_id::P2:
				putimage_alpha(Camera, (int)(position.x + (size.x - img_2p_cursor->getwidth()) / 2), (int)(position.y - img_2p_cursor->getheight()), img_2p_cursor);
				break;
			
			}
		}
	};
	void set_hp(int val) {
		hp = val;
	}
	virtual void on_input(const ExMessage& msg) {
		switch (msg.message) {
		case WM_KEYDOWN:
			switch (id) {
			case player_id::P1:
				switch (msg.vkcode) {
				case 'a':
				case 'A':
					is_left_key_down = true;
					break;
				case 'd':
				case 'D':
					is_right_key_down = true;
					break;
				case 'W':
				case 'w':
					on_jump();
					break;
				case 'f':
				case 'F':
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();//restart函数会把计时器重置并开始计时
					}
					break;
				case'g':
				case 'G':
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
					break;
				default:
					break;
				}
				break;
			case player_id::P2:
				switch (msg.vkcode) {
				case VK_LEFT:
					is_left_key_down = true;
					break;
				
				case VK_RIGHT:
					is_right_key_down = true;
					break;
				case VK_UP:
					on_jump();
					break;
				case VK_OEM_PERIOD:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
				case VK_OEM_2:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
					break;
				default:
					break;
				}
			}
			break;
		case WM_KEYUP:
			switch (id) {
			case player_id::P1:
				switch (msg.vkcode) {
				case 'a':
				case 'A':
					is_left_key_down = false;
					break;
				case 'd':
				case 'D':
					is_right_key_down = false;
					break;
				default:
					break;
				}
				break;
			case player_id::P2:
				switch (msg.vkcode) {
				case VK_LEFT:
					is_left_key_down = false;
					break;

				case VK_RIGHT:
					is_right_key_down = false;
					break;
				default:
					break;
				}
				break;
			}
			break;
		default:
			break;
	}
	
	};
	void make_invulnerable(){
		is_invulnerable = true;
		// 立即显示剪影并启动闪烁计时器
		is_showing_sketch_frame = true;
		timer_invulnerable_blink.restart();
		timer_invulnerable.restart();
		}
	void set_player_id(player_id new_id) {
		id = new_id;
	}
	void set_position(float x,float y) {
		position.x = x;
		position.y = y;
	}
	void on_run(float distance) {
		if (is_attacking_ex)return;//如果正在使用大招，就不能移动了
		position.x += distance;
		timer_run_effect_generation.resume();
	}
	const vector1& get_position() const {
		return position;
	}
	const vector1& get_size() const {
		return size;
	}
	virtual void on_attack() {}
	virtual void on_attack_ex() {}
	int get_hp()const {
		return hp;
	}
	int get_mp() const{
		return mp;
	}
protected:
	bool is_invulnerable = false;//是否无敌
	bool is_showing_sketch_frame = false;//是否当前帧显示剪映
	Timer timer_invulnerable;//无敌状态定时器
	Timer timer_invulnerable_blink;//无敌状态闪烁定时器
	IMAGE img_sketch;
	bool is_attacking_ex = false;

	int mp = 0;//能量值
	int hp = 100;
	vector1 position;
	vector1 size;//玩家尺寸
	//防止空指针未初始化，直接在构造函数里初始化动画指针，虽然是空指针，但至少不会野指针了。给个空间
	animation* idle_animation_left=new animation(NULL,75);
	animation *idle_animation_right = new animation(NULL, 75);
	animation *run_animation_left = new animation(NULL, 75);
	animation *run_animation_right = new animation(NULL, 75);
	animation* attack_ex_animation_left = new animation(NULL, 75);
	animation* attack_ex_animation_right = new animation(NULL, 75);
	animation* die_animation_left = new animation(NULL, 75);
	animation* die_animation_right = new animation(NULL, 75);
	animation* animation_jump_effect=new animation(NULL,75);
	animation* animation_land_effect=new animation(NULL,75);
	bool is_jump_effect_visible=false;
	bool is_land_effect_visible=false;//可见性，特效
	vector1 position_jump;
	vector1 position_land;

	bool  is_cursor_visible = true;
	Timer timer_cursor_visibility;

	vector1 last_hurt_direction;//受击方向

	player_id id = player_id::P1;
	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_facing_right = true;
	bool can_attack = true;//防止无敌打击，攻击后进入冷却，冷却结束才能再次攻击
	Timer timer_attack_cd;
	int attack_cd = 500;//攻击冷却时间，单位毫秒
	animation* current_animation = NULL;//防止空指针未初始化
	const float run_speed = 0.55f;
	const float gravity = 1.6e-3f;//重力加速度 
	const float jump_velocity = -0.85f;

	Timer timer_run_effect_generation;//奔跑特效生成计时器
	Timer timer_die_effect_generation;//死亡特效生成计时器
	std::vector<particle>particle_list;
	vector1 velocity;//速度矢量，两个方向的速度都放在这里了，跳跃的时候只需要修改y方向的速度就好了，x方向的速度由按键控制，最后每帧都调用move_and_collide函数来更新位置和速度
	//由于这里的时间是delta,所以乘以delta就是每帧的速度增量了，直接加到速度上就好了，最后再把速度加到位置上就行了
	void move_and_collide(int delta) {
		float last_velocity_y = velocity.y;
		velocity.y += gravity * delta; //x 方向的速度不受重力影响，y方向的速度受重力影响，所以只修改y方向的速度
		position += velocity * delta;//妙
		if (hp <= 0)return;
		if (velocity.y > 0) {
			for (const Platform& platform : Platform_list) {
				const Platform::CollisonShape& shape = platform.shape;//为了判断下降的粒子效果，而不是与平台碰撞就生成粒子下降的效果
				bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left) <= size.x + (shape.right - shape.left));
				bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);
				if (is_collide_x && is_collide_y) {
					float delta_pos_y = velocity.y * delta;
					float last_delta_pos_y = position.y + size.y - delta_pos_y;
					if (last_delta_pos_y <= shape.y) {
						position.y = shape.y - size.y;
						velocity.y = 0;
						if (last_velocity_y != 0) {
							on_land();
						}
						break;//省去多余判断
					}
				}
			}
		}
		if (!is_invulnerable) {
			for (bullet* bullet : bullet_list) {
				if (!bullet->get_valid() || bullet->get_collide_target() != id) {
					continue;
				}//先判断子弹是否有效和碰撞目标是否是自己，不是的话就没必要进行碰撞检测了
				if (bullet->check_collision(position, size)) {
					make_invulnerable();
					bullet->on_collide();
					bullet->set_valid(false);
					hp -= bullet->get_damage();//生命计算处
					last_hurt_direction = bullet->get_position() - position;
					if (hp <= 0) {
						velocity.x = last_hurt_direction.x < 0 ? 0.35f : -0.35f;
						velocity.y = -1.0f;
					}
				}

			}
		}
	}
	void on_jump() {
		if (velocity.y != 0||is_attacking_ex) {
			return;
		}
		velocity.y += jump_velocity;
		is_jump_effect_visible = true;
		animation_jump_effect->reset();
		IMAGE* effect_frame = animation_jump_effect->get_frame();
		position_jump.x = position.x + (size.x - effect_frame->getwidth()) / 2;
		position_jump.y = position.y + size.y - effect_frame->getheight();

	}
	virtual void on_land() {
		is_land_effect_visible = true;
		animation_land_effect->reset();
		IMAGE* effect_frame = animation_land_effect->get_frame();
		position_land.x = position.x + (size.x - effect_frame->getwidth()) / 2;
		position_land.y = position.y + size.y - effect_frame->getheight();
	}


};





#endif
