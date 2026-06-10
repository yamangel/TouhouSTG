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

int main() {
	initgraph(640, 960);//创建窗口
	loadResources();//加载资源
	BeginBatchDraw();

	Background stage01a;//背景
	initBackground(stage01a, stage01aPath,80);

	int shootCount = 1;//自机子弹数量
	float baseAngle = 0, spreadAngle = 10;//自机多子弹偏移角度
	player pl00(32, 48, 320.0f, 750.0f, 300.0f, 100.0f, 5);//自机00灵梦
	float shootColdown = 0;//射击冷却
	vector<Bullet> bullets;//自弹列表

	vector<Bullet> enemyBullets;//敌弹列表
	vector<enemy> enemies;//敌人列表
	EnemyManager enemyManager;//出怪顺序表
	enemyManager.init();

	clock_t lastTime = clock();
	while (true) {
		clock_t now = clock();
		float dt = (double)(now - lastTime) / CLOCKS_PER_SEC;
		lastTime = now;//计算两帧间的时间差来控制帧率稳定

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)break;//退出控制

		enemyManager.update(enemies, dt);//更新出怪
		updateBackground(stage01a, dt);//更新背景
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

		checkCollisions(pl00,bullets,enemies,enemyBullets);//检测碰撞

		cleardevice();//清屏
		drawBackground(stage01a);//绘制背景
		drawBullets(bullets);//绘制自弹
		drawBullets(enemyBullets);//绘制敌弹
		drawEnemy(enemies);//绘制敌人	
		drawPlayer(pl00);//绘制自机
		FlushBatchDraw();//刷新绘制，防闪屏

		int elapsed = (int)((clock() - now) * 1000 / CLOCKS_PER_SEC);
		if (elapsed < 16)Sleep(16 - elapsed);//控制帧率稳定
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
