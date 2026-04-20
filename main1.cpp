#include<windows.h>
#include "menu.h"
#include "game_scene.h"
#include "scene_manager.h"
#include "selectorscene.h"
#include "atlas.h"
#include "util.h"
#include "camera.h"
#pragma comment(lib,"winmm.lib")
#include <tchar.h>	
#include <imm.h>
#pragma comment(lib, "imm32.lib")
#include "platform.h"
#include "player.h"
#include <ctime>
#include "bullet.h"
#include <iostream>				
#include<iostream>
std::vector<bullet*> bullet_list;//全局子弹列表
bool is_debug = false;//是否打开调试模式
camera main_camera;//主摄像机

IMAGE* img_menu_background;

IMAGE* img_VS;//相关的图片文字
IMAGE* img_1p;
IMAGE* img_2p;
IMAGE* img_1p_desc;//键位描述
IMAGE* img_2p_desc;
IMAGE* img_gravestone_left;//墓碑向左图片
IMAGE* img_gravestone_right;
IMAGE* img_selector_tip;
IMAGE* img_selector_background;
IMAGE* img_1p_selector_bth_idle_left;//1p 向左选择按钮默认状态图片
IMAGE* img_1p_selector_bth_idle_right;
IMAGE* img_1p_selector_bth_down_left  ;//1p 向左选自按钮按下状态图片
IMAGE* img_1p_selector_bth_down_right;
IMAGE* img_2p_selector_bth_idle_left ;
IMAGE* img_2p_selector_bth_idle_right;
IMAGE* img_2p_selector_bth_down_left;
IMAGE* img_2p_selector_bth_down_right;
IMAGE* img_peashooter_selector_background_left;//选角色界面向左的豌豆射手背景图片
IMAGE* img_peashooter_selector_background_right;
IMAGE* img_sunflower_selector_background_left;
IMAGE* img_sunflower_selector_background_right;

IMAGE* img_sky;
IMAGE* img_hills;//山脉图片
IMAGE* img_platform_large;
IMAGE* img_platform_small;
IMAGE* img_1p_cursor;//1p 指示光标图片
IMAGE* img_2p_cursor;

atlas* atlas_peashooter_idle_left;//豌豆射手向左待机动画
atlas* atlas_peashooter_idle_right;
atlas* atlas_peashooter_run_left;
atlas* atlas_peashooter_run_right;
atlas* atlas_peashooter_attack_ex_left;//豌豆射手向左特殊攻击动画
atlas* atlas_peashooter_attack_ex_right;
atlas* atlas_peashooter_die_left;
atlas* atlas_peashooter_die_right;

atlas* atlas_sunflower_idle_left;
atlas* atlas_sunflower_idle_right;
atlas* atlas_sunflower_run_left;
atlas* atlas_sunflower_run_right;
atlas* atlas_sunflower_attack_ex_left;
atlas* atlas_sunflower_attack_ex_right;
atlas* atlas_sunflower_die_left;
atlas* atlas_sunflower_die_right;

IMAGE* img_pea;//豌豆图片
atlas* atlas_pea_break;//豌豆破碎动画
atlas* atlas_sun;//太阳动画
atlas* atlas_sun_explode;//太阳爆炸动画
atlas* atlas_sun_ex;//特殊太阳动画
atlas* atlas_sun_ex_explode;
atlas* atlas_sun_text;//日字文本图集

atlas* atlas_run_effect;//奔跑特效动画图集
atlas* atlas_jump_effect;//跳跃特效动画图集
atlas* atlas_land_effect;//落地特效动画图集

IMAGE* img_1p_winner ;//1p 获胜文本图片
IMAGE* img_2p_winner;//2p 获胜文本图片
IMAGE* img_winner_bar;//获胜玩家文本背景图片
IMAGE* img_avatar_peashooter ;//豌豆射手头像图片
IMAGE* img_avatar_sunflower ;//龙日葵头像图片
IMAGE* img_player1_avatar;
IMAGE* img_player2_avatar;

Scene* Menu_scene=NULL;
Scene* gamescene=NULL;
Scene* selectorscene = NULL;
SceneManager scene_manager;

player* player1;
player* player2;

std::vector<Platform> Platform_list;
void load_game_resources();
int main() {
	HWND f= initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(f, _T("双人小格斗游戏"));
	std::srand(time(NULL));
	load_game_resources();
	HWND hwnd = GetForegroundWindow();
	HIMC prevImc = ImmAssociateContext(hwnd, NULL);
	settextstyle(28, 0, _T("IPix.ttf"));//设置字体样式
	setbkmode(TRANSPARENT);//文字透明设置！！！
	Menu_scene = new Menu();
	gamescene = new Game_scene();
	selectorscene = new Selector_scene();
	scene_manager.set_current_scene(Menu_scene);
	
	ExMessage msg;
	const int FPS = 60;
	BeginBatchDraw();
	DWORD last_time = GetTickCount();
	while (true) {
		DWORD frame_start_time = GetTickCount();
	     
		while (peekmessage(&msg)) {
			scene_manager.on_input(msg);
		}
		DWORD current_time = GetTickCount();
		DWORD delta = current_time - last_time;

		scene_manager.on_update(delta);
		last_time = current_time;
		cleardevice();
		scene_manager.on_draw(main_camera);
		FlushBatchDraw();
		DWORD frame_detal_time = GetTickCount() - frame_start_time;
		if (frame_detal_time < (1000/FPS)) {
			Sleep((1000/FPS)-frame_detal_time);
		}
	}
	EndBatchDraw();
	closegraph();
	return 0;
    // 在程序结束前恢复 IME（示例放在退出前）
    ImmAssociateContext(hwnd, prevImc);
}
void load_game_resources() {
	img_menu_background = new IMAGE();
	img_VS = new IMAGE();
	img_1p = new IMAGE();
	img_2p = new IMAGE();
	img_1p_desc = new IMAGE();
	img_2p_desc = new IMAGE();
	img_gravestone_left = new IMAGE();
	img_gravestone_right = new IMAGE();
	img_selector_tip = new IMAGE();
	img_selector_background = new IMAGE();
	img_1p_selector_bth_idle_left = new IMAGE();
	img_1p_selector_bth_idle_right = new IMAGE();
	img_1p_selector_bth_down_left = new IMAGE();
	img_1p_selector_bth_down_right = new IMAGE();
	img_2p_selector_bth_idle_left = new IMAGE();
	img_2p_selector_bth_idle_right = new IMAGE();
	img_2p_selector_bth_down_left = new IMAGE();
	img_2p_selector_bth_down_right = new IMAGE();
	img_peashooter_selector_background_left = new IMAGE();
	img_peashooter_selector_background_right = new IMAGE();
	img_sunflower_selector_background_left = new IMAGE();
	img_sunflower_selector_background_right = new IMAGE();
	img_sky = new IMAGE();
	img_hills = new IMAGE();
	img_platform_large = new IMAGE();
	img_platform_small = new IMAGE();
	img_1p_cursor = new IMAGE();
	img_2p_cursor = new IMAGE();
	img_pea = new IMAGE(); // <--- 别忘了这个！
	img_1p_winner = new IMAGE();
	img_2p_winner = new IMAGE();
	img_winner_bar = new IMAGE();
	img_avatar_peashooter = new IMAGE();
	img_avatar_sunflower = new IMAGE();
	AddFontResourceEx(_T("resources//IPix.ttf"), FR_PRIVATE, NULL);
	loadimage(img_menu_background,_T ("resources//menu_background.png"));
	loadimage(img_VS, _T("resources//VS.png"));
	loadimage(img_1p, _T("resources//1P.png"));
	loadimage(img_2p, _T("resources//2P.png"));
	loadimage(img_1p_desc, _T("resources//1P_desc.png"));
	loadimage(img_2p_desc, _T("resources//2P_desc.png"));
	loadimage(img_gravestone_right, _T("resources//gravestone.png"));
	fill_image(img_gravestone_left, img_gravestone_right);
	loadimage(img_selector_tip, _T("resources//selector_tip.png"));
	loadimage(img_selector_background, _T("resources//selector_background.png"));
	loadimage(img_1p_selector_bth_idle_right, _T("resources//1P_selector_btn_idle.png"));
	fill_image(img_1p_selector_bth_idle_left, img_1p_selector_bth_idle_right);
	loadimage(img_1p_selector_bth_down_right, _T("resources//2P_selector_btn_down.png"));
	fill_image(img_1p_selector_bth_down_left, img_1p_selector_bth_down_right);
	loadimage(img_2p_selector_bth_idle_right, _T("resources//2P_selector_btn_idle.png"));
	fill_image(img_2p_selector_bth_idle_left, img_2p_selector_bth_idle_right);
	loadimage(img_2p_selector_bth_down_right, _T("resources//2P_selector_btn_down.png"));
	fill_image(img_2p_selector_bth_down_left, img_2p_selector_bth_down_right);
	loadimage(img_peashooter_selector_background_right, _T("resources//peashooter_selector_background.png"));
	fill_image(img_peashooter_selector_background_left, img_peashooter_selector_background_right);
	loadimage(img_sunflower_selector_background_right, _T("resources//sunflower_selector_background.png"));
	fill_image(img_sunflower_selector_background_left, img_sunflower_selector_background_right);
	loadimage(img_sky, _T("resources//sky.png"));
	loadimage(img_hills, _T("resources//hills.png"));
	loadimage(img_platform_large, _T("resources//platform_large.png"));
	loadimage(img_platform_small, _T("resources//platform_small.png"));
	loadimage(img_1p_cursor, _T("resources//1P_cursor.png"));
	loadimage(img_2p_cursor, _T("resources//2P_cursor.png"));

	atlas_peashooter_idle_right = new atlas("resources//peashooter_idle_", 9);
	atlas_peashooter_idle_left = new atlas(atlas_peashooter_idle_right);
	atlas_peashooter_run_right = new atlas("resources//peashooter_run_", 5);
	atlas_peashooter_run_left = new atlas(atlas_peashooter_run_right);
	atlas_peashooter_attack_ex_right = new atlas("resources//peashooter_attack_ex_", 3);
	atlas_peashooter_attack_ex_left = new atlas(atlas_peashooter_attack_ex_right);
	atlas_peashooter_die_right = new atlas("resources//peashooter_die_", 4);
	atlas_peashooter_die_left = new atlas(atlas_peashooter_die_right);

	atlas_sunflower_idle_right = new atlas("resources//sunflower_idle_", 8);
	atlas_sunflower_idle_left = new atlas(atlas_sunflower_idle_right);
	atlas_sunflower_run_right = new atlas("resources//sunflower_run_", 5);
	atlas_sunflower_run_left = new atlas(atlas_sunflower_run_right);
	atlas_sunflower_attack_ex_right = new atlas("resources//sunflower_attack_ex_", 9);
	atlas_sunflower_attack_ex_left = new atlas(atlas_sunflower_attack_ex_right);
	atlas_sunflower_die_right = new atlas("resources//sunflower_die_", 2);
	atlas_sunflower_die_left = new atlas(atlas_sunflower_die_right);

	loadimage(img_pea, _T("resources//pea.png"));
	atlas_pea_break = new atlas("resources//pea_break_", 3);
	atlas_sun = new atlas("resources//sun_", 5);
	atlas_sun_explode = new atlas("resources//sun_explode_", 5);
	atlas_sun_ex = new atlas("resources//sun_ex_", 5);
	atlas_sun_ex_explode = new atlas("resources//sun_explode_", 5);
	atlas_sun_text = new atlas("resources//sun_text_", 6);
	atlas_run_effect = new atlas("resources//run_effect_", 4);
	atlas_jump_effect = new atlas("resources//jump_effect_", 5);
	atlas_land_effect = new atlas("resources//land_effect_", 2);

	// 简单运行时检查资源是否加载成功（调试用）
	struct Checker {
		static void check_img(const char* name, IMAGE* img) {
			if (!img) std::cout << "[RESOURCE ERROR] image not loaded: " << name << std::endl;
		}
		static void check_atlas(const char* name, atlas* a) {
			if (!a) { std::cout << "[RESOURCE ERROR] atlas is null: " << name << std::endl; return; }
			if (a->get_size() == 0) std::cout << "[RESOURCE ERROR] atlas empty: " << name << std::endl;
		}
	};

	Checker::check_img("img_pea", img_pea);
	Checker::check_atlas("atlas_pea_break", atlas_pea_break);
	Checker::check_atlas("atlas_sun", atlas_sun);
	Checker::check_atlas("atlas_sun_explode", atlas_sun_explode);
	Checker::check_atlas("atlas_run_effect", atlas_run_effect);
	Checker::check_atlas("atlas_jump_effect", atlas_jump_effect);
	Checker::check_atlas("atlas_land_effect", atlas_land_effect);
	loadimage(img_1p_winner, _T("resources//1P_winner.png"));
	loadimage(img_2p_winner, _T("resources//2P_winner.png"));
	loadimage(img_winner_bar, _T("resources//winnner_bar.png"));

	loadimage(img_avatar_peashooter, _T("resources//avatar_peashooter.png"));
	loadimage(img_avatar_sunflower,_T( "resources//avatar_sunflower.png"));

	mciSendString(_T("open resources//bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resources//bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resources//pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resources//pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resources//pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resources//pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
	mciSendString(_T("open resources//pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resources//sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
	mciSendString(_T("open resources//sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources//sun_text.mp3 alias sun_text"), NULL, 0, NULL);
	mciSendString(_T("open resources//ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
	mciSendString(_T("open resources//ui_switch.wav alias ui_switch"), NULL, 0, NULL);
	mciSendString(_T("open resources//ui_win.wav alias ui_win"), NULL, 0, NULL);
}
