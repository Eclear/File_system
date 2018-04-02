#pragma once
#ifndef _FILE_SYSTEM_
#define _FILE_SYSTEM_
#include<string>
#include<iostream>
#include<fstream>
#include<deque>
#define FILE 1
#define DIRECTORY 0
#define FCB_NUM 1024  //FCB��Ŀ
#define BLK_NUM 1024*80  //���̿���Ŀ
using namespace std;
class Superblock {
	//λͼ���򣬼�¼FCB��Disk�����ʹ�����
public:
	Superblock();
	int remain_fcb();
	int remian_blk();
	int get_fcb();
	int get_blk();
	bool free_fcb(int Number);
	bool free_blk(int Number);
	
private:
	bool fcb_map[FCB_NUM];  //�ڵ�λͼ
	bool blk_map[BLK_NUM];  //���̿�λͼ
	int freefcb_num = FCB_NUM;  //ʣ��ڵ�����
	int freeblk_num = BLK_NUM;  //ʣ����̿�����

};

class FCB {
	//FCB
public:
	string name;
	int type;
	int number;  //FCB��
	int address;  //ռ���״��̿��
	int size;  //�ļ���С
	FCB(int Number, string Name, int Type, int Address = -1, int Size = 0);
	bool set(int Number, string Name, int Type, int Address = -1, int Size = 0);
	FCB();
};

class Dirnode {
	//���Ŀ¼�ṹ�����Ľڵ�
public:
	Dirnode();
	Dirnode(string Name, int Father);
	bool set(string Name, int Father);
	string name;
	int father;
	int children[20];
	int children_num = 0;
	bool add_child(int FCB_numer);
	bool del_child(int FCB_numer);
	

};

class blk {
public:
	char space[1024-sizeof(int)];
	int next;
	blk();
};


class FileSystem {
public:
	FileSystem();
	string current_dirname();  //��ʾ��ǰĿ¼
	bool ls();  //�г���ǰ�ļ��е������ļ�
	bool cd(string FolderName);   //�����¼�Ŀ¼
	bool mkdir(string FolderName);   //����Ŀ¼
	bool touch(string FileName);  //�����հ��ļ�
	bool rm(string Name);   //ɾ���ļ���Ŀ¼
	bool mvin(string FileName);  //�������ļ������ļ�ϵͳ
	bool mvout(string FileName);  //�����ļ�ϵͳ�е��ļ�����ɾ����
	bool mkfs();    //��ʽ���ļ�ϵͳ
	bool savS(string Name);  //���ļ�ϵͳ����������
	bool recS(string Name);  //�Ӵ����ļ��ָ�ϵͳ
	
private:
	int search(string Name);     //���ҵ�ǰĿ¼
	Superblock superblk;   //λͼ��
	FCB fcb[FCB_NUM];      //fcb��
	blk disk_blk[BLK_NUM]; //���̿���
	Dirnode dirnodes[FCB_NUM];  //Ŀ¼�����
	int dir_root;   //��Ŀ¼���ָ��
	int current_dir;  //��ǰĿ¼ָ��
	bool free_file(int number);
};

#endif  //_FILE_SYSTEM_

