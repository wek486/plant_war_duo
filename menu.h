#ifndef MENU_H
#define MENU_H
#include "scene.h"
#include "scene_manager.h"


extern SceneManager scene_manager;
extern IMAGE *img_menu_background;
class Menu :public Scene {
public:
	Menu(){
		
	}
	~Menu()=default;
	void on_enter()override {
		mciSendString(_T("play bgm_menu repeat from 0  "), NULL, 0, NULL);
	}
	 void on_update(int delta)override {
		
	}
	 void on_draw(const camera& Camera)override {
		 putimage(0,0,img_menu_background);
	}
	 void on_input(const ExMessage& msg)override {
		 if (msg.message == WM_KEYUP) {
			 mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			 scene_manager.switch_to(SceneManager::SceneType::Selector);
		}
	}
	 void on_exit() override {
	 }
private:
	
	
	
};

#endif
