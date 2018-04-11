#include "memory.h"
#include "block.h"
#include <iostream>
#include <iomanip>

Block::Block() {
	startAddress=0;
        size=0;
        Pid="";
        Bid="";
        next=0;
	}
/***************************************************************
Function: print

Use:      this prints out the starting addresses and sizes of processes

Arguments: 1. none

Returns:   nothing
***************************************************************/
void Block::print() {
	Block* t=this;
	int total = 0;
	if(t == 0) {
		cout << "(NONE)" << endl;
		return;
	}
		cout << "Start Address      Size" << endl;
	while(t != 0) {
		cout << setw(10)<< t->startAddress<< "     " << setw(10) << t->size <<endl;
		total=total+t->size;
		t=t->next;
	}
	cout<< "Total size of the list:" << total << endl;
}
/***************************************************************
Function: search

Use:      this searches for what block to use depending on algorith

Arguments: 1. size of block.
           2. string what algorithm to use

Returns:   block object
***************************************************************/
Block* Block::search(int size,string arg) {
        Block* t=this;
	int i=0;
	int k=0;
	int j=0;
        if(arg == "F") { //Searching for the First-Fit block
		while(t!=0) {
			if(t->size>=size)
				return t;
                	t=t->next;
       		 }
}
	else if(arg == "B") {//BF Algorithm
		 while(t!=0) {
			i++;
                        if(t->size==size){
				return t;


				}
			else if(t->size>size) {
				if(k==0){
					k=t->size-size;
					j=i;
					}
				else if(k>t->size-size){//Looking for BF block
					k=t->size-size;
					j=i;
				}
			}
                        t=t->next;
                 }

		if(k>0){
			t=this; //Looks for best fitting block
			for(i=0;i<j-1;i++)
				t=t->next;
			return t;
			}
	}
	else{
		cerr<<"ERROR: Incorrect Argument Provided"<<endl;
		exit(-1);
	    }
	return 0;//error return if incorrect argument (solved earlier so redundant)

}
/***************************************************************
Function: accom

Use:      this merges memory blocks with other free memory blocks

Arguments: none.

Returns:   nothing
***************************************************************/
void Block::accom() {
	Block* t=this;
	while(t!=0 && t->next!=0) {//Runs through the memory blocks
		if((t->startAddress+t->size)==(t->next)->startAddress && ((t->next)->size+t->size<=4*MB)) {
			cout<<"Merging free memory block at address " << t->startAddress << " with free memory block at address " << (t->next)->startAddress<<endl;
			t->size=t->size+(t->next)->size;
			t->next=(t->next)->next;

		}
		else
			t=t->next; //next in list
	}

}

