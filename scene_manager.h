#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include "scene.h"

// 在此声明全局场景指针，避免头文件使用时找不到标识符
extern Scene* Menu_scene;
extern Scene* gamescene;
extern Scene* selectorscene;

class SceneManager :public Scene {
public:
    enum class SceneType {
        Menu,
        Game,
        Selector
    };
    void set_current_scene(Scene* scene) {
        current_scene = scene;
        current_scene->on_enter();
    }
    void switch_to(SceneType type) {
        current_scene->on_exit();
        switch (type) {
        case SceneType::Menu:
            current_scene = Menu_scene;
            break;
        case SceneType::Game:
            current_scene = gamescene;
            break;
        case SceneType::Selector:
            current_scene = selectorscene;
            break;
        default:
            break;
        }
        current_scene->on_enter();
    }
    SceneManager() {};
     ~SceneManager() = default;
     void on_enter()override {
         current_scene->on_enter();
     }
     void on_update(int delta)override {
         current_scene->on_update(delta);
     }
     void on_draw(const camera& Camera)override {
         current_scene->on_draw(Camera);
     }
     void on_input(const ExMessage& msg)override {
         current_scene->on_input(msg);
     }
     void on_exit() override {
         current_scene->on_exit();
     }
private:
    Scene* current_scene = NULL;
};
#endif

