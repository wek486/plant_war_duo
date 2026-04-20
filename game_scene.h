#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include "scene.h"
#include "scene_manager.h"
#include <iostream>
#include "util.h"
#include "platform.h"
#include "player.h"
#include "status.h"
extern bool is_debug;
extern SceneManager scene_manager;
extern IMAGE* img_sky;
extern IMAGE* img_hills;
extern IMAGE* img_platform_large;
extern IMAGE* img_platform_small;
extern std::vector<Platform> Platform_list;
extern camera main_camera;
extern  player* player1;
extern player* player2;
extern IMAGE* img_player1_avatar;  
extern IMAGE* img_player2_avatar;
extern IMAGE* img_1p_winner;
extern IMAGE* img_2p_winner;
extern IMAGE* img_winner_bar;
class Game_scene :public Scene {
public:
	Game_scene() {}
	~Game_scene() = default;
	void on_enter() {
		is_game_over = false;
		is_slide_out_started = false;//实现循环的游戏逻辑
		pos_img_winner_bar.x = -img_winner_bar->getwidth();
		pos_img_winner_bar.y = (getheight() - img_winner_bar->getheight()) / 2;
		pos_x_img_winner_bar_dst = (getwidth() - img_winner_bar->getwidth()) / 2;

		pos_img_winner_text.x = pos_img_winner_bar.x;
		pos_img_winner_text.y = (getheight() - img_1p_winner->getheight()) / 2;
		pos_x_img_winner_text_dst = (getwidth() - img_1p_winner->getwidth()) / 2;
		timer_winner_slide_in.restart();
		timer_winner_slide_in.set_wait_time(2500);
		timer_winner_slide_in.set_one_shot(true);
		timer_winner_slide_in.set_callback([&]() {
			is_slide_out_started = true;
			});
		timer_winner_slide_out.restart();
		timer_winner_slide_out.set_wait_time(1000);
		timer_winner_slide_out.set_one_shot(true);
		timer_winner_slide_out.set_callback([&]() {
			scene_manager.switch_to(SceneManager::SceneType::Menu);
			});//实现游戏结束后的跳回菜单界面效果
		mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);
		pos_img_sky.x = (getwidth() - img_sky->getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky->getheight()) / 2;
		pos_img_hills.x = (getwidth() - img_hills->getwidth()) / 2;
		pos_img_hills.y = (getheight() - img_hills->getheight()) / 2;
		Platform_list.resize(4);
		Platform& large_platform = Platform_list[0];
		large_platform.img = img_platform_large;
		large_platform.render_position.x = 122;
		large_platform.render_position.y = 455;
		large_platform.shape.left = (float)large_platform.render_position.x + 30;
		large_platform.shape.right = (float)large_platform.render_position.x + img_platform_large->getwidth() - 30;
		large_platform.shape.y = (float)large_platform.render_position.y + 60;
		Platform& small_platform_1 = Platform_list[1];
		small_platform_1.img = img_platform_small;
		small_platform_1.render_position.x = 175;
		small_platform_1.render_position.y = 360;
		small_platform_1.shape.left = (float)small_platform_1.render_position.x + 40;
		small_platform_1.shape.right = (float)small_platform_1.render_position.x + img_platform_small->getwidth() - 40;
		small_platform_1.shape.y = (float)small_platform_1.render_position.y + img_platform_small->getheight()/2 ;
		Platform& small_platform_2 = Platform_list[2];
		small_platform_2.img = img_platform_small;
		small_platform_2.render_position.x = 855;
		small_platform_2.render_position.y = 360;
		small_platform_2.shape.left = (float)small_platform_2.render_position.x + 40;
		small_platform_2.shape.right = (float)small_platform_2.render_position.x + img_platform_small->getwidth() - 40;
		small_platform_2.shape.y = (float)small_platform_2.render_position.y +img_platform_small->getheight()/2;
		Platform& small_platform_3 = Platform_list[3];
		small_platform_3.img = img_platform_small;
		small_platform_3.render_position.x = 515;
		small_platform_3.render_position.y = 225;
		small_platform_3.shape.left = (float)small_platform_3.render_position.x + 40;
		small_platform_3.shape.right = (float)small_platform_3.render_position.x + img_platform_small->getwidth() - 40;
		small_platform_3.shape.y = (float)small_platform_3.render_position.y +img_platform_small->getheight()/2;

	
		player1->set_position(200, 50);
		player2->set_position(975, 50);
		player1_status.set_img_avatar(img_player1_avatar);
		player2_status.set_img_avatar(img_player2_avatar);
		player1_status.set_position(235, 625);
		player2_status.set_position(675, 625);
	}
	void on_update(int delta) {
		player1->on_update(delta);
		player2->on_update(delta);
		main_camera.on_update(delta);
		//删除子弹逻辑，妙
		bullet_list.erase(std::remove_if(bullet_list.begin(), bullet_list.end(), [](const bullet* bullet) {
			bool deletable = bullet->check_can_delete();
			if (deletable) {
				delete bullet;
				return deletable;
			}
			return false;//这里如果缺少，会导致子弹逻辑崩溃，就是生成子弹，只有刚开始极短时间有效，后面都没效，且，子弹动画相关逻辑也无法展示
			}), bullet_list.end());//使用erase和remove_if(),特别是remove_if，它的最后判断逻辑是依据返回的是true,和false,看是保留还是覆盖到后面去ture是移动后，false是保留
		for (bullet* bullet : bullet_list) {
			bullet->on_update(delta);
		}
		player1_status.set_hp(player1->get_hp());
		player1_status.set_mp(player1->get_mp());
		player2_status.set_hp(player2->get_hp());
		player2_status.set_mp(player2->get_mp());
		const vector1& position_player1 = player1->get_position();
		const vector1& position_player2 = player2->get_position();
		if (position_player1.y >= getheight()) {
			player1->set_hp(0);
		}
		if (position_player2.y >= getheight()) {
			player2->set_hp(0);
		}
		if (player1->get_hp() <= 0 || player2->get_hp() <= 0) {
			//实现游戏结束第一帧的切换音乐
			if (!is_game_over) {
				mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
				mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
			}
			is_game_over = true;
		}
		//妙
		if (is_game_over) {
			pos_img_winner_bar.x += (int)(speed_winner_bar * delta);
			pos_img_winner_text.x += (int)(speed_winner_text * delta);
			if (!is_slide_out_started) {
				timer_winner_slide_in.on_update(delta);
				if (pos_img_winner_bar.x > pos_x_img_winner_bar_dst)
					pos_img_winner_bar.x = pos_x_img_winner_bar_dst;
				if (pos_img_winner_text.x > pos_x_img_winner_text_dst)
					pos_img_winner_text.x = pos_x_img_winner_text_dst;
			}
			else {
				timer_winner_slide_out.on_update(delta);
			}

		}
	}
	void on_draw(const camera& Camera) {
		putimage_alpha(main_camera,pos_img_sky.x, pos_img_sky.y, img_sky);
		putimage_alpha(main_camera,pos_img_hills.x,pos_img_hills.y,img_hills);
		//新的循环方法，更简单的写法
		for (const Platform& platform : Platform_list) {
			platform.on_draw(Camera);
		}
		//拓展数组也是，
		if (is_debug) {
			settextcolor(RGB(255, 0, 0));
			outtextxy(15, 15, _T("已开始调试，按E关闭"));
		}
		player1->on_draw(Camera);
		player2->on_draw(Camera);
		for (bullet* bullet : bullet_list) {
			bullet->on_draw(Camera);
		}
		if (is_game_over) {
			putimage_alpha(pos_img_winner_bar.x, pos_img_winner_bar.y, img_winner_bar);
			putimage_alpha(pos_img_winner_text.x, pos_img_winner_text.y, player1->get_hp() > 0 ? img_1p_winner : img_2p_winner);
		}
		else {
			player1_status.on_draw();
			player2_status.on_draw();
		}
	}
	void on_input(const ExMessage& msg) {
		player1->on_input(msg);
		player2->on_input(msg);
		switch (msg.message) {
		case WM_KEYUP:
			if (msg.vkcode == 'Q') {
				is_debug = true;
			}
			if (msg.vkcode == 'E') {
				is_debug = false;
			}
			break;
		default:
			break;
		}
	}
	void on_exit() {
		std::cout << "游戏场景退出" << std::endl;
		delete player1;
		player1 = NULL;
		delete player2;
		player2 = NULL;
		bullet_list.clear();
		main_camera.reset();//防止卡了大招的震动效果
		mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
	}
private:
	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = {0};
	status player1_status;
	status player2_status;
	bool is_game_over = false;
	POINT pos_img_winner_bar = { 0 };
	POINT pos_img_winner_text = { 0 };
	int pos_x_img_winner_bar_dst=0;
	int pos_x_img_winner_text_dst=0;
	Timer timer_winner_slide_in;
	Timer timer_winner_slide_out;
	bool is_slide_out_started = false;
	float speed_winner_bar = 20;
	float speed_winner_text = 20;
};
#endif
