#ifndef block_H
#define block_H
#include "memory.h"

class Block {
	public:
		int startAddress;
		int size;
		string Pid;
		string Bid;
		Block* next;
		Block();
		void print();
		Block* search(int size,string mode);
		void deleteB(Block* p);
		void accom();
};


#endif
