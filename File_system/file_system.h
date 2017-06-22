#pragma once
#ifndef _FILE_SYSTEM_
#define _FILE_SYSTEM_
#include<string>
#include<list>
#define FILE 1
#define DIRECTORY 0
#define FCB_NUM 1024  //FCB数目
#define BLK_NUM 1024*80  //磁盘块数目
using namespace std;
class Superblock {
	//位图区域，记录FCB和Disk区域的使用情况
public:
	Superblock();
	int remain_fcb();
	int remian_blk();
	int get_fcb();
	int get_blk();
	
private:
	bool fcb_map[FCB_NUM];  //节点位图
	bool blk_map[BLK_NUM];  //磁盘块位图
	int freefcb_num = FCB_NUM;  //剩余节点数量
	int freeblk_num = BLK_NUM;  //剩余磁盘块数量

};

class FCB {
	//FCB
public:
	string name;
	int type;
	int number;  //FCB号
	int address;  //占用首磁盘块号
	int size;  //占用磁盘块数量
	FCB(int Number, string Name, int Type, int Address = -1, int Size = 0);
	bool set(int Number, string Name, int Type, int Address = -1, int Size = 0);
	FCB();
};

class Dirnode {
	//多层目录结构中树的节点
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

