/*
Assignment #3 - Question #1
Date Due: Nov. 5th, 2018
By: Jason Han & Keun Young Jee

Description:
Write a multithreaded program that calculates various statistical values for a list of
numbers. This program will be passed a series of numbers on the command line and will
then create three separate worker threads.

One thread will determine the average of the numbers, the second will determine the
maximum value, and the third will determine the minimum value. For example, suppose
your program is passed the integers

90 81 78 95 79 72 85

The program will report:

The average value is 82
The minimum value is 72
The maximum value is 95

The variables representing the average, minimum, and maximum values will be stored
globally. The worker threads will set these values, and the parent thread will output the
values once the workers have exited. (We could obviously expand this program by
creating additional threads that determine other statistical values, such as median and
standard deviation.)

References:

https://www.geeksforgeeks.org/multithreading-c-2/
https://stackoverflow.com/questions/16320354/passing-pointer-char-argument-to-function-in-thread
https://stackoverflow.com/questions/1352749/multiple-arguments-to-function-called-by-pthread-create
https://stackoverflow.com/questions/36050901/how-to-pass-command-line-arguments-to-thread-function
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Struct that is used to hold the data required to perform calculations
//Contains the number of arguments given on the command line and
//a pointer to those arguments
typedef struct my_args{
  int length;
  char **array;
};

//Global variables
double avg;
int min;
int max;

//Function prototypes
void *findAvg(void *args);
void *findMin(void *args);
void *findMax(void *args);

int main(int ac, char *av[])
{
	//Initialize thread id values	
	pthread_t tid1 = 1;
	pthread_t tid2 = 2;
	pthread_t tid3 = 3;
	
	//Create our struct and pass values to the struct
	struct my_args args1; 
	args1.length = ac;
	args1.array = av;
	
	//Create our threads and start them
	pthread_create(&tid1, NULL, findAvg, &args1);	
	pthread_create(&tid2, NULL, findMin, &args1);
	pthread_create(&tid3, NULL, findMax, &args1);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	
	//Now print out the results in our global variables
	printf("The average of the integers recieved is: %.2f.\n",avg);
	
	printf("The minimum of the integers recieved is: %d.\n",min);
	
	printf("The maximum of the integers recieved is: %d.\n",max);

  return 1;
}

// Function finds the average between the given values
void *findAvg(void *args)
{
	//After obtaining the data from the struct,
	//loop through the values, calculating the average at
	//the end.
	
	//Convert the void pointer to a struct pointer of our struct
  	struct my_args* thing = args;
	//Grab the length and save to a local variable
	int length = thing->length;
	//Grab the array pointer and save to a local variable
	char **av = thing->array;
	avg = 0.0;
	
	//Loop through values here:
	int n = 1;
	
	for(n = 1; n < length; n++)
	{
	    avg += atoi(av[n]);
	}
	avg = avg/(length-1);

}

// Function finds the minimum value between the given values
void *findMin(void *args)
{

	//Comments here are pretty much the same as the ones
	//for findAvg
  	struct my_args* thing = args;
  	int length = thing->length;
  	char **av = thing->array;
  	min = atoi(av[1]);
  	int n = 0;

  	for(n = 1; n < length; n++)
    {
      	int temp = atoi(av[n]);
      	if (temp < min)
        {
          min = temp;
        }
    }
}

void *findMax(void *args)
{
	//Comments here are pretty much the same as the ones
	//for findAvg
  	struct my_args* thing = args;
  	int length = thing->length;
  	char **av = thing->array;
	
  	max = atoi(av[1]);
  	int n = 0;
	
  	for(n = 1; n < length; n++)
    {
      	int temp = atoi(av[n]);
      	if (temp > max)
        {
          	max = temp;
        }
    }
}
