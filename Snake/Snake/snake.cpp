#include "snake.h"
#include<Windows.h>

void gotoxy1(HANDLE hOut1, int x, int y)
{
	COORD pos;
	pos.X = x;             //横坐标
	pos.Y = y;            //纵坐标
	SetConsoleCursorPosition(hOut1, pos);
}
HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量


Snake::Snake(Wall & tempWall, Food & tempFood):wall(tempWall), food(tempFood)
{
	pHead = NULL;
	isRoll = false;
}

void Snake::initSnake()
{
	destroyPoint();
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
	
}

void Snake::destroyPoint()
{
	Point* pCur = pHead;
	while (pHead != NULL)
	{
		pCur = pHead->next;
		delete pHead;

		pHead = pCur;
	}
}

void Snake::addPoint(int x, int y)
{
	// 创建新的节点
	Point* newPoint = new Point;
	newPoint->x = x;
	newPoint->y = y;
	newPoint->next = NULL;

	// 如果原来的头不为空，改为身子
	if (pHead != NULL) 
	{
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy1(hOut1, pHead->y * 2, pHead->x);
		cout << "=";
	}

	newPoint->next = pHead;

	pHead = newPoint; // 更新头部
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy1(hOut1, pHead->y * 2, pHead->x);
	cout << "@";
}

void Snake::delPoint()
{
	// 判断两个节点以上才做删除
	if (pHead == NULL || pHead->next == NULL) 
	{
		return;
	}

	Point* pCur = pHead->next;
	Point* pPre = pHead;

	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	// 删除尾节点

	wall.setWall(pCur->x, pCur->y, ' ');
	gotoxy1(hOut1, pCur->y * 2, pCur->x);
	cout << " ";

	delete pCur;
	pCur = NULL;
	pPre->next = NULL;

}

bool Snake::move(char key)
{
	int x = pHead->x;
	int y = pHead->y;

	switch (key)
	{
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;

	default:
		break;
	}

	// 判断如果是下一步碰到尾巴，不应该死亡
	Point* pCur = pHead->next;
	Point* pPre = pHead;

	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	if (pCur->x == x && pCur->y == y)
	{
		// 碰到尾巴，循环
		isRoll = true;
	}
	else
	{
		// 判断用户要到达的位置是否成功
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			addPoint(x, y);
			delPoint();
			system("cls");
			wall.drawWall();
			cout << "Score : " << getScore() << "分" << endl;
			cout << "GAME OVER !!!" << endl;
			return false;
		}
	}
	
	
	// 移动成功，分两种
	// 吃到食物，未迟到食物
	if (wall.getWall(x, y) == '#') 
	{
		addPoint(x, y);

		// 重新设置食物
		food.setFood();
	}
	else
	{
		addPoint(x, y);
		delPoint();
		if (isRoll == true) 
		{
			wall.setWall(x, y, '@');
			gotoxy1(hOut1, y * 2, x);
			cout << "@";
			
		}
	}

	return true;
}

int Snake::getSleepTime()
{
	int sleepTime = 0;
	int size = countList();
	if (size < 5) 
	{
		sleepTime = 300;
	}
	else if (size >= 5 && size <= 8) 
	{
		sleepTime = 200;
	}
	else
	{
		sleepTime = 100;
	}
	return sleepTime;
}

int Snake::countList()
{
	int size = 0;
	Point* curPoint = pHead;

	while (curPoint != NULL)
	{
		size++;
		curPoint = curPoint->next;
	}
	return size;
}

int Snake::getScore()
{
	int size = countList();

	int score = (size - 3) * 100;

	return score;
}
