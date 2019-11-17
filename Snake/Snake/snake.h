#pragma once
#include <iostream>
#include "wall.h"
#include "food.h"

using namespace std;

class Snake
{
public:
	Snake(Wall& tempWall, Food & food);
	// 节点

	enum 
	{
		UP = 'w',
		DOWN = 's',
		LEFT = 'a',
		RIGHT = 'd'
	};

	struct Point
	{
		// 数据域
		int x;
		int y;

		// 指针域
		Point* next;
	};

	void initSnake();

	// 销毁节点
	void destroyPoint();

	// 添加节点
	void addPoint(int x, int y);

	// 删除节点
	void delPoint();

	// 蛇的移动
	bool move(char key);

	// 设定难度
	// 获取刷屏时间
	int getSleepTime();

	// 获取蛇的身段
	int countList();

	// 获取分数
	int getScore();

	Point * pHead;

	Wall & wall;

	Food& food;

	bool isRoll; // 判断循环标示
};