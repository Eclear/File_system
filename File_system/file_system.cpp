#include "file_system.h"

Superblock::Superblock()
{
	for (int i = 0;i < FCB_NUM;i++) {
		fcb_map[i] = 0;
	}
	for (int i = 0;i < BLK_NUM;i++) {
		blk_map[i] = 0;
	}
	
	int freefcb_num = FCB_NUM;  
	int freeblk_num = BLK_NUM;  
}

int Superblock::remain_fcb()
{
	return freefcb_num;
}

int Superblock::remian_blk()
{
	return freeblk_num;
}

int Superblock::get_fcb()
{
	if (freefcb_num > 0) {
		int i = 0;
		for (;i < FCB_NUM;i++) {
			if (!fcb_map[i]) break;
		}
		if (i < FCB_NUM) {
			freefcb_num--;
			fcb_map[i] = 1;
			return i;
		}
	}
	return -1;
}

int Superblock::get_blk()
{
	if (freeblk_num > 0) {
		int i = 0;
		for (;i < BLK_NUM;i++) {
			if (!blk_map[i]) break;
		}
		if (i < BLK_NUM) {
			freeblk_num--;
			blk_map[i] = 1;
			return i;
		}
	}
	return -1;
}

bool Superblock::free_fcb(int Number)
{
	if (Number < 0 || Number >= FCB_NUM) return false;
	else {
		fcb_map[Number] = 0;
		return true;
	}
	
}

bool Superblock::free_blk(int Number)
{
	if (Number < 0 || Number >= BLK_NUM) return false;
	else {
		blk_map[Number] = 0;
		return true;
	}
}

FCB::FCB(int Number, string Name, int Type, int Address, int Size)
{
	number = Number;
	name = Name;
	type = Type;
	address = Address;
	size = Size;
}

bool FCB::set(int Number, string Name, int Type, int Address, int Size)
{
	number = Number;
	name = Name;
	type = Type;
	address = Address;
	size = Size;
	return true;
}

FCB::FCB()
{
	name = "-";
	type = -1;
	size = 0;
}

Dirnode::Dirnode()
{
	name = "-";

}

Dirnode::Dirnode(string Name, int Father)
{
	name = Name;
	father = Father;
}

bool Dirnode::set(string Name, int Father)
{
	name = Name;
	father = Father;
	children_num = 0;
	return true;
}

blk::blk() {
	for (int i = 0;i < 1024 - sizeof(int);i++) {
		space[i] = '5';
	}
	next = -1;
}

bool Dirnode::add_child(int FCB_numer)
{
	children[children_num]=FCB_numer;
	children_num++;
	return true;
}

bool Dirnode::del_child(int FCB_numer)
{
	if (children_num > 0) {
		children_num--;
		return true;
	}
	else return false;
}

FileSystem::FileSystem()
{
	int i = superblk.get_fcb();
	fcb[i].set(i, "root", DIRECTORY);
	dirnodes[i] = Dirnode("root", 0);
	dir_root = i;
    current_dir = dir_root;

}

string FileSystem::current_dirname()
{
	return fcb[current_dir].name;
}

bool FileSystem::ls()
{
	if (dirnodes[current_dir].children_num==0) {
		cout << "NULL\n";
		return false;
	}
	for (int i = 0;i< dirnodes[current_dir].children_num;i++) {
		cout << fcb[dirnodes[current_dir].children[i]].name << "  ";
	}
	cout << "\n";
	return true;
}

bool FileSystem::cd(string FolderName)
{
	if (FolderName == "..") {
		current_dir = dirnodes[current_dir].father;
		return true;
	}
	int id=search(FolderName);
	if (id > 0) {
		current_dir = id;
	}
	return false;
}

bool FileSystem::mkdir(string FolderName)
{
	int i = superblk.get_fcb();
	fcb[i].set(i, FolderName, DIRECTORY);
	dirnodes[i].set(FolderName, current_dir);
	dirnodes[current_dir].add_child(i);
	cout << "Folder:  " << FolderName << "  created.\n";
	return true;
}

bool FileSystem::touch(string FileName)
{
	//获取fcb、初始磁盘块
	int fn = superblk.get_fcb();
	int bn = superblk.get_blk();
	if (fn < 0 || bn < 0) {
		cout << "Failed: Space is not enough\n";
		return false;
	}
	//设置fcb
	fcb[fn].set(fn, FileName, FILE, bn, 1);
	//将fcb添加到当前目录
	dirnodes[current_dir].add_child(fn);
	cout << "Successfully created file:" << FileName << "\n"
		<< "fcb number: " << fn << "    start address: " << bn <<"\n";
	return true;
}

bool FileSystem::rm(string Name)
{
	int p1;
	int a;
	deque<int> que;
	int del_number = search(Name);
	if (del_number < 0) {
		return false;
	}
	if (fcb[del_number].type == FILE) {
		//删除文件
		free_file(del_number);
		//删除当前目录中的纪录
		dirnodes[current_dir].del_child(del_number);
		
	}

	else if (fcb[del_number].type == DIRECTORY) {
		//删除目录，层序递归删除目录下的所有纪录
		que.push_back(del_number);
		while (!que.empty()) {
			//头元素出队
			p1 = que.front();
			que.pop_front();

			//如果是目录，将目录的子目录和文件入队
			if (fcb[p1].type == DIRECTORY) {
				while (dirnodes[p1].children_num) {
					a = dirnodes[p1].children[dirnodes[p1].children_num-1];
					que.push_back(a);
					dirnodes[p1].children_num--;
				}
				//解除fcb占用
				superblk.free_fcb(p1);
				//删除父结点中的纪录
				dirnodes[dirnodes[p1].father].del_child(p1);
			}

			//如果是文件，解除文件占用
			if (fcb[p1].type == FILE) {
				free_file(p1);
			}
		}
	}
	cout << "Successfully deleted: " << Name <<"\n";
	return true;
}

bool FileSystem::mvin(string FileName)
{
	
	//新建文件
	touch("copy_"+FileName);
	int fcbn = search("copy_" + FileName);
	int current_address = fcb[fcbn].address;

	int remain_size = 0;
	int fblk_num = 0;
	
	//获取文件大小，保存在fcb中
	ifstream fin(FileName, ios::binary);
	if (!fin) { return false; }
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fcb[fcbn].size = length;

	cout << "Size of the file: " << length << " bytes" << "\n";
	fin.seekg(0, fin.beg);
	//计算所占磁盘块数
	if (length % 1020 != 0) {
		remain_size = length % 1020;
		fblk_num = length / 1020 + 1;
	}
	else {
		fblk_num = length / 1020;
	}
	cout << "First blk: " << current_address << "\n"
		<< "copy_" + FileName << "Takes " << fblk_num << " blocks in total.\n";
	if (length > 1020) {
		
		for (int i = 0;i < fblk_num - 1;i++) {
			fin.read(disk_blk[current_address].space, 1020);
			disk_blk[current_address].next = superblk.get_blk();
			//cout << "Next blk:" << disk_blk[current_address].next << "\n";
			current_address = disk_blk[current_address].next;
		}
		if (length % 1020 > 0) {
			fin.read(disk_blk[current_address].space, length%1020);
		}
		else {
			fin.read(disk_blk[current_address].space, 1020);
		}
	}
	else {
		fin.read(disk_blk[current_address].space, length);
		
	}
	fin.close();
	return 0;
}

bool FileSystem::mvout(string FileName)
{
	ofstream fout(FileName, ios::binary);
	int fcbn = search(FileName);
	int fsize = fcb[fcbn].size;
	int current_blk = fcb[fcbn].address;
	int take_blks;
	if (fsize % 1020 != 0) {
		take_blks = fsize / 1020 + 1;
	}
	else {
		take_blks = fsize / 1020;
	}
	
	if (fsize > 1020) {
		for (int i = 0;i < take_blks - 1;i++) {
			fout.write(disk_blk[current_blk].space, 1020);
			current_blk = disk_blk[current_blk].next;
		}
		if (fsize % 1020 != 0) {
			fout.write(disk_blk[current_blk].space, fsize % 1020);
		}
		else {
			fout.write(disk_blk[current_blk].space, 1020);
		}
	}
	else {
		fout.write(disk_blk[current_blk].space, fsize);
	}
	cout << FileName << " successfully moved out\n";
	fout.close();
	return true;
}

bool FileSystem::mkfs()
{
	for (int i = 0;i < FCB_NUM;i++) {
		superblk.free_fcb(i);
	}
	for (int i = 0;i < BLK_NUM;i++) {
		superblk.free_blk(i);
	}
	rm("root");
	cout << "System formated";
	return true;
}

bool FileSystem::savS(string Name)
{
	ofstream fout(Name, ios::binary);
	fout.write((char*)this, sizeof(*this));
	fout.close();
	cout << "Successfully saved to " << Name << "\n";
	return true;
}

bool FileSystem::recS(string Name)
{
	ifstream fin(Name, ios::binary);
	if (!fin) { 
		cout << "File not exist\n";
		return false; 
	}
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, fin.beg);
	fin.read((char*)this, length);
	fin.close();
	cout << "Successfully recovered from " << Name << "\n";
	return true;
}



int FileSystem::search(string Name)
{
	if (Name == "root") {
		return 0;
	}
	for (int i = 0;i< dirnodes[current_dir].children_num;i++) {
		if (fcb[dirnodes[current_dir].children[i]].name == Name) {
			return dirnodes[current_dir].children[i];
		}
	}
	return -2;
}

bool FileSystem::free_file(int number)
{
	int p1, p2;
	//依次清空文件所占磁盘块
	p1 = fcb[number].address;
	p2 = p1;
	for (int i = 0;i < fcb[number].size;i++) {
		p1 = disk_blk[p1].next;
		//delete p2
		superblk.free_blk(p2);
		p2 = p1;
	}
	//更改位图
	superblk.free_fcb(number);
	return true;
}
