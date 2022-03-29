#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
# include<assert.h>
using namespace std;
int endx = 12, endy = 16;
struct  offsets	//a��b��x��y�����ϵ�ƫ��
{
	int a;
	int b;
};
offsets direction[8] = {
	//����8������
	{-1, 0}, // ����{-1, 0, "N"}
	{-1, 1}, // ������{-1, 1, "NE"}
	{0, 1}, // ����{0, 1, "E"}
	{1, 1}, // ���ϣ�{1, 1, "SE"}
	{1, 0}, // �ϣ�{1, 0, "S"}
	{1, -1}, // ���ϣ�{1, -1, "SW"}
	{0, -1}, // ����{0, -1, "W"}
	{-1, -1} // ������{-1, -1, "NW"}
};
class Maze {
public:
	int maze[14][17]; // �Թ�����
	int mark[14][17];
	//��ڣ�1 0
	//���ڣ�12 16
	Maze() {
		for (int i = 0; i < 14; i++)
			for (int j = 0; j < 17; j++) {
				maze[i][j] = 1; mark[i][j] = 0;
			}
		maze[1][0] = 0; //���
		mark[1][0] = 1; //������
		maze[12][16] = 0; //���� x=12 y=16
	}
	void create_map(int maze[][17]) {
		int num1 = 0, num0 = 0;
		srand((int)time(0)); //�����������
		int num;
		for (int i = 1; i < 13; i++)
			for (int j = 1; j < 16; j++) {
				num = (rand() % 3); //��������� 0/1
				//if (num == 0||num==2)num0++; else { num1++; }
				if (num == 2)num = 0;  // ͨ����ǽΪ2:1
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
	//��ӡ��ͼ
	bool search_path(int x, int y);
	void BFS();
	void dfs_stack(int x, int y);
	void DFS_nr(int x, int y);
};
bool Maze::search_path(int x, int y) {
	int i, g, h; // g, h��¼λ����Ϣ g�洢������ h�洢������
	if (x == endx && y == endy) // ��������
		return true;
	for (i = 0; i < 8; i++) {
		g = x + direction[i].a;
		h = y + direction[i].b;
		// ����һλ��Ѱ��ͨ����ڵ�·��
		if (maze[g][h] == 0 && mark[g][h] == 0) { // ���ͨ��δ�����ʹ�
			mark[g][h] = 1; // ���Ϊ�ѷ��ʹ�
			if (search_path(g, h)) { // �ݹ�Ѱ��
				cout << "(" << g << "," << h << ")" << "\t"; // �������·������
				return true;
			}
		}
		// ���ݣ���һ����������̽ͨ����ڵ�·��
	}
	return false; // �Ҳ���ͨ����ڵ�·��
}
//��ķǵݹ�����
//void Maze::dfs_stack(int x, int y) {
//	for (int i = 0; i < 14; i++)
//		for (int j = 0; j < 17; j++) {
//			mark[i][j] = 0;
//		} //��ʼ���������
//	mark[x][y] = 1; //������
//	stack <int> sx, sy; sx.push(x); sy.push(y);
//	cout << "����ǣ� " << "(1,0)\n";
//	for (int i = 0; i < 14; i++)
//		for (int j = 0; j < 17; j++) {
//			if (maze[i][j] == 0 && mark[i][j] == 0) {
//				mark[i][j] = 1; sx.push(i); sy.push(j);
//			}
//		}
//	while (!sx.empty() && !sy.empty()) {
//		int sx_top = sx.top(), sy_top = sy.top();
//		mark[sx_top][sy_top] = 1;
//		cout << "(" << sx_top << "," << sy_top << ")" << "��"; sx.pop(); sy.pop();
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
		} //��ʼ���������
	mark[1][0] = 1; //������
	stack <int*> sk;  //ջ�ڴ��ָ�� ָ�����ڴ�ź�������
	p = new int[2];
	p[0] = x;
	p[1] = y; 
	sk.push(p); //�����ջ
	p = NULL;
	int g, h,i,j,n;
	while (sk.empty() == false) {
		int flag = 0; //��־�Ƿ��յ�
		n = 0;
		int* q = sk.top(); sk.pop();//ȡ��ջ�������� ����ջ
		i = q[0], j = q[1]; cout << "(" << i << "," << j << ")\t"; //����㿪ʼ����
		while (n < 8) {   //�ɹ��������
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

//���·��
struct node {
	int x, y;
	int pre; //�����˵�ĳ����� 
};
struct node queue[50]; //�洢·���Ķ���
void print(struct node a) //ʵ��·������ĺ���
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
		} //��ʼ���������
	int head = 0, tail = 0, i, nextx, nexty; //g�洢������ h�洢������
	queue[tail].x = 1; queue[tail].y = 0; queue[tail].pre = -1; mark[1][0] = 1; //������
	//�������� �����
	tail++; //β��+1
	while (head < tail) {
		int flag = 0; //��־�Ƿ��յ�
		for (i = 0; i < 8; i++) {
			nextx = queue[head].x + direction[i].a;
			nexty = queue[head].y + direction[i].b;
			if (nextx < 0 || nexty < 0 || nextx>14 || nexty>17)continue;
			if (maze[nextx][nexty] == 0 && mark[nextx][nexty] == 0) {
				mark[nextx][nexty] = 1; // ���Ϊ�ѷ��ʹ�
				queue[tail].x = nextx;  //�����
				queue[tail].y = nexty;
				queue[tail].pre = head;
				tail++; //���г���++
			}
			if (nextx == endx && nexty == endy) {
				flag = 1; break;
			}
		}
		if (flag) //����Ŀ�ĵغ���ú������·��
		{
			print(queue[tail - 1]);
			break;
		}
		head++; //����
	}
	return;
}