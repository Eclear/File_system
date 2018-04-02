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
	cout << "��ӭ����ģ��Linux�ļ�ϵͳ������help��ȡ��������˵��\n";
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
			cout << setw(12) << "����" << setw(20) << "����" << setw(20) << "��ʽ\n"
				<< setw(12) << "ls" << setw(20) << "��ʾ��ǰĿ¼" << setw(20) << "ls\n"
				<< setw(12) << "cd" << setw(20) << "����Ŀ¼" << setw(20) << "cd Ŀ¼��\n"
				<< setw(12) << "mkdir" << setw(20) << "����Ŀ¼" << setw(20) << "mkdir Ŀ¼��\n"
				<< setw(12) << "touch" << setw(20) << "�������ļ�" << setw(20) << "touch �ļ���\n"
				<< setw(12) << "rm" << setw(20) << "ɾ���ļ���Ŀ¼" << setw(20) << "rm �ļ���Ŀ¼��\n"
				<< setw(12) << "mvin" << setw(20) << "���������ļ������ļ�ϵͳ" << setw(20) << "mvin �ļ���ַ\n"
				<< setw(12) << "mvout" << setw(20) << "����ϵͳ���ļ�" << setw(20) << "mvout �ļ���\n"
				<< setw(12) << "mkfs" << setw(20) << "��ʽ��ϵͳ" << setw(20) << "mkfs\n"
				<< setw(12) << "savS" << setw(20) << "����ϵͳ" << setw(20) << "savS �浵��\n"
				<< setw(12) << "recS" << setw(20) << "�Ӵ浵�ָ�ϵͳ" << setw(20) << "recS �浵��\n"
				<< setw(12) << "help" << setw(20) << "��ʾ�������" << setw(20) << "help\n";
			break;
		}
		}
		cout << "admin:" << F.current_dirname() << "/ $ ";
		cin >> com;
		choice = get_choice(com);
	}
	
	return 0;
}
