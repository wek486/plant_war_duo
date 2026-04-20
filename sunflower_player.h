#pragma once

#include "player.h"
#include "timer.h"
#include "vector1.h"
#include "sun_bullet.h"
#include "sun_bullet_ex.h"
extern atlas* atlas_sunflower_idle_left;
extern atlas* atlas_sunflower_idle_right;
extern atlas* atlas_sunflower_run_left;
extern atlas* atlas_sunflower_run_right;
extern atlas* atlas_sunflower_attack_ex_left;
extern atlas* atlas_sunflower_attack_ex_right;
extern atlas* atlas_sun_text;
extern player* player1;
extern player* player2;
extern atlas* atlas_sunflower_die_left;
extern atlas* atlas_sunflower_die_right;
class sunflower_player:public player {
public:
	sunflower_player(bool facing_right):player(facing_right) {
		size.x = 96;
		size.y = 96;
		idle_animation_left->set_atlas(atlas_sunflower_idle_left);
		idle_animation_left->set_interval(75);
		idle_animation_right->set_atlas(atlas_sunflower_idle_right);
		idle_animation_right->set_interval(75);
		run_animation_left->set_atlas(atlas_sunflower_run_left);
		run_animation_left->set_interval(75);
		run_animation_right->set_atlas(atlas_sunflower_run_right);
		run_animation_right->set_interval(75);
		animation_sun_text.set_atlas(atlas_sun_text);
		animation_sun_text.set_interval(100);
		attack_ex_animation_left->set_atlas(atlas_sunflower_attack_ex_left);
		attack_ex_animation_left->set_interval(75);
		attack_ex_animation_right->set_atlas(atlas_sunflower_attack_ex_right);
		attack_ex_animation_right->set_interval(75);
		attack_ex_animation_left->set_callback([&]() {is_attacking_ex = false; is_showing_sun_text = false; });
		attack_ex_animation_right->set_callback([&]() {is_attacking_ex = false; is_showing_sun_text = false; });
		die_animation_left->set_atlas(atlas_sunflower_die_left);
		die_animation_left->set_interval(150);
		die_animation_right->set_atlas(atlas_sunflower_die_right);
		die_animation_right->set_interval(150);
		die_animation_left->set_loop(false);
		die_animation_right->set_loop(false);
		attack_cd = 250;
	};
	~sunflower_player() = default;
	void on_update(int delta) override {
		player::on_update(delta);
		if(is_showing_sun_text) {
			animation_sun_text.on_update(delta);
		}
	}
	void on_draw(const camera& Camera) override {
		player::on_draw(Camera);
		if (is_showing_sun_text) {
			vector1 text_position;
			IMAGE* current_frame = animation_sun_text.get_frame();
			text_position.x = position.x - (size.x - current_frame->getwidth()) / 2.0f;
			text_position.y = position.y - current_frame->getheight();//文本在玩家上方，距离玩家10像素
			animation_sun_text.on_draw(Camera, (int)text_position.x, (int)text_position.y);
		}
	}
	void on_input(const ExMessage& msg) override {
		player::on_input(msg);
	}
	void on_attack() override{
		bullet* bullet_sun = new sun_bullet();
		vector1 bullet_position;
		const vector1 bullet_size = bullet_sun->get_size();
		bullet_position.x = position.x + (size.x - bullet_size.x) / 2.0f;
		bullet_position.y = position.y;
		bullet_sun->set_collide_target(id == player_id::P1 ? player_id::P2 : player_id::P1);//设置子弹碰撞目标为另一个玩家
		bullet_sun->set_position(bullet_position.x, bullet_position.y);
		bullet_sun->set_velocity(is_facing_right ? velocity_sun.x: -velocity_sun.x, velocity.y);//叠加
		bullet_sun->set_callback([&]() {
			mp += 35;
			});
		bullet_list.push_back(bullet_sun);
	
	}
	void on_attack_ex()override {
		is_attacking_ex = true;
		is_showing_sun_text = true;
		animation_sun_text.reset();
		is_facing_right ? attack_ex_animation_right->reset() : attack_ex_animation_left->reset();
		player* target_player = (id == player_id::P1 ? player2 : player1);
		bullet* bullet_ex = new sun_bullet_ex();
		vector1 bullet_position, bullet_velocity;
		const vector1& bullet_size = bullet_ex->get_size();//由于向日葵的大招要索敌所以要对目标玩家的位置进行获取，写个函数接口实现
		const vector1& target_size = target_player->get_size();
		const vector1& target_position = target_player->get_position();
		bullet_position.x = target_position.x + (target_size.x - bullet_size.x) / 2;
		bullet_position.y = -size.y;
		bullet_velocity.x = 0;
		bullet_velocity.y = speed_sun_ex;
		bullet_ex->set_position(bullet_position.x, bullet_position.y);
		bullet_ex->set_velocity(bullet_velocity.x, bullet_velocity.y);

		bullet_ex->set_collide_target(id == player_id::P1 ? player_id::P2 : player_id::P1);
		bullet_ex->set_callback([&]() {
			mp += 50;
			});
		bullet_list.push_back(bullet_ex);
		mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);
	}
private:
	animation animation_sun_text;
	
	bool is_showing_sun_text = false;
	const float speed_sun_ex = 0.15f;
	const vector1 velocity_sun = { 0.25f,-0.5f };


};