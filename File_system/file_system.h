#pragma once
#ifndef _FILE_SYSTEM_
#define _FILE_SYSTEM_
#include<string>
#include<iostream>
#include<fstream>
#include<deque>
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
	bool free_fcb(int Number);
	bool free_blk(int Number);
	
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
	int size;  //文件大小
	FCB(int Number, string Name, int Type, int Address = -1, int Size = 0);
	bool set(int Number, string Name, int Type, int Address = -1, int Size = 0);
	FCB();
};

class Dirnode {
	//多层目录结构中树的节点
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
	string current_dirname();  //显示当前目录
	bool ls();  //列出当前文件夹的所有文件
	bool cd(string FolderName);   //进入下级目录
	bool mkdir(string FolderName);   //创建目录
	bool touch(string FileName);  //创建空白文件
	bool rm(string Name);   //删除文件或目录
	bool mvin(string FileName);  //将已有文件移入文件系统
	bool mvout(string FileName);  //导出文件系统中的文件（不删除）
	bool mkfs();    //格式化文件系统
	bool savS(string Name);  //将文件系统保存至磁盘
	bool recS(string Name);  //从磁盘文件恢复系统
	
private:
	int search(string Name);     //查找当前目录
	Superblock superblk;   //位图区
	FCB fcb[FCB_NUM];      //fcb区
	blk disk_blk[BLK_NUM]; //磁盘块区
	Dirnode dirnodes[FCB_NUM];  //目录结点区
	int dir_root;   //根目录结点指针
	int current_dir;  //当前目录指针
	bool free_file(int number);
};

#endif  //_FILE_SYSTEM_

