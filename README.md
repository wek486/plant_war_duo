<div align="center">

# 植物大战 · 双人对战

豌豆射手与向日葵的同屏平台对战练习。

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square) ![EasyX](https://img.shields.io/badge/EasyX-16a34a?style=flat-square) ![双人同屏](https://img.shields.io/badge/%E5%8F%8C%E4%BA%BA%E5%90%8C%E5%B1%8F-f59e0b?style=flat-square)

</div>

---

<p align="center"><a href="https://github.com/wek486/plant_war_duo/tree/master">完整源码与资源 · master 分支</a></p>

## 项目亮点

- 菜单、角色选择与战斗场景分离，练习场景管理。
- 双人移动、跳跃、普通攻击和能量技能。
- 角色动画、粒子效果、平台碰撞与音效配合。
- 摄像机与计时器等基础模块，适合在入门小游戏后继续学习。

## 资源预览

下方图片直接引用本仓库已有资源，用于展示项目中的场景和角色，属于素材预览。角色、美术和音乐的权利归各自权利人所有；仓库提供素材不代表授予额外使用许可。


<p align="center"><img src="https://raw.githubusercontent.com/wek486/plant_war_duo/master/resources/menu_background.png" alt="仓库中的菜单背景素材" width="760"></p>
<p align="center"><img src="https://raw.githubusercontent.com/wek486/plant_war_duo/master/resources/avatar_peashooter.png" alt="豌豆射手头像素材" width="120">&nbsp;&nbsp;<img src="https://raw.githubusercontent.com/wek486/plant_war_duo/master/resources/avatar_sunflower.png" alt="向日葵头像素材" width="120"></p>

## 操作

| 动作 | 玩家 1 | 玩家 2 |
| --- | --- | --- |
| 左右移动 | A / D | ← / → |
| 跳跃 | W | ↑ |
| 普通攻击 | F | . |
| 能量技能 | G | / |

技能需要足够能量，具体规则见 `player.h`。

## 本地运行

环境：Windows、Visual Studio C++ 桌面开发工具、与目标架构匹配的 EasyX。工程使用的工具集以 `.vcxproj` 为准；本机版本不同可在项目属性中重定向。

```sh
git clone --branch master https://github.com/wek486/plant_war_duo.git
cd plant_war_duo
```

1. 打开 `zhiwu.cpp.slnx`，选择相应平台和编译配置。
2. 确认 EasyX 的头文件与库已配置，再生成项目。
3. 将工作目录设为仓库根目录，保留 `resources/` 的相对位置。

以上是按仓库代码整理的运行步骤，未在此次文档整理中完成编译验证。

## 代码导览

| 入口 | 职责 |
| --- | --- |
| `main1.cpp` | 程序初始化与主流程；`main.cpp` 当前为空文件 |
| `player.h` | 玩家输入、状态与基础行为 |
| `peashooter_player.h` | 豌豆射手角色逻辑 |
| `game_scene.h`、`menu.h` | 战斗与菜单场景 |
| `animation.*`、`atlas.*` | 动画与图集 |
| `camera.h`、`particle.h` | 镜头与粒子 |


---

如果你也在学习这个方向，欢迎通过 Issues 交流思路、反馈问题。遇到不理解的实现，可以结合代码与 AI 提问，先理解，再动手修改。
