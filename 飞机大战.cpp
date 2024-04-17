#include <stdio.h>
#include <windows.graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <easyx.h>
#define PLAYER_BALL 15
#define ENEMY_NUM 10
#define ENEMY_BALL 15
void creat_ball();
IMAGE bk;//��Ϸ����
IMAGE player[2];//�Ի�
IMAGE ball[2];
IMAGE enemy[2];
IMAGE img_dead;
IMAGE title_1,title_2;
IMAGE choose[2];
char score_data[20];
int bk_wide = 548;
int bk_high = 865;
DWORD t1, t2;//����ʱ�����
int score;
struct playerdata
{
	double x;
	double y;
	bool flage;//�������
	int wide;//�Ի�����101
	int high;//�Ի�����66
}player_data,player_ball[PLAYER_BALL],enemy_data[ENEMY_NUM];
void introduce()
{
	
	
	putimage(0, 0, &title_2);
	while (1)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			mciSendString("close, ./image/choose.wav ", 0, 0, 0);//��������
			mciSendString("open, ./image/choose.wav ", 0, 0, 0);//��������
			mciSendString("play  ./image/choose.wav  ", 0, 0, 0);//��������
			break;
		}
	}
}
void reimage_2()
{
	
	initgraph(bk_wide, bk_high);//�������ڣ�548*800��
	loadimage(&title_1,"./image/title_1.jpg");//����
	loadimage(&choose[0], "./image/choose_1.jpg");//ѡ���
	loadimage(&choose[1], "./image/choose_2.jpg");//ѡ����Ƭ
	loadimage(&title_2, "./image/title_2.jpg");
	mciSendString("open, ./image/music.mp3 ", 0, 0, 0);//��������
	mciSendString("play  ./image/music.mp3  ", 0, 0, 0);//��������
}
int menu()
{
	reimage_2();
	putimage(0, 0, &title_1);
	putimage(103, 345, &choose[1], NOTSRCERASE);//ѡ����Ƭ��λ���ڵ�һ��
	putimage(103, 345, &choose[0], SRCINVERT);//ѡ���
	int x, y;
FLAGE1:
	int num = 1;
	//1���������Ǹ��������м䣬����������
	while (1)
	{
		if (rand() % 1000 == 1)
		{
			if (GetAsyncKeyState(VK_UP))//������ϣ�����һ��
			{
				mciSendString("close, ./image/choose.wav ", 0, 0, 0);//��������
				mciSendString("open, ./image/choose.wav ", 0, 0, 0);//��������
				mciSendString("play  ./image/choose.wav  ", 0, 0, 0);//��������
				if (num == 1)
				{
					num = 3;
					putimage(0, 0, &title_1);
					putimage(103, 645, &choose[1], NOTSRCERASE);//ѡ����Ƭ��λ���ڵ�����
					putimage(103, 645, &choose[0], SRCINVERT);//ѡ���
				}
				else
					if (num == 2)
					{
						num = 1;
						putimage(0, 0, &title_1);
						putimage(103, 345, &choose[1], NOTSRCERASE);//ѡ����Ƭ��λ���ڵ�һ��
						putimage(103, 345, &choose[0], SRCINVERT);//ѡ���

					}
					else
						if (num == 3)
						{
							num = 2;
							putimage(0, 0, &title_1);
							putimage(103, 485, &choose[1], NOTSRCERASE);//ѡ����Ƭ��λ���ڵڶ���
							putimage(103, 485, &choose[0], SRCINVERT);//ѡ���
						}

			}
			if (GetAsyncKeyState(VK_DOWN))//������£�����һ��
			{
				mciSendString("close, ./image/choose.wav ", 0, 0, 0);//��������
				mciSendString("open, ./image/choose.wav ", 0, 0, 0);//��������
				mciSendString("play  ./image/choose.wav  ", 0, 0, 0);//��������
				if (num == 3)
				{
					num = 1;
					putimage(0, 0, &title_1);
					putimage(103, 345, &choose[1], NOTSRCERASE);//ѡ����Ƭ��λ���ڵ�һ��
					putimage(103, 345, &choose[0], SRCINVERT);//ѡ���
				}
				else if (num == 2)
				{
					num = 3;
					putimage(0, 0, &title_1);
					putimage(103, 645, &choose[1], NOTSRCERASE);//ѡ����Ƭ��λ���ڵ�����
					putimage(103, 645, &choose[0], SRCINVERT);//ѡ���
				}
				else if (num == 1)
				{
					num = 2;
					putimage(0, 0, &title_1);
					putimage(103, 485, &choose[1], NOTSRCERASE);//ѡ����Ƭ��λ���ڵڶ���
					putimage(103, 485, &choose[0], SRCINVERT);//ѡ���
				}
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				mciSendString("close, ./image/choose.wav ", 0, 0, 0);//�ر�����
				mciSendString("open, ./image/choose.wav ", 0, 0, 0);//��������
				mciSendString("play  ./image/choose.wav  ", 0, 0, 0);//��������
				switch (num)
				{
				case 1:mciSendString("close  ./image/music.mp3 ", 0, 0, 0);//�ر�����
					return 0; 
				case 2:introduce(); goto FLAGE1;
				case 3:exit(0);
				}
				break;
			}
		}
	}
}
void init()//��ʼ������
{
	
	score = 0;
	srand(GetTickCount());
	loadimage(&bk,"./image/background.jpg");//����Ϸ������ʼ��
	loadimage(&player[0], "./image/player_1.jpg");//���Ի���ʼ��
	loadimage(&player[1], "./image/player_2.jpg");//�Ի���Ƭ
	loadimage(&ball[0], "./image/ball_1.jpg");//������ӵ���ʼ��
	loadimage(&ball[1], "./image/ball_2.jpg");//����ӵ���Ƭ
	loadimage(&enemy[0], "./image/enemy_1.jpg");//�л�
	loadimage(&enemy[1], "./image/enemy_2.jpg");//�л���Ƭ
	loadimage(&img_dead, "./image/deadbackground.jpg");//����ͼƬ
	mciSendString("open, ./image/game_bgm.mp3 ",0 ,0 , 0);//��������
	mciSendString("play  ./image/game_bgm.mp3 repeat ", 0, 0, 0);//��������
	player_data.wide = 101;
	player_data.high = 66;
	player_data.x = bk_wide / 2 - player_data.wide / 2;//��ʼ���Ի�x��
	player_data.y = bk_high - player_data.high;//��ʼ���Ի�Y��
	for (int i = 0;i < PLAYER_BALL;i++)
	{
		player_ball[i].flage = FALSE;//����ζ������ӵ�û�з���
		player_ball[i].wide = 14;
		player_ball[i].high = 14;
	}
	t1 = t2 = GetTickCount();//�ӿ��������ڵĺ�����
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy_data[i].wide = 101;
		enemy_data[i].high = 66;
		enemy_data[i].flage = false;
	}
}
void plane_control(double speed)//�ٿطɻ�
{
	//�����ƶ�
	if (GetAsyncKeyState(VK_UP)&& player_data.y>0)
	{
		player_data.y -=speed;
	}
	//�����ƶ�
	if (GetAsyncKeyState(VK_DOWN)&&player_data.y< bk_high-player_data.high/2)
	{
		player_data.y += speed;
	}
	//�����ƶ�
	if (GetAsyncKeyState(VK_LEFT)&& player_data.x+player_data.wide/2>=0)
	{
		player_data.x-= speed;
	}//�����ƶ�
	if (GetAsyncKeyState(VK_RIGHT)&& player_data.x<bk_wide-player_data.wide/2)
	{
		player_data.x += speed;
	}
	//����
	if (GetAsyncKeyState(VK_SPACE)&&t2-t1>200)//ÿ200���뷢һ���ӵ�
	{
		mciSendString("close  ./image/attack_1.mp3  ", 0, 0, 0);//��������
		mciSendString("open, ./image/attack_1.mp3 ", 0, 0, 0);//��������
		mciSendString("play  ./image/attack_1.mp3  ", 0, 0, 0);//��������
		
		creat_ball();	
		t1 = t2;
	}
	t2 = GetTickCount();
}
void reimage()//ˢ��ͼ��
{
	BeginBatchDraw();
	putimage(0,0,&bk);//��bk��ͼƬ����(0,0����λ��
	putimage(player_data.x ,player_data.y,&player[1], NOTSRCERASE);//�Ի���Ƭ
	putimage(player_data.x, player_data.y, &player[0],SRCINVERT );//�Ի�
	for (int i = 0; i < PLAYER_BALL; i++)
	{
		if (player_ball[i].flage)
		{
			putimage(player_ball[i].x, player_ball[i].y, &ball[1], NOTSRCERASE);//����ӵ���Ƭ
			putimage(player_ball[i].x, player_ball[i].y, &ball[0], SRCINVERT);//����ӵ�
			
		}
	}
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy_data[i].flage)
		{
			putimage(enemy_data[i].x, enemy_data[i].y, &enemy[1],NOTSRCERASE);//�л���Ƭ
			putimage(enemy_data[i].x, enemy_data[i].y, &enemy[0],SRCINVERT);//�л�
			

		}
	}
	settextcolor(RGB(0, 0, 0));
	settextstyle(50, 0, "����");
	setbkmode(TRANSPARENT);
	outtextxy(20, 20, "��ǰ�÷�:");
	sprintf_s(score_data, "%d", score);
	outtextxy(250, 20, score_data);
	if (score == 1000)
	{
		settextstyle(50, 0, "����");
		setbkmode(TRANSPARENT);
		outtextxy(20, 40, "��ϲ�������زʵ�");
		setbkmode(TRANSPARENT);
		settextstyle(50, 0, "����");
		outtextxy(20, 60, "�Ǿ��ǿ���ȥbվ��עС����ӳ��ˣ�");
	}
	EndBatchDraw();
}
void creat_ball()//�����ӵ�
{
	for (int i=0; i <PLAYER_BALL; i++)
	{
		if (!player_ball[i].flage)
		{
			
			player_ball[i].x = player_data.x +50;
			player_ball[i].y = player_data.y;
			player_ball[i].flage = TRUE;//����ζ������ӵ�������
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
void enemy_move(double speed)//�л��ƶ�
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
void creat_enemy()//���ɵл�
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemy_data[i].flage)
		{
			enemy_data[i].y = 0;
			enemy_data[i].x = rand() % (bk_wide-enemy_data[i].wide);//��������Ļ�ڵл�
			enemy_data[i].flage = true;
			break;
		}
	}
}
void attack()
{
	int i, j;
	//���ӵ�����͵л�����һ��ʱ��ɱ
	for ( i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy_data[i].flage)//����õл������ھ�����
		{
			for (j = 0; j < PLAYER_BALL; j++)
			{
				if (player_ball[j].flage)
				{
				if (   player_ball[j].x>enemy_data[i].x&&player_ball[j].x< enemy_data[i].x+enemy_data[i].wide
					&& player_ball[j].y>enemy_data[i].y && player_ball[j].y < enemy_data[i].y + enemy_data[i].high)
					{
					mciSendString("close  ./image/attack_2.mp3  ", 0, 0, 0);//��������
					mciSendString("open, ./image/attack_2.mp3 ", 0, 0, 0);//��������
					mciSendString("play  ./image/attack_2.mp3  ", 0, 0, 0);//��������
					score += 1;
					//�����ˣ��ӵ��͵л�����ʧ
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
	int x1 = player_data.x+player_data.x / 2.;//�ж���x��
	int  y1 = player_data.y + player_data.wide / 3;//�ж���y��
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		
		if (enemy_data[i].flage)
		{
			if (   x1 > enemy_data[i].x && x1 < enemy_data[i].x + enemy_data[i].wide
				&& y1 > enemy_data[i].y && y1 < enemy_data[i].y + enemy_data[i].high)
			{
				mciSendString("open, ./image/dead.wav ", 0, 0, 0);//��������
				mciSendString("play  ./image/dead.wav ", 0, 0, 0);//��������
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
	
	init();//���ó�ʼ������
	while (1)
	{
		printf("1");
		
		reimage();//ˢ��ͼƬ
		plane_control(0.1);//��Ұ������������ٶ�
		ball_move(1);//�ӵ��ƶ�
		if (rand() % 100 == 1)
		{
			creat_enemy();//�����л�
		}
		attack();
		enemy_move(0.07);//�л��ƶ�
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