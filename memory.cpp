/********************************************************************
Progammer: Saad Rasheed

Purpose:   This assignment uses either best fit or first fit memory
management scheme provided by the user to simulate how the management
schemes work. We read in data from a text file and manage those processes.
*********************************************************************/
#include "memory.h"
#include "block.h"

int deallocate(string s1,string s2); //Prototype

Block* InUse=0; // initializing to be empty
Block* Avail=0; // will initialize to 1,2,2,4,4 MB 

int main(int argc,char* argv[]) {
	int i;
	int c = 0;
	string carg;

if (argc!=2) {//Checking if right number of command line arguments have been entered while executing the program
  	cout << "ERROR: ./memory: INCORRECT NUMBER OF ARGUMENTS!" << endl; //making sure correct args
  	return -1;
	}

	carg = argv[1];
	if (carg == "F"){ //First fit algorithm 
        cout << "You chose to run the First-Fit algorithm for Memory Management!" << endl << endl;
	}
	else if(carg == "B") { //Best fit algorithm
        cout << "You chose to run the Best-Fit algorithm for Memory Management!" << endl << endl;
	}
	else { //crash if wrong argument given
	cout << "Incorrect argument given" << endl;
	return -1;
	}


cout << "Beginning the Simulation Run now." << endl << endl;

Avail=(Block*) new Block();
Avail->size=1*MB; //1MB initialization
Avail->startAddress=3*MB; //assuming it starts at 3MB
Avail->next=0;
Block* t=Avail;

for(i = 0; i < 2; i++) { //Initializing 2 of 2MB
	t->next=(Block*) new Block();
	(t->next)->size=2*MB;
	(t->next)->startAddress=t->startAddress + t->size;
	t=t->next;
	}

for(i = 0; i < 2;i++) { //Initializing 2 of 4MB
	t->next=(Block*) new Block();
        (t->next)->size=4*MB;
        (t->next)->startAddress=t->startAddress + t->size;
        t=t->next;
	}

t->next=0;
ifstream In;
int k;
string trans,s1,s2,z;
In.open("data.txt");

if(In == NULL) {
	cout<<"File not found"<<endl;
	exit(-1);
	}

	In >> trans;
while (trans != "?") { //Loop until question mark in data file
	if(trans=="L"||trans=="A") {
			In>>s1; //Process
			In>>k; //Size
			In>>z; //Block ID
			cout<<endl<<"Transaction: Request to load process " << s1 << ", Block ID " << z
			<< " using" << endl << k << " bytes of memory" << endl;
			if((t=Avail->search(k,argv[1]))!=0) {
		cout << endl << "Sufficient Memmory Block Found! Size: " << t->size << endl;
				Block* b= new Block();
				b->size=k;
				b->Pid=s1;
				In>>b->Bid;
				t->size=t->size-k;// Decrease the block found on Avail by that amount
				b->startAddress=t->startAddress;
				t->startAddress=t->startAddress+k;
				if(t->size==0) {// If the block on Avail is now of size 0,Delete it
					Avail->deleteB(t);
				}

				b->next=InUse;
				InUse=b;
				cout << "Allocating Memory to Block Succesful!" << endl << endl;
			}
			else
				cout << endl << "ERROR: FAILED SEARCH FOR AVAILABLE BLOCK: BLOCK NOT FOUND!" << endl;
		}
		else if(trans=="D") {

			In>>s1;
			In>>s2;
			cout<< endl << "Transacrion:Deallocation of Process of PID" << s1 << " " << "BID:" << s2 << endl;
			if(deallocate(s1,s2)==1)//if deallcation successfull print success message
				cout<<"Succesfull deallocation"<<endl;
			Avail->accom();

		}
		else if(trans=="T") {
			In>>s1;
			cout << "Transaction: Request to Terminate process: " << s1 << endl;
			int m=0;
			t=InUse;
			while(t!=0) {//loop to weed out the blocks that are allocated to Process to be terminated
				if(t->Pid==s1) {
					m=1;
					s2=t->Bid;
					if(deallocate(s1,s2)==1)
						cout << "Block" << s2 << "of Process ID:" << s1 <<" succesfull deallocated" << endl;
					Avail->accom();
					t=InUse;
				}
				else
					t=t->next;
			}
			if(m==1)
				cout << endl << "Process ID :" << s1 << " Terminated" << endl;
			else
				cout << endl << "Process ID :" << s1 << "Could not be located" << endl;

		}
		 if((c++)%HOW_OFTEN==0) {
                        cout << "List of available blocks" << endl;
                        Avail->print();
                        cout << endl;
                        cout << "List of blocks currently in use" << endl << endl;
        		InUse->print(); 
	       }

		In>>trans;
         }
        In.close();
	cout << endl << "The run has ended" << endl << endl;
	cout << "The Blocks of memory available are follows" << endl << endl;
        Avail->print();
        cout << endl;
        cout << "The Blocks of memory in use are as follows" << endl << "(NONE)";
        cout << endl << "Total size of the list = 0" << endl;

	return 0;
}
/***************************************************************
Function: deleteB

Use:      This is used to delete the block of data that was created
(the object)
Arguments: 1. the block pointer (Block*)

Returns:   nothing
***************************************************************/
void Block::deleteB(Block* s) {

        Block* t=this;
        if(t==s) {
                Avail=this->next; //next in list
        }
        else {
                 while(t->next!=s) {
                        t=t->next;
                 }
                 t->next=(t->next)->next;
        }
        delete s; //deleting block
}
/***************************************************************
Function: deallocate

Use:      This is used to deallocate the data
Arguments: 1. string 1
			2. string 2

Returns:   integer (0 for fail 1 for success)
***************************************************************/
int deallocate(string s1,string s2) {
	Block* t=InUse;
	if(t->next==0 && t->Pid==s1 && t->Bid==s2) { 
		Block* p=t; 
		p->Pid="";
		p->Bid="";
		t=0;
		InUse=0;
		if(Avail->startAddress>p->startAddress) {
                        p->next=Avail; //move to avail list
                        Avail=p;
                }
		  else {
			t=Avail;
                        while(!((t->next)->startAddress>p->startAddress && (t->startAddress<p->startAddress))) {
                                t=t->next;
                                if(t->next==0)
                                        break;
                        }
                                p->next=t->next;
                                t->next=p;
               }

		return 1;
	}

	if(t->Pid==s1 && t->Bid==s2) {
		Block* p =t; //first block deallocation
		p->Pid="";
		p->Bid="";
		InUse=InUse->next;
		 if(Avail->startAddress>p->startAddress) {
                        p->next=Avail; //move to avail list
                        Avail=p;
                }
                  else {
                        t=Avail; //set to available
                        while(!((t->next)->startAddress>p->startAddress && (t->startAddress<p->startAddress))) {
                                t=t->next; //next in list
                                if(t->next==0)
                                        break;
                        }
                                p->next=t->next; 
                                t->next=p;
               }

                return 1;

	}

        while(!((t->next)->Pid==s1 && (t->next)->Bid==s2)) {
		t=t->next;
		if(t->next==0) //searching 
			break; //break
	}
	if(t->next==0) {
		cout<<"ERROR: Could not deallocate block"<<endl; //print error message
		return 0;
	}

                Block* p1=t->next;
                t->next=(t->next)->next;
		p1->Pid=""; //clear
		p1->Bid=""; //clear
                if(Avail->startAddress>p1->startAddress) {
                	p1->next=Avail; //next in list
                        Avail=p1;
                }
                else {
                        t=Avail;
                        while(!((t->next)->startAddress>p1->startAddress && (t->startAddress<p1->startAddress))) {
                        	t=t->next;
                                if(t->next==0)
                                	break;
                        }
                                p1->next=t->next;
                                t->next=p1;
               }
	return 1;
}

