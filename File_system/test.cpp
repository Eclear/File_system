#include<iostream>
#include<iomanip>
#include"file_system.h"
using namespace std;
FileSystem F;
string commands[11] = { "ls","cd","mkdir","touch","rm","mvin","mvout","mkfs","savS",
"recS","help"};
int get_choice(string command) {
	int i=-1;
	for (i = 0;i < 11;i++) {
		if (commands[i] == command) {
			break;
		}
	}
	return i;
}
int main() {
	string com,target;
	int choice = -1;
	cout << "欢迎进入模拟Linux文件系统，输入help获取可用命令说明\n";
	cout << "admin:" << F.current_dirname() << "/ $ ";
	cin >> com;
	choice = get_choice(com);
	while (choice >= 0) {
		switch (choice)
		{
		case 0: {
			F.ls();
			break;
		}
		case 1: {
			cin >> target;
			F.cd(target);
			break;
		}
		case 2: {
			cin >> target;
			F.mkdir(target);
			break;
		}
		case 3: {
			cin >> target;
			F.touch(target);
			break;
		}
		case 4: {
			cin >> target;
			F.rm(target);
			break;
		}
		case 5: {
			cin >> target;
			F.mvin(target);
			break;
		}
		case 6: {
			cin >> target;
			F.mvout(target);
			break;
		}
		case 7: {
			F.mkfs();
			break;
		}
		case 8: {
			cin >> target;
			F.savS(target);
			break;
		}
		case 9: {
			cin >> target;
			F.recS(target);
			break;
		}
		
		case 10: {
			cout << setw(12) << "命令" << setw(20) << "功能" << setw(20) << "格式\n"
				<< setw(12) << "ls" << setw(20) << "显示当前目录" << setw(20) << "ls\n"
				<< setw(12) << "cd" << setw(20) << "进入目录" << setw(20) << "cd 目录名\n"
				<< setw(12) << "mkdir" << setw(20) << "创建目录" << setw(20) << "mkdir 目录名\n"
				<< setw(12) << "touch" << setw(20) << "创建空文件" << setw(20) << "touch 文件名\n"
				<< setw(12) << "rm" << setw(20) << "删除文件或目录" << setw(20) << "rm 文件或目录名\n"
				<< setw(12) << "mvin" << setw(20) << "将磁盘中文件导入文件系统" << setw(20) << "mvin 文件地址\n"
				<< setw(12) << "mvout" << setw(20) << "导出系统中文件" << setw(20) << "mvout 文件名\n"
				<< setw(12) << "mkfs" << setw(20) << "格式化系统" << setw(20) << "mkfs\n"
				<< setw(12) << "savS" << setw(20) << "保存系统" << setw(20) << "savS 存档名\n"
				<< setw(12) << "recS" << setw(20) << "从存档恢复系统" << setw(20) << "recS 存档名\n"
				<< setw(12) << "help" << setw(20) << "显示命令及功能" << setw(20) << "help\n";
			break;
		}
		}
		cout << "admin:" << F.current_dirname() << "/ $ ";
		cin >> com;
		choice = get_choice(com);
	}
	
	return 0;
}
