#ifndef SELECTORSCENE_H
#define SELECTORSCENE_H
#include "scene.h"
#include "scene_manager.h"
#include "animation.h"
#include "util.h"
#include "string.h"
#include <tchar.h>
#include "peashooter_player.h"
#include "sunflower_player.h"
extern player* player1;
extern player* player2;
extern SceneManager scene_manager;
extern Scene* Menu_scene;
extern Scene* gamescene;
extern Scene* selectorscene;
extern IMAGE* img_VS;
extern IMAGE* img_1p;
extern IMAGE* img_2p;
extern IMAGE* img_1p_desc;
extern IMAGE* img_2p_desc;
extern IMAGE* img_gravestone_left;
extern IMAGE* img_gravestone_right;
extern IMAGE* img_selector_tip;
extern IMAGE* img_selector_background;
extern IMAGE* img_1p_selector_bth_idle_left;
extern IMAGE* img_1p_selector_bth_idle_right;
extern IMAGE* img_1p_selector_bth_down_left;
extern IMAGE* img_1p_selector_bth_down_right;
extern IMAGE* img_2p_selector_bth_idle_left;
extern IMAGE* img_2p_selector_bth_idle_right;
extern IMAGE* img_2p_selector_bth_down_left;
extern IMAGE* img_2p_selector_bth_down_right;
extern IMAGE* img_peashooter_selector_background_left;
extern IMAGE* img_peashooter_selector_background_right;
extern IMAGE* img_sunflower_selector_background_left;
extern IMAGE* img_sunflower_selector_background_right;

extern atlas* atlas_peashooter_idle_left;
extern atlas* atlas_peashooter_idle_right;
extern atlas* atlas_sunflower_idle_left;
extern atlas* atlas_sunflower_idle_right;
extern IMAGE* img_avatar_peashooter;//头像
extern IMAGE* img_avatar_sunflower;
extern IMAGE* img_player1_avatar;
extern IMAGE* img_player2_avatar;

class Selector_scene :public Scene {
public:
	Selector_scene()
		: animation_peashooter(nullptr, 100)
		, animation_sunflower(nullptr, 100)
	{
		animation_peashooter.set_loop(true);
		animation_sunflower.set_loop(true);
	
	
	}
	~Selector_scene() = default;

	void on_enter() {
		animation_peashooter.set_atlas(atlas_peashooter_idle_right);
		animation_sunflower.set_atlas(atlas_sunflower_idle_right);
		animation_peashooter.set_interval(100);
		animation_sunflower.set_interval(100);

		static const int OFFSET_X = 50;
		pos_img_VS.x = (getwidth() - img_VS->getwidth()) / 2;
		pos_img_VS.y = (getheight() - img_VS->getheight()) / 2;
		pos_img_tip.x = (getwidth() - img_selector_tip->getwidth()) / 2;
		pos_img_tip.y = getheight()-125;
		pos_img_1P.x = (getwidth()/2 - img_1p->getwidth()) / 2 - OFFSET_X;
		pos_img_1P.y = 35;
		pos_img_2P.x = getwidth()/2+(getwidth()/2 - img_2p->getwidth()) / 2 + OFFSET_X;
		pos_img_2P.y = 35;
		pos_img_1P_desc.x = (getwidth() / 2 - img_1p_desc->getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 150;
		pos_img_2P_desc.x = (getwidth() / 2 + (getwidth() / 2 - img_2p_desc->getwidth()) / 2) + OFFSET_X;
		pos_img_2P_desc.y = getheight() - 150;
		pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right->getwidth()) / 2 - OFFSET_X;
		pos_img_1P_gravestone.y = pos_img_1P.y + img_1p->getheight() + 35;
		pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_right->getwidth()) / 2 + OFFSET_X;
		pos_img_2P_gravestone.y = pos_img_2P.y + img_2p->getheight() + 35;
		pos_animation_1P.x = (getwidth() / 2 - atlas_peashooter_idle_right->get_image(0)->getwidth()) / 2 - OFFSET_X;
		pos_animation_1P.y = (pos_img_1P_gravestone.y + 80);
		pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right->get_image(0)->getwidth()) / 2 + OFFSET_X;
		pos_animation_2P.y = pos_animation_1P.y;
		pos_img_1P_name.y = pos_animation_1P.y+155;
		pos_img_2P_name.y = pos_animation_1P.y+155;
		pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1p_selector_bth_idle_left->getwidth();
		pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right->getheight() - img_1p_selector_bth_idle_left->getheight())/2;
		pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right->getwidth();
		pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2p_selector_bth_idle_left->getwidth();
		pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left->getwidth();
		pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;

	}
	void on_update(int delta) {
		animation_peashooter.on_update(delta);
		animation_sunflower.on_update(delta);
		selector_background_scorll_offset_x += 5;
		if (selector_background_scorll_offset_x >= img_peashooter_selector_background_left->getwidth()) {
			selector_background_scorll_offset_x = 0;
		}
	}
	void on_draw(const camera& Camera) {
		IMAGE* current_selector_background_1P = nullptr;
		IMAGE* current_selector_background_2P = nullptr;
		switch (player_type_1) {
		case PlayerType::Peashooter:
			current_selector_background_2P = img_peashooter_selector_background_right;
			break;
		case PlayerType::Sunflower:
			current_selector_background_2P = img_sunflower_selector_background_right;
			break;
		default:
			break;
		}
		switch (player_type_2) {
		case PlayerType::Peashooter:
			current_selector_background_1P = img_peashooter_selector_background_left;
			break;
		case PlayerType::Sunflower:
			current_selector_background_1P = img_sunflower_selector_background_left;
			break;
		}
		putimage(0, 0, img_selector_background);
		putimage_alpha(selector_background_scorll_offset_x - current_selector_background_1P->getwidth(), 0, current_selector_background_1P);
		putimage_alpha(selector_background_scorll_offset_x, 0, current_selector_background_1P->getwidth() - selector_background_scorll_offset_x, 0, current_selector_background_1P, 0, 0);
		putimage_alpha(getwidth() - current_selector_background_2P->getwidth(), 0, current_selector_background_2P->getwidth() - selector_background_scorll_offset_x, 0, current_selector_background_2P,selector_background_scorll_offset_x, 0);
		putimage_alpha(getwidth()-selector_background_scorll_offset_x,0,current_selector_background_2P);

		putimage_alpha(pos_img_VS.x, pos_img_VS.y, img_VS);
		putimage_alpha(pos_img_1P.x, pos_img_1P.y, img_1p);
		putimage_alpha(pos_img_2P.x, pos_img_2P.y, img_2p);
		putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, img_gravestone_right);
		putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, img_gravestone_left);
		
		switch (player_type_1) {
		case PlayerType::Peashooter:
			animation_peashooter.on_draw(Camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right->getwidth() - textwidth(str_peashooter_name.c_str())) / 2;
			outtext_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
			break;
		case PlayerType::Sunflower:
			animation_sunflower.on_draw(Camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right->getwidth() - textwidth(str_sunflower_name.c_str())) / 2;
			outtext_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);

			break;
		}
		switch (player_type_2) {
		case PlayerType::Peashooter:
			animation_peashooter.on_draw(Camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right->getwidth() - textwidth(str_peashooter_name.c_str())) / 2;
			outtext_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);

			break;
		case PlayerType::Sunflower:
			animation_sunflower.on_draw(Camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right->getwidth() - textwidth(str_sunflower_name.c_str())) / 2;
			outtext_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
			break;
		}
		
		putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, img_1p_desc);
		putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, img_2p_desc);
		putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y, is_selector_1P_btn_left_down ? img_1p_selector_bth_down_left : img_1p_selector_bth_idle_left);
		putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y, is_selector_2P_btn_left_down ? img_2p_selector_bth_down_left : img_2p_selector_bth_idle_left);
		putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y, is_selector_1P_btn_right_down ? img_1p_selector_bth_down_right : img_1p_selector_bth_idle_right);
		putimage_alpha(pos_img_tip.x, pos_img_tip.y, img_selector_tip);
		putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y,is_selector_2P_btn_right_down ? img_2p_selector_bth_down_right : img_2p_selector_bth_idle_right);
	}
	void on_input(const ExMessage& msg) {
		switch (msg.message) {
		case WM_KEYDOWN:
			switch (msg.vkcode) {
			case 'A':
			case 'a':
				is_selector_1P_btn_left_down = true;
				break;
			case 'd':
			case 'D':
				is_selector_1P_btn_right_down = true;
				break;
			case VK_LEFT:
				is_selector_2P_btn_left_down = true;
				break;
			case VK_RIGHT:
				is_selector_2P_btn_right_down = true;
				break;
			
			}

			break;
		case WM_KEYUP:
			switch (msg.vkcode) {
			case 'A':
			case 'a':
				is_selector_1P_btn_left_down = false;
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_1 - 1)%(int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"),NULL,0,NULL);
				break;
			case 'd':
			case 'D':
				is_selector_1P_btn_right_down = false;
				player_type_1 = (PlayerType)(( (int)player_type_1 +1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_LEFT:
				is_selector_2P_btn_left_down = false;
				player_type_2 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_2 - 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_RIGHT:
				is_selector_2P_btn_right_down = false;
				player_type_2 = (PlayerType)(( (int)player_type_2 +1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_RETURN:
				scene_manager.switch_to(SceneManager::SceneType::Game);
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				break;
			default:
				break;
			}
			
		default:
			break;

		}
	
	}
	void on_exit() { 
		switch (player_type_1) {
		case PlayerType::Peashooter:
			player1 = new peashooter_player(true);
			img_player1_avatar = img_avatar_peashooter;
			break;
		case PlayerType::Sunflower:
			player1 = new sunflower_player(true);
			img_player1_avatar = img_avatar_sunflower;
			break;
		}
		player1->set_player_id(player_id::P1);
		switch (player_type_2) {
			case PlayerType::Peashooter:
				player2 = new peashooter_player(false);
				img_player2_avatar = img_avatar_peashooter;
				break;
			case PlayerType::Sunflower:
				player2 = new sunflower_player(false);
				img_player2_avatar = img_avatar_sunflower;
				break;
		}
		player2->set_player_id(player_id::P2);
		mciSendString(_T("stop bgm_menu"), NULL, 0, NULL);
	}

private:
	void outtext_shaded(int x, int y, std::string str) {
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str.c_str());
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str.c_str());
	}
	enum class PlayerType {
		Peashooter=0,
		Sunflower,
		Invalid
	};
	bool is_selector_1P_btn_left_down = false;//按键状态
	bool is_selector_1P_btn_right_down = false;
	bool is_selector_2P_btn_left_down = false;
	bool is_selector_2P_btn_right_down = false;


	POINT pos_img_VS = { 0 };
	POINT pos_img_1P = { 0 };
	POINT pos_img_2P = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1P_desc = { 0 };
	POINT pos_img_2P_desc = { 0 };
	POINT pos_img_1P_name = { 0 };//名字位置还没图片吧，先占个位置
	POINT pos_img_2P_name = { 0 };
	POINT pos_animation_1P = { 0 };//1P动画位置
	POINT pos_animation_2P = { 0 };//2P动画位置
	POINT pos_img_1P_gravestone = { 0 };//1P墓碑位置
	POINT pos_img_2P_gravestone = { 0 };//2P墓碑位置
	POINT pos_1P_selector_btn_left = { 0 };//1P选择按钮向左位置
	POINT pos_2P_selector_btn_left = { 0 };
	POINT pos_1P_selector_btn_right = { 0 };//1P选择按钮向右位置
	POINT pos_2P_selector_btn_right = { 0 };

	animation animation_peashooter;
	animation animation_sunflower;
	PlayerType player_type_1 = PlayerType::Peashooter;
	PlayerType player_type_2 = PlayerType::Sunflower;
	std::string str_peashooter_name = "豌豆射手";
	std::string str_sunflower_name = "龙日葵";
	int selector_background_scorll_offset_x = 0;

};
#endif
