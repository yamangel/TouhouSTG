#include "resource.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemyManager.h"
#include "collision.h"
#include "background.h"
#include <time.h>
#include <Windows.h>
using namespace std;

void title_start()
{
	putimage(0, 0, &title_bk00);
	putimage(0, 0, &title_ch00white, NOTSRCERASE);
	putimage(0, 0, &title_ch00, SRCINVERT);
	putimage(700, 30, &title_logowhite, NOTSRCERASE);
	putimage(700, 30, &title_logo, SRCINVERT);
	putimage(800, 440, 350, 480, &title_item00white, 350, 0, NOTSRCERASE);
	putimage(800, 440, 350, 480, &title_item00, 350, 0, SRCINVERT);
}

int main() {
	initgraph(1280, 960);//创建窗口640//记得要更新窗口大小ui布局
	loadResources();//加载资源
	bool ontext = false;
	bool gameJustStarted = true;//判断是否需要重置游戏
	enum GameScene { SCENE_TITLE, SCENE_GAME, SCENE_GAMEOVER };
	GameScene currentScene = SCENE_TITLE;

	Background stage01a;//背景
	initBackground(stage01a, stage01aPath, 80, 0);//加载背景
	//Background stage01d;//云
	//initBackground(stage01d, stage01dblackPath, 100, 1);//加载云
	Background ending_bk00;//end
	initBackground(ending_bk00, ending_bg00Path, 300, -1);//加载end

	int shootCount = 1;//自机子弹数量
	float baseAngle = 0, spreadAngle = 10;//自机多子弹偏移角度
	player pl00(32, 48, 320.0f, 750.0f, 300.0f, 100.0f, 5);//自机00灵梦
	float shootColdown = 0;//射击冷却
	vector<Bullet> bullets;//自弹列表

	vector<Bullet> enemyBullets;//敌弹列表
	vector<enemy> enemies;//敌人列表
	EnemyManager enemyManager;//出怪顺序表
	BeginBatchDraw();
	enemyManager.init();

	clock_t lastTime = clock();
	while (true)
	{
		clock_t now = clock();
		float dt = (double)(now - lastTime) / CLOCKS_PER_SEC;
		lastTime = now;//计算两帧间的时间差来控制帧率稳定
		cleardevice();//清屏
		switch (currentScene)
		{
		case SCENE_TITLE:
			title_start();
			if (MouseHit() || ontext)
			{
				MOUSEMSG msg = GetMouseMsg();
				int mx = msg.x, my = msg.y;
				bool inside = (mx >= 840 && mx <= 1100 && my >= 440 && my <= 480);
				switch (msg.uMsg)
				{
				case WM_MOUSEMOVE:
					if (inside)
					{
						putimage(800, 440, 350, 40, &title_item00white, 0, 0, NOTSRCERASE);
						putimage(800, 440, 350, 40, &title_item00, 0, 0, SRCINVERT);
						ontext = true;
					}
					break;
				case WM_LBUTTONDOWN:
					if (inside)
					{
						currentScene = SCENE_GAME;
					}
					break;
				default:
					ontext = false;
					break;
				}
			}
			break;

		case SCENE_GAME:
			if (gameJustStarted) 
			{
				pl00.hp = 5;
				pl00.x = 320;
				pl00.y = 750;
				pl00.invincibleTimer = 0;
				bullets.clear();
				enemyBullets.clear();
				enemies.clear();
				enemyManager.init();
				shootColdown = 0;
				gameJustStarted = false;
			}
			lastTime = clock();//重置时间基准
			enemyManager.update(enemies, dt);//更新出怪
			updateBackground(stage01a, dt);//更新背景
			//updateBackground(stage01d, dt);//更新云
			updatePlayer(pl00, dt);//更新自机
			updateBullets(bullets, dt);//更新自弹
			updateBullets(enemyBullets, dt);//更新敌弹
			updateEnemy(enemies, enemyBullets, pl00.x, pl00.y, dt);//更新敌人状态

			shootColdown -= dt;//实现有冷却的基础自动射击
			if (shootColdown <= 0)
			{
				shoot(bullets, 12, 55, pl00.x, pl00.y - pl00.high / 2.0f, shootCount, baseAngle, spreadAngle, 350.0f, 0);//发射基础子弹
				shootColdown = 0.18f;
			}

			checkCollisions(pl00, bullets, enemies, enemyBullets);//检测碰撞

			drawBackground(stage01a);//绘制背景
			//drawBackground(stage01d);//绘制云
			drawBullets(bullets);//绘制自弹
			drawBullets(enemyBullets);//绘制敌弹
			drawEnemy(enemies);//绘制敌人	
			drawPlayer(pl00);//绘制自机
			drawplayerCollisions(pl00,enemyBullets);//绘制自机碰撞箱
			if (pl00.hp <= 0) 
			{
				currentScene = SCENE_GAMEOVER;
				gameJustStarted = true;
			}
			break;

		case SCENE_GAMEOVER:
			lastTime = clock();//重置时间基准
			updateBackground(ending_bk00, dt);
			drawBackground(ending_bk00);
			if (GetAsyncKeyState(VK_SPACE) & 0x8000) currentScene = SCENE_TITLE;
			break;
		}
		FlushBatchDraw();//刷新绘制，防闪屏
		int elapsed = (int)((clock() - now) * 1000 / CLOCKS_PER_SEC);
		if (elapsed < 16)Sleep(16 - elapsed);//控制帧率稳定

	}
	EndBatchDraw();
	closegraph();
	return 0;
}
