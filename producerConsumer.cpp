/********************************************************************
Progammer: Saad
Purpose:   producer consumer problem using sempahores and mutexes to illustrate
this provlem. we create threads, and wait for them to close while inserting items.
*********************************************************************/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define BUFFER_SIZE 12
#define P_NUMBER 6
#define C_NUMBER 4
#define N_P_STEPS 4
#define N_C_STEPS 6

using namespace std;
//initialization 
char buffer[BUFFER_SIZE];
char data[1];
char producers[6];
char consumers[4];
sem_t empty,full;
static pthread_mutex_t mtx;

int i = 0,j = 0;
int totalItems = 0;

void *producer(void *);
void *consumer(void *);
void insert_item(const char& item,int &i);
void remove_item(char& item,int &j);
pthread_t p_tids[6],c_tids[4];

int main(int argc, const char * argv[]) {
	//Initializing semaphors and mutexes
    memset(buffer, ' ', sizeof(buffer));
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full, 0,0);
    pthread_mutex_init(&mtx, NULL);
	//output for beginning
	cout << "Simulation of Producers and Consumers" << endl;
	cout << endl << "The semaphores and mutex have been initialized" << endl << endl;

	for (int i = 0; i < P_NUMBER; ++i) { //Creating 6 producer threads
        	pthread_create(&p_tids[i], NULL, producer, NULL);
	}
	for (int i = 0; i < C_NUMBER; ++i) { //Creating 4 consumer threads
        	pthread_create(&c_tids[i], NULL, consumer, NULL);
	}
	for (int i = 0; i < N_C_STEPS; ++i) { //waiting for consmer threads to close
        	pthread_join(p_tids[i], NULL);
	}
	for (int i = 0; i < N_P_STEPS; ++i) { //waiting for producer threads to close
        	pthread_join(c_tids[i], NULL);
	}
	cout << endl << "All the producer and consumer threads have been closed." 
	<< endl << endl << "The semaphores and mutex have been deleted." << endl;
return 0;
}

void *producer(void *) {
	int ctr = 0; //setting counter to 0
	while(true) {
		sem_wait(&empty);
        	pthread_mutex_lock(&mtx); //lock mutex
		sleep(1); //sleep one second
        	insert_item(data[random()%1],i); //insert item random data 
        	sem_post(&full);
        	pthread_mutex_unlock(&mtx);
        	++ctr; //increase counter
        if (ctr == 4)
            pthread_exit(0); //exit when producers full
    }
}

void *consumer(void *) {
	int ctr = 0;
	while(true) {
        	sem_wait(&full);
        	pthread_mutex_lock(&mtx); //lock mutex
        	sleep(1); //sleep one second
        	char taken;
        	remove_item(taken,j); //take random char
        	sem_post(&empty); 
        	pthread_mutex_unlock(&mtx);
        	++ctr; //increase counter 
        if (ctr == 6) //when consumer full
            pthread_exit(0);
    }
}


void insert_item(const char& item,int &i) {
int pID = 0;
//if (i > 6)
	i = (rand() % 6) + 1;

	pID = i;
	buffer[i] = item; //random item put in
	//i = (i+1) % BUFFER_SIZE;
	cout << "Producer "<< pID << " inserted one item.";
	totalItems++; //increase count of items 
	cout << "   Total is now " << totalItems; //output
	cout << endl;
}

void remove_item(char& item,int &j) {
int cID = 0;
//if (j > 4) 
	j = (rand() % 4) + 1;

	cID = j;
	item = buffer[j];
	buffer[j] = ' '; //empty space where item was
	//j = (j+1)%BUFFER_SIZE;
	cout << "Consumer " << cID << " removed one item.";
	totalItems--; //decrement count
	cout << "    Total is now " << totalItems; //output 
	cout << endl;
}
