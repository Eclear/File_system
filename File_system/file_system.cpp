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

blk::blk() {
	for (int i = 0;i < 1000;i++) {
		space[i] = '0';
	}
	next = -1;
}

bool Dirnode::add_child(int FCB_numer)
{
	children.push_back(FCB_numer);
	return true;
}

bool Dirnode::del_child(int FCB_numer)
{
	for (it = children.begin();it != children.end();it++) {
		if (*it == FCB_numer) break;
	}
	if (it != children.end()) {
		return true;
		children.erase(it);
	}
	else return false;
}

FileSystem::FileSystem()
{
	fcb[0].set(0, "root", DIRECTORY);
	dir_root = new Dirnode("root", 0);
	current_dir = dir_root;
}
