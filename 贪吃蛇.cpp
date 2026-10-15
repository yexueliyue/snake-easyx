#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#define SNAKE_NUM 500
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Snake
{
	int size = 3;
	int dir;
	int speed;
	POINT coor[SNAKE_NUM];
}snake;
struct Food
{
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;
void GameInit()
{
	initgraph(640, 480/*, SHOWCONSOLE*/);
	srand(GetTickCount());
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT; 
	for (int i = 0; i < snake.size ;  i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256,rand()%256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}
void GameDraw()
{
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}
void snakeMove()
{
	for (int i =  snake.size-1; i >0 ; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
	case UP:
			snake.coor[0].y-=snake.speed;
			if (snake.coor[0].y <= 0)
			{
				snake.coor[0].y = 480;
			}
			break; 
	case DOWN:
			snake.coor[0].y+=snake.speed;
			if (snake.coor[0].y >= 480)
			{
				snake.coor[0].y = 0;
			}
			break;
	case LEFT:
			snake.coor[0].x-=snake.speed;
			if (snake.coor[0].x<= 0)
			{
				snake.coor[0].x= 640;
			}
			break;
	case RIGHT:
			snake.coor[0].x+=snake.speed;
			if (snake.coor[0].x >= 640)
			{
				snake.coor[0].x = 0;
			}
			break;
	}
}
void keyControl()
{
	if (_kbhit())
	{
	switch (_getch())
	{
	case 'W':
	case'w':
	case 72 :
		if(snake.dir!=DOWN)
		snake.dir = UP;
		break;
	case 'S':
	case's':
	case 80:
		if(snake.dir != UP)
		snake.dir = DOWN;
		break;
	case 'a':
	case'A':
	case 75:
		if(snake.dir != RIGHT)
		snake.dir = LEFT;
		break;
	case 'd':
	case'D':
	case 77:
		if(snake.dir != LEFT)
		snake.dir = RIGHT;
		break;
	case ' ':
		while (1)
		{
			if (_getch() == ' ')
				return; 
		}
	}
	}
	

}
void EatFood()
{
	if (food.flag && snake.coor[0].x >= food.x-food.r && snake.coor[0].x <= food.x+food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
		}
	if( ! food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}
void Snakedie()
{
	for (int i = 1; i <= snake.size; i++)
	{
		if ((snake.coor[0].x == snake.coor[i].x) && (snake.coor[0].y == snake.coor[i].y))
		{
			while (1);
		}
	}
}
int main()
{
	GameInit();
	while (1)
	{
		snakeMove();
		GameDraw();
		keyControl();
		EatFood();
		Sleep(100);
	}
	return 0;
}