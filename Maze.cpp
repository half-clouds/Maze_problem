#include <iostream>
#include"Maze_p.h"
using namespace std;
int main()
{
	int choice;
	Maze *m = new Maze();
	while (1) {
		cout << "\t\t*********菜单*********\n";
		cout << "\t\t*********1.生成迷宫地图*********\n";
		cout << "\t\t*********2.打印迷宫地图*********\n";
		cout << "\t\t*********3.递归算法求可行路线*********\n";
		cout << "\t\t*********4.非递归算法求可行路线*********\n";
		cout << "\t\t*********5.输出最短路径*********\n";
		cout << "\t\t*********0.结束*********\n";
		cout << "输入你的选择： "; cin >> choice;
		switch (choice)
		{
		case 1:
			//cout << "初始化：\n"; //m->print_map(m->maze);
			m->create_map(m->maze); cout << "地图已随机生成！\n";
			break;
		case 2:
			cout << "生成地图：\n"; m->print_map(m->maze);
			break;
		case 3:
			cout << "路线:\n";
			if (m->search_path(1, 0) == false)cout << "无可行解！\n"; 
			cout << "(1,0)"<<endl;
			break;
		case 4:
			//m->dfs_stack(1, 0);
			m->DFS_nr(1, 0);
			cout << endl; break;
		case 5:
			m->BFS(); cout << endl; break;
		default:
			break;
		}
		cout << "是否清屏(1/0),请输入\n"; int a; cin >> a;
		if (a == 1) { system("cls"); }
	}

	return 0;
}


