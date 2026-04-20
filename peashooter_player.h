#pragma once
#include "player.h"
#include "timer.h"
#include "animation.h"
#include "pea_bullet.h"
#include <iostream>
extern atlas* atlas_peashooter_idle_left;
extern atlas* atlas_peashooter_idle_right;
extern atlas* atlas_peashooter_run_left;
extern atlas* atlas_peashooter_run_right;
extern atlas* atlas_peashooter_attack_ex_left;//豌豆射手向左特殊攻击动画
extern atlas* atlas_peashooter_attack_ex_right;
extern atlas* atlas_peashooter_die_left;
extern atlas* atlas_peashooter_die_right;
class peashooter_player :public player{
public:
	peashooter_player(bool facing_right):player(facing_right) {
		size.x = 96;
		size.y = 96;
		idle_animation_left->set_atlas(atlas_peashooter_idle_left);
		idle_animation_left->set_interval(75);
		idle_animation_right->set_atlas(atlas_peashooter_idle_right);
		idle_animation_right->set_interval(75);
		run_animation_left->set_atlas(atlas_peashooter_run_left);
		run_animation_left->set_interval(75);
		run_animation_right->set_atlas(atlas_peashooter_run_right);
		run_animation_right->set_interval(75);
		attack_ex_animation_left->set_atlas(atlas_peashooter_attack_ex_left);
		attack_ex_animation_left->set_interval(75);
		attack_ex_animation_right->set_atlas(atlas_peashooter_attack_ex_right);
		attack_ex_animation_right->set_interval(75);
		die_animation_left->set_atlas(atlas_peashooter_die_left);
		die_animation_left->set_interval(150);
		die_animation_right->set_atlas(atlas_peashooter_die_right);
		die_animation_right->set_interval(150);
		die_animation_left->set_loop(false);
		die_animation_right->set_loop(false);
		timer_attack_ex.set_wait_time(attack_ex_during);
		timer_attack_ex.set_one_shot(true);
		timer_attack_ex.set_callback([&]() {is_attacking_ex = false; });
		timer_spawn_pea_ex.set_wait_time(100);
		timer_spawn_pea_ex.set_callback([&]() {spawn_pea_bullet(speed_pea_ex); });
		attack_cd = 100;
	};
	~peashooter_player() = default;
	void on_update(int delta) override {
		player::on_update(delta);
		if (is_attacking_ex) {
			main_camera.shake(5, 100);
			timer_attack_ex.on_update(delta);
			timer_spawn_pea_ex.on_update(delta);
		}
	}
	void on_draw(const camera& Camera) override {
		player::on_draw(Camera);
	}
	void on_input(const ExMessage& msg) override {
		player::on_input(msg);
	}
	void on_attack()override {
		spawn_pea_bullet(speed_pea);
		
			switch (rand() % 2) {
			case 0:
				mciSendString(_T("play pea_shoot_1 from 0"),NULL,0,NULL);
				break;
			case 1:
				mciSendString(_T("play pea_shoot_2 from 0"), NULL, 0, NULL);
				break;
			}
	}
     void on_attack_ex() {
		 is_attacking_ex = true;
		 timer_attack_ex.restart();
		 is_facing_right ? attack_ex_animation_right->reset() : attack_ex_animation_left->reset();
		 mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);
	 }
private:
	void spawn_pea_bullet(float speed) {
		bullet* bullet_pea = new peashooter_bullet();
		vector1 bullet_position, bullet_velocity;
		const vector1& bullet_size = bullet_pea->get_size();
		bullet_position.x = is_facing_right ? position.x + size.x / 2 : position.x - bullet_size.x / 2;//依据角色朝向设置子弹初始位置和速度
		bullet_position.y = position.y;
		bullet_velocity.x = is_facing_right ? speed : -speed;
		bullet_velocity.y = 0;
		bullet_pea->set_position(bullet_position.x, bullet_position.y);
		bullet_pea->set_velocity(bullet_velocity.x, bullet_velocity.y);
		bullet_pea->set_collide_target(id == player_id::P1 ? player_id::P2 : player_id::P1);//设置子弹碰撞目标为另一个玩家
        bullet_pea->set_callback([&]() {
            mp += 20;
        });

        // Debug: ensure img_pea and atlas_pea_break are available
        if (!img_pea) std::cout << "[DEBUG] img_pea is null when spawning pea bullet\n";
        if (!atlas_pea_break) std::cout << "[DEBUG] atlas_pea_break is null when spawning pea bullet\n";
        else if (atlas_pea_break->get_size() == 0) std::cout << "[DEBUG] atlas_pea_break empty when spawning pea bullet\n";

        bullet_list.push_back(bullet_pea);
	}
	const float speed_pea = 0.75f;
	const float speed_pea_ex = 1.5f;
	const int attack_ex_during = 2500;
	Timer timer_attack_ex;
	Timer timer_spawn_pea_ex;
};
