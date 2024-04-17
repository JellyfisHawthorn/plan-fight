#include <stdio.h>
#include <windows.graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <easyx.h>
#define PLAYER_BALL 15
#define ENEMY_NUM 10
#define ENEMY_BALL 15
void creat_ball();
IMAGE bk;//游戏背景
IMAGE player[2];//自机
IMAGE ball[2];
IMAGE enemy[2];
IMAGE img_dead;
IMAGE title_1,title_2;
IMAGE choose[2];
char score_data[20];
int bk_wide = 548;
int bk_high = 865;
DWORD t1, t2;//两个时间变量
int score;
struct playerdata
{
	double x;
	double y;
	bool flage;//死亡标记
	int wide;//自机宽是101
	int high;//自机高是66
}player_data,player_ball[PLAYER_BALL],enemy_data[ENEMY_NUM];
void introduce()
{
	
	
	putimage(0, 0, &title_2);
	while (1)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			mciSendString("close, ./image/choose.wav ", 0, 0, 0);//调用音乐
			mciSendString("open, ./image/choose.wav ", 0, 0, 0);//调用音乐
			mciSendString("play  ./image/choose.wav  ", 0, 0, 0);//播放音乐
			break;
		}
	}
}
void reimage_2()
{
	
	initgraph(bk_wide, bk_high);//制作窗口，548*800的
	loadimage(&title_1,"./image/title_1.jpg");//背景
	loadimage(&choose[0], "./image/choose_1.jpg");//选项框
	loadimage(&choose[1], "./image/choose_2.jpg");//选项框底片
	loadimage(&title_2, "./image/title_2.jpg");
	mciSendString("open, ./image/music.mp3 ", 0, 0, 0);//调用音乐
	mciSendString("play  ./image/music.mp3  ", 0, 0, 0);//播放音乐
}
int menu()
{
	reimage_2();
	putimage(0, 0, &title_1);
	putimage(103, 345, &choose[1], NOTSRCERASE);//选项框底片，位置在第一格
	putimage(103, 345, &choose[0], SRCINVERT);//选项框
	int x, y;
FLAGE1:
	int num = 1;
	//1是最上面那个，二是中间，三是最下面
	while (1)
	{
		if (rand() % 1000 == 1)
		{
			if (GetAsyncKeyState(VK_UP))//如果按上，往上一格
			{
				mciSendString("close, ./image/choose.wav ", 0, 0, 0);//调用音乐
				mciSendString("open, ./image/choose.wav ", 0, 0, 0);//调用音乐
				mciSendString("play  ./image/choose.wav  ", 0, 0, 0);//播放音乐
				if (num == 1)
				{
					num = 3;
					putimage(0, 0, &title_1);
					putimage(103, 645, &choose[1], NOTSRCERASE);//选项框底片，位置在第三个
					putimage(103, 645, &choose[0], SRCINVERT);//选项框
				}
				else
					if (num == 2)
					{
						num = 1;
						putimage(0, 0, &title_1);
						putimage(103, 345, &choose[1], NOTSRCERASE);//选项框底片，位置在第一格
						putimage(103, 345, &choose[0], SRCINVERT);//选项框

					}
					else
						if (num == 3)
						{
							num = 2;
							putimage(0, 0, &title_1);
							putimage(103, 485, &choose[1], NOTSRCERASE);//选项框底片，位置在第二个
							putimage(103, 485, &choose[0], SRCINVERT);//选项框
						}

			}
			if (GetAsyncKeyState(VK_DOWN))//如果按下，往下一格
			{
				mciSendString("close, ./image/choose.wav ", 0, 0, 0);//调用音乐
				mciSendString("open, ./image/choose.wav ", 0, 0, 0);//调用音乐
				mciSendString("play  ./image/choose.wav  ", 0, 0, 0);//播放音乐
				if (num == 3)
				{
					num = 1;
					putimage(0, 0, &title_1);
					putimage(103, 345, &choose[1], NOTSRCERASE);//选项框底片，位置在第一格
					putimage(103, 345, &choose[0], SRCINVERT);//选项框
				}
				else if (num == 2)
				{
					num = 3;
					putimage(0, 0, &title_1);
					putimage(103, 645, &choose[1], NOTSRCERASE);//选项框底片，位置在第三个
					putimage(103, 645, &choose[0], SRCINVERT);//选项框
				}
				else if (num == 1)
				{
					num = 2;
					putimage(0, 0, &title_1);
					putimage(103, 485, &choose[1], NOTSRCERASE);//选项框底片，位置在第二个
					putimage(103, 485, &choose[0], SRCINVERT);//选项框
				}
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				mciSendString("close, ./image/choose.wav ", 0, 0, 0);//关闭音乐
				mciSendString("open, ./image/choose.wav ", 0, 0, 0);//调用音乐
				mciSendString("play  ./image/choose.wav  ", 0, 0, 0);//播放音乐
				switch (num)
				{
				case 1:mciSendString("close  ./image/music.mp3 ", 0, 0, 0);//关闭音乐
					return 0; 
				case 2:introduce(); goto FLAGE1;
				case 3:exit(0);
				}
				break;
			}
		}
	}
}
void init()//初始化函数
{
	
	score = 0;
	srand(GetTickCount());
	loadimage(&bk,"./image/background.jpg");//给游戏背景初始化
	loadimage(&player[0], "./image/player_1.jpg");//给自机初始化
	loadimage(&player[1], "./image/player_2.jpg");//自机底片
	loadimage(&ball[0], "./image/ball_1.jpg");//给玩家子弹初始化
	loadimage(&ball[1], "./image/ball_2.jpg");//玩家子弹底片
	loadimage(&enemy[0], "./image/enemy_1.jpg");//敌机
	loadimage(&enemy[1], "./image/enemy_2.jpg");//敌机底片
	loadimage(&img_dead, "./image/deadbackground.jpg");//死亡图片
	mciSendString("open, ./image/game_bgm.mp3 ",0 ,0 , 0);//调用音乐
	mciSendString("play  ./image/game_bgm.mp3 repeat ", 0, 0, 0);//播放音乐
	player_data.wide = 101;
	player_data.high = 66;
	player_data.x = bk_wide / 2 - player_data.wide / 2;//初始化自机x轴
	player_data.y = bk_high - player_data.high;//初始化自机Y轴
	for (int i = 0;i < PLAYER_BALL;i++)
	{
		player_ball[i].flage = FALSE;//假意味着这个子弹没有发射
		player_ball[i].wide = 14;
		player_ball[i].high = 14;
	}
	t1 = t2 = GetTickCount();//从开机到现在的毫秒数
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy_data[i].wide = 101;
		enemy_data[i].high = 66;
		enemy_data[i].flage = false;
	}
}
void plane_control(double speed)//操控飞机
{
	//向上移动
	if (GetAsyncKeyState(VK_UP)&& player_data.y>0)
	{
		player_data.y -=speed;
	}
	//向下移动
	if (GetAsyncKeyState(VK_DOWN)&&player_data.y< bk_high-player_data.high/2)
	{
		player_data.y += speed;
	}
	//向左移动
	if (GetAsyncKeyState(VK_LEFT)&& player_data.x+player_data.wide/2>=0)
	{
		player_data.x-= speed;
	}//向右移动
	if (GetAsyncKeyState(VK_RIGHT)&& player_data.x<bk_wide-player_data.wide/2)
	{
		player_data.x += speed;
	}
	//攻击
	if (GetAsyncKeyState(VK_SPACE)&&t2-t1>200)//每200毫秒发一个子弹
	{
		mciSendString("close  ./image/attack_1.mp3  ", 0, 0, 0);//播放音乐
		mciSendString("open, ./image/attack_1.mp3 ", 0, 0, 0);//调用音乐
		mciSendString("play  ./image/attack_1.mp3  ", 0, 0, 0);//播放音乐
		
		creat_ball();	
		t1 = t2;
	}
	t2 = GetTickCount();
}
void reimage()//刷新图像
{
	BeginBatchDraw();
	putimage(0,0,&bk);//将bk的图片放在(0,0）的位置
	putimage(player_data.x ,player_data.y,&player[1], NOTSRCERASE);//自机底片
	putimage(player_data.x, player_data.y, &player[0],SRCINVERT );//自机
	for (int i = 0; i < PLAYER_BALL; i++)
	{
		if (player_ball[i].flage)
		{
			putimage(player_ball[i].x, player_ball[i].y, &ball[1], NOTSRCERASE);//玩家子弹底片
			putimage(player_ball[i].x, player_ball[i].y, &ball[0], SRCINVERT);//玩家子弹
			
		}
	}
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy_data[i].flage)
		{
			putimage(enemy_data[i].x, enemy_data[i].y, &enemy[1],NOTSRCERASE);//敌机底片
			putimage(enemy_data[i].x, enemy_data[i].y, &enemy[0],SRCINVERT);//敌机
			

		}
	}
	settextcolor(RGB(0, 0, 0));
	settextstyle(50, 0, "黑体");
	setbkmode(TRANSPARENT);
	outtextxy(20, 20, "当前得分:");
	sprintf_s(score_data, "%d", score);
	outtextxy(250, 20, score_data);
	if (score == 1000)
	{
		settextstyle(50, 0, "黑体");
		setbkmode(TRANSPARENT);
		outtextxy(20, 40, "恭喜解锁隐藏彩蛋");
		setbkmode(TRANSPARENT);
		settextstyle(50, 0, "黑体");
		outtextxy(20, 60, "那就是可以去b站关注小僵大队长了！");
	}
	EndBatchDraw();
}
void creat_ball()//创造子弹
{
	for (int i=0; i <PLAYER_BALL; i++)
	{
		if (!player_ball[i].flage)
		{
			
			player_ball[i].x = player_data.x +50;
			player_ball[i].y = player_data.y;
			player_ball[i].flage = TRUE;//真意味着这个子弹发射了
			break;
		}
	}
}
void ball_move(int speed)
{
	for (int i = 0; i < PLAYER_BALL; i++)
	{
		if(player_ball[i].flage)
		{ 
			player_ball[i].y -= speed;
			if (player_ball[i].y < 0) 
			{
				player_ball[i].flage = false;
			}
		}
			
	}
}
void enemy_move(double speed)//敌机移动
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy_data[i].flage)
		{
			enemy_data[i].y += speed;
			if (enemy_data[i].y > bk_high)
			{
				enemy_data[i].flage = false;
			}
		}
	}
}
void creat_enemy()//生成敌机
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemy_data[i].flage)
		{
			enemy_data[i].y = 0;
			enemy_data[i].x = rand() % (bk_wide-enemy_data[i].wide);//生成在屏幕内敌机
			enemy_data[i].flage = true;
			break;
		}
	}
}
void attack()
{
	int i, j;
	//当子弹坐标和敌机坐标一致时击杀
	for ( i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy_data[i].flage)//如果该敌机不存在就跳过
		{
			for (j = 0; j < PLAYER_BALL; j++)
			{
				if (player_ball[j].flage)
				{
				if (   player_ball[j].x>enemy_data[i].x&&player_ball[j].x< enemy_data[i].x+enemy_data[i].wide
					&& player_ball[j].y>enemy_data[i].y && player_ball[j].y < enemy_data[i].y + enemy_data[i].high)
					{
					mciSendString("close  ./image/attack_2.mp3  ", 0, 0, 0);//播放音乐
					mciSendString("open, ./image/attack_2.mp3 ", 0, 0, 0);//调用音乐
					mciSendString("play  ./image/attack_2.mp3  ", 0, 0, 0);//播放音乐
					score += 1;
					//击中了，子弹和敌机都消失
					enemy_data[i].flage = false;
					player_ball[j].flage = false;
					
					}
				}
			}
		}
	}
}
int dead()
{
	int x1 = player_data.x+player_data.x / 2.;//判定点x轴
	int  y1 = player_data.y + player_data.wide / 3;//判定点y轴
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		
		if (enemy_data[i].flage)
		{
			if (   x1 > enemy_data[i].x && x1 < enemy_data[i].x + enemy_data[i].wide
				&& y1 > enemy_data[i].y && y1 < enemy_data[i].y + enemy_data[i].high)
			{
				mciSendString("open, ./image/dead.wav ", 0, 0, 0);//调用音乐
				mciSendString("play  ./image/dead.wav ", 0, 0, 0);//播放音乐
				return 1;
			}
						
		}
	}
}
int aftdead()
{
	putimage(0, 0, &img_dead);
	for (;;)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			return 1;
		}
	}
}
int main()
{
	menu();
	
FLAGE:
	
	init();//调用初始化函数
	while (1)
	{
		printf("1");
		
		reimage();//刷新图片
		plane_control(0.1);//玩家按键，参数是速度
		ball_move(1);//子弹移动
		if (rand() % 100 == 1)
		{
			creat_enemy();//产生敌机
		}
		attack();
		enemy_move(0.07);//敌机移动
		if (dead()==1)
		{
			break;
		}
	}
	if (aftdead())
	{
		goto FLAGE;
	}
	getchar();
}