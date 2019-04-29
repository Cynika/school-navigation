#include <iostream>
#include <fstream>
#define MIN 100
#define MID 1000
#define MAX 10000
#define SAVE_FILE "save.txt"

using namespace std;

typedef struct {
	char name[MID];
	char info[MAX];
}Sight;

typedef struct {
	Sight vexs[MIN];
	int arcs[MID][MID];
	int vexnum, arcnum;
}MGraph;

MGraph m;

void init_debug();
void read();
void check();
void print_logo();
void print_menu();
void print_sightlist();
void print_sightinfo();
void add_sight();
void add_way();
void alter_sight();
void main_work();
void write();
void reset();
int name_to_id(char in[]);

int main()
{
	read();
	check();
	print_logo();
	print_menu();
	main_work();
	reset();
}

void init_debug() {

}

void print_logo() {
	cout << "欢迎使用校园导航系统\n" << endl;
}

void print_menu() {
	cout << "1.查询地点信息\n"
		<< "2.查询地点间位置\n"
		<< "3.增加一个景点及信息\n"
		<< "4.修改一个景点的信息\n"
		<< "5.增加一条新路径\n"
		<< "6.退出\n"
		<< "请输入:\n" << endl;
}

void print_sightlist() {
	cout << "景点列表：\n" << endl;
	for (int i = 0; i < m.vexnum; i++) {
		cout << i + 1 << "." << m.vexs[i].name << "\n" << endl;
	}

}
void print_sightinfo() {
	cout << "输入序号选择景点：\n" << endl;
	int i;
	cin >> i;
	cout << m.vexs[i - 1].info << endl;
}

void print_far() {
	int s, e;
	cout << "输入起点" << endl;
	cin >> s;
	cout << "输入终点" << endl;
	cin >> e;
	cout << "距离：" << m.arcs[s - 1][e - 1] << endl;
}

void add_sight() {
	cout << "输入名字:\n" << endl;
	cin >> m.vexs[m.vexnum].name;
	cout << "输入简介:\n" << endl;
	cin >> m.vexs[m.vexnum].info;
	m.vexnum++;
	write();
	cout << "添加完成！\n" << endl;
}

void alter_sight() {
	int i;
	cout << "输入序号:\n" << endl;
	cin >> i;
	cout << "输入新简介:\n" << endl;
	cin >> m.vexs[i - 1].info;
	write();
	cout << "修改完成！\n" << endl;
}

void add_way() {
	int s, e, f;
	cout << "输入起点序号:\n" << endl;
	cin >> s;
	cout << "输入终点序号:\n" << endl;
	cin >> e;
	cout << "输入距离:\n" << endl;
	cin >> f;
	m.arcs[s - 1][e - 1] = f;
	m.arcs[e - 1][s - 1] = f;
	m.arcnum++;
	write();
	cout << "添加完成！\n" << endl;
}

void main_work()
{
	int i;
	cin >> i;
	switch (i)
	{
	case 1:
		print_sightlist();
		print_sightinfo();
		break;
	case 2:
		print_sightlist();
		print_far();
		break;
	case 3:
		print_sightlist();
		add_sight();
		break;
	case 4:
		print_sightlist();
		alter_sight();
		break;
	case 5:
		print_sightlist();
		add_way();
		break;
	case 6:
		exit(0);
		break;
	default:
		cout << "不规范输入" << endl;
		break;
	}
}

void check() {
	m.vexnum = 0;
	m.arcnum = 0;
	for (int i = 0; i < MIN; i++) {
		if (*m.vexs[i].name != NULL)
			m.vexnum++;
	}
	for (int i = 0; i < MID; i++) {
		for (int j = 0; j < MID; j++) {
			if (m.arcs[i][j] != 0 && i < j)
			{
				m.arcnum++;
			}
		}
	}
}

void read() {
	ifstream readFile(SAVE_FILE);
	readFile >> m.vexnum >> m.arcnum;
	for (int i = 0; i < m.vexnum; i++) {
		readFile >> m.vexs[i].name >> m.vexs[i].info;
	}
	for (int i = 0; i < m.arcnum; i++) {
		char start[MIN], end[MIN];
		int far;
		readFile >> start >> end >> far;
		m.arcs[name_to_id(start)][name_to_id(end)] = far;
		m.arcs[name_to_id(end)][name_to_id(start)] = far;
	}
	readFile.close();
}
void write() {
	check();
	ofstream OutFile(SAVE_FILE);
	OutFile << m.vexnum << " " << m.arcnum << "\n";
	for (int i = 0; i < m.vexnum; i++) {
		OutFile << m.vexs[i].name << " " << m.vexs[i].info << "\n";
	}
	for (int i = 0; i < m.arcnum; i++) {
		for (int j = 0; j < m.arcnum; j++) {
			if (m.arcs[i][j] != 0 && i < j)
			{
				OutFile << " " << m.vexs[i].name << " " << m.vexs[j].name << " " << m.arcs[i][j] << "\n";
			}
		}
	}
	OutFile.close();
}
int name_to_id(char in[]) {
	for (int i = 0; i < m.vexnum; i++) {
		if (strlen(m.vexs[i].name) != strlen(in)) {
			continue;
		}
		else {
			for (int n = 0; n < strlen(in); n++)
			{
				if (m.vexs[i].name[n] == in[n]) {
					return i;
				}
			}
		}
	}
	return NULL;
}
void reset() {
	cout << "1.返回主菜单\n2.退出程序\n" << endl;
	int i;
	cin >> i;
	switch (i)
	{
	case 1:
		main();
		break;
	case 2:
		exit(0);
		break;
	default:
		cout << "不规范输入\n" << endl;
		break;
	}
}