#pragma once
#ifndef _FILE_SYSTEM_
#define _FILE_SYSTEM_
#include<string>
#include<list>
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
	int size;  //ռ�ô��̿�����
	FCB(int Number, string Name, int Type, int Address = -1, int Size = 0);
	bool set(int Number, string Name, int Type, int Address = -1, int Size = 0);
	FCB();
};

class Dirnode {
	//���Ŀ¼�ṹ�����Ľڵ�
public:
	Dirnode();
	Dirnode(string Name, int Father);
	string name;
	int father;
	list<int> children;
	bool add_child(int FCB_numer);
	bool del_child(int FCB_numer);
private:
	list<int>::iterator it = children.begin();
};

class blk {
public:
	char space[1000];
	int next;
	blk();
};

class FileSystem {
public:
	FileSystem();

private:
	Superblock superblk;
	FCB fcb[FCB_NUM];
	blk disk_blk[BLK_NUM];
	Dirnode* dir_root;
	Dirnode* current_dir;
};

#endif  //_FILE_SYSTEM_

