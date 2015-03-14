/*
This program solves the problem of finding the nearest house to a specified train station. We define houses by 
their x and y coordinates then compare those coordinates to a set that represents a train station in parallel. 
*/

#include <omp.h>
#include <stdio.h>
#include <windows.h> 
#include <time.h>
#include <math.h>


//The train station will never move so we can define it's coordinates here 
#define trainX 0
#define trainY 0

//structure that will hold the house data
struct PrimTask{
	int houseX,houseY;
};
//pointer to a house, each thread will have it's own cursor which it will use to look though the house array
PrimTask* cursor;
#pragma omp threadprivate(cursor)



//Prototypes
double distance(PrimTask * task);
double square(double valToSquare);

int main() {

	//Constants
	const int NUMTASKS = 40000000;	
	static const int T = 8; 

	//Clock vars
	clock_t start;
	clock_t end;


	//Arrays we will use in the program
	double* mins = new double[T];
	double * distances = new double[NUMTASKS]; 
	PrimTask* taskArray = new PrimTask[NUMTASKS]; 


	//Shared variables which will hold global minimums
	int minIndex;
	double minVal = MAXINT; 
	
	//Set up omp and rand
	omp_set_num_threads(T);
	srand(time(NULL));



	//Build the house objects	
	#pragma omp parallel for  	
	for(int i = 0; i <  NUMTASKS;i++)
	{
		cursor = &taskArray[i];
		cursor->houseX = (rand()%10000) + 1;
		cursor->houseY = (rand()%10000) + 1;

	}

	//We start the timer here after the houses have been randomly assigned
	start = clock();

	//We get a pointer to a house object then pass that pointer to the distance calculator which we then set as the value in 
	//the distance array in the same index as the house. This way we preserve the index of the house. 
	#pragma omp parallel for 
	for(int i = 0; i <  NUMTASKS;i++)
	{	
		cursor = &taskArray[i];
		distances[i] = distance(cursor);
	
	}


	//We use a distributed method to look through the distances and find a global minimum, if we find a value thats 
	//lower than our global minimum we set the global minimum and min index to the new values
	#pragma omp parallel for 
	for(int i = 0; i <  NUMTASKS;i++)
	{
		if(distances[i] < minVal)
		{
		#pragma omp critical
			{
				//If a thread was paused waiting to run we check again to make sure the global min hasn't already been reduced
				//to something smaller than the distance we are trying to input
			if(distances[i] < minVal){
			minVal = distances[i];
			minIndex = i;
			}
			}
		}
	}


	//End time measurement for critical section
	end = clock();

	printf("The program took %d miliseconds \n", end-start);
	printf("The smallest distance is %f at index %d \n", minVal, minIndex);

	//Pause the program so you can read the output
	const char* pause = " ";
	scanf(pause);
	return -1;
}

double square(double valToSquare)
{
	return valToSquare * valToSquare;
}

double distance(PrimTask * task)
{
	return  sqrt((square(task->houseX - trainX) + square(task->houseY - trainY)));
}

