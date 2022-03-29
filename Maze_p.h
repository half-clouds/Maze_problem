#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
# include<assert.h>
using namespace std;
int endx = 12, endy = 16;
struct  offsets	//a、b是x、y方向上的偏移
{
	int a;
	int b;
};
offsets direction[8] = {
	//定义8个方向
	{-1, 0}, // 北：{-1, 0, "N"}
	{-1, 1}, // 东北：{-1, 1, "NE"}
	{0, 1}, // 东：{0, 1, "E"}
	{1, 1}, // 东南：{1, 1, "SE"}
	{1, 0}, // 南：{1, 0, "S"}
	{1, -1}, // 西南：{1, -1, "SW"}
	{0, -1}, // 西：{0, -1, "W"}
	{-1, -1} // 西北：{-1, -1, "NW"}
};
class Maze {
public:
	int maze[14][17]; // 迷宫数组
	int mark[14][17];
	//入口：1 0
	//出口：12 16
	Maze() {
		for (int i = 0; i < 14; i++)
			for (int j = 0; j < 17; j++) {
				maze[i][j] = 1; mark[i][j] = 0;
			}
		maze[1][0] = 0; //入口
		mark[1][0] = 1; //标记入口
		maze[12][16] = 0; //出口 x=12 y=16
	}
	void create_map(int maze[][17]) {
		int num1 = 0, num0 = 0;
		srand((int)time(0)); //设置随机种子
		int num;
		for (int i = 1; i < 13; i++)
			for (int j = 1; j < 16; j++) {
				num = (rand() % 3); //定义随机数 0/1
				//if (num == 0||num==2)num0++; else { num1++; }
				if (num == 2)num = 0;  // 通道和墙为2:1
				maze[i][j] = num;
			}
	}
	void print_map(int maze[][17]) {
		for (int i = 0; i < 14; i++) {
			for (int j = 0; j < 17; j++) {
				cout << maze[i][j] << " ";
			}
			cout << endl;
		}
	}
	//打印地图
	bool search_path(int x, int y);
	void BFS();
	void dfs_stack(int x, int y);
	void DFS_nr(int x, int y);
};
bool Maze::search_path(int x, int y) {
	int i, g, h; // g, h记录位置信息 g存储横坐标 h存储纵坐标
	if (x == endx && y == endy) // 出口坐标
		return true;
	for (i = 0; i < 8; i++) {
		g = x + direction[i].a;
		h = y + direction[i].b;
		// 找下一位置寻找通向出口的路径
		if (maze[g][h] == 0 && mark[g][h] == 0) { // 如果通且未被访问过
			mark[g][h] = 1; // 标记为已访问过
			if (search_path(g, h)) { // 递归寻找
				cout << "(" << g << "," << h << ")" << "\t"; // 逆向输出路径坐标
				return true;
			}
		}
		// 回溯，换一个方向再试探通向出口的路径
	}
	return false; // 找不到通向出口的路径
}
//错的非递归搜索
//void Maze::dfs_stack(int x, int y) {
//	for (int i = 0; i < 14; i++)
//		for (int j = 0; j < 17; j++) {
//			mark[i][j] = 0;
//		} //初始化标记数组
//	mark[x][y] = 1; //标记起点
//	stack <int> sx, sy; sx.push(x); sy.push(y);
//	cout << "起点是： " << "(1,0)\n";
//	for (int i = 0; i < 14; i++)
//		for (int j = 0; j < 17; j++) {
//			if (maze[i][j] == 0 && mark[i][j] == 0) {
//				mark[i][j] = 1; sx.push(i); sy.push(j);
//			}
//		}
//	while (!sx.empty() && !sy.empty()) {
//		int sx_top = sx.top(), sy_top = sy.top();
//		mark[sx_top][sy_top] = 1;
//		cout << "(" << sx_top << "," << sy_top << ")" << "←"; sx.pop(); sy.pop();
//		for (int i = 0; i < 14; i++)
//			for (int j = 0; j < 17; j++) {
//				if (maze[i][j] == 0 && mark[i][j] == 0) {
//					mark[i][j] = 1; sx.push(i); sy.push(j);
//				}
//			}
//	}
//
//}

void Maze::DFS_nr(int x,int y) {
	int* p = NULL;
	for (int i = 0; i < 14; i++)
		for (int j = 0; j < 17; j++) {
			mark[i][j] = 0;
		} //初始化标记数组
	mark[1][0] = 1; //标记起点
	stack <int*> sk;  //栈内存放指针 指针用于存放横纵坐标
	p = new int[2];
	p[0] = x;
	p[1] = y; 
	sk.push(p); //起点入栈
	p = NULL;
	int g, h,i,j,n;
	while (sk.empty() == false) {
		int flag = 0; //标志是否到终点
		n = 0;
		int* q = sk.top(); sk.pop();//取出栈顶的数组 并出栈
		i = q[0], j = q[1]; cout << "(" << i << "," << j << ")\t"; //用起点开始深搜
		while (n < 8) {   //成广度优先了
			g = i + direction[n].a;
			h = j + direction[n].b;
			//if (g < 0 || g>14 || h < 0 || h>17)continue;
			if (maze[g][h] == 0 && mark[g][h] == 0) {
				mark[g][h] = 1;
				p = new int[2];
				p[0] = g;
				p[1] = h;
				sk.push(p); p = NULL;
			}
			else {
				n++;
			}
			if (g == endx && h == endy)
			{
				cout <<"("<< g << "," << h << ")\t";
				flag = 1; break;
			}
		}
		if (flag==1) {
			return;
		}
	}
}

//最短路径
struct node {
	int x, y;
	int pre; //来到此点的出发点 
};
struct node queue[50]; //存储路径的队列
void print(struct node a) //实现路径输出的函数
{
	if (a.pre == -1)
	{
		cout << "(" << a.x << "," << a.y << ")" << "\t";
		return;
	}
	else
	{
		print(queue[a.pre]);
		cout << "(" << a.x << "," << a.y << ")" << "\t";
	}
}
void Maze::BFS() {
	for (int i = 0; i < 14; i++)
		for (int j = 0; j < 17; j++) {
			mark[i][j] = 0;
		} //初始化标记数组
	int head = 0, tail = 0, i, nextx, nexty; //g存储横坐标 h存储纵坐标
	queue[tail].x = 1; queue[tail].y = 0; queue[tail].pre = -1; mark[1][0] = 1; //标记入口
	//起点入队列 并标记
	tail++; //尾巴+1
	while (head < tail) {
		int flag = 0; //标志是否到终点
		for (i = 0; i < 8; i++) {
			nextx = queue[head].x + direction[i].a;
			nexty = queue[head].y + direction[i].b;
			if (nextx < 0 || nexty < 0 || nextx>14 || nexty>17)continue;
			if (maze[nextx][nexty] == 0 && mark[nextx][nexty] == 0) {
				mark[nextx][nexty] = 1; // 标记为已访问过
				queue[tail].x = nextx;  //入队列
				queue[tail].y = nexty;
				queue[tail].pre = head;
				tail++; //队列长度++
			}
			if (nextx == endx && nexty == endy) {
				flag = 1; break;
			}
		}
		if (flag) //到达目的地后调用函数输出路径
		{
			print(queue[tail - 1]);
			break;
		}
		head++; //出队
	}
	return;
}