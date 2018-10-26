/*
Assignment #3 - Question #1
Date Due: Nov. 5th, 2018
By: Jason Han & Kevin Jee

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

typedef struct my_args{
  int length;
  char **array;
};

void *findAvg(void *args);
void *findMin(void *args);
void *findMax(void *args);

int main(int ac, char *av[])
{
  pthread_t tid1 = 1;
  pthread_t tid2 = 2;
  pthread_t tid3 = 3;

  struct my_args args1;
  args1.length = ac;
  args1.array = av;

  pthread_create(&tid1, NULL, findAvg, &args1);
  pthread_create(&tid2, NULL, findMin, &args1);
  pthread_create(&tid3, NULL, findMax, &args1);
  pthread_join (tid1, NULL);
  pthread_join (tid2, NULL);
  pthread_join (tid3, NULL);

  return 1;
}

void *findAvg(void *args)
{
  struct my_args* thing = args;
  int length = thing->length;
  char **av = thing->array;
  double avg = 0.0;

  int n = 1;

  for(n = 1; n < length; n++)
    {
      avg += atoi(av[n]);
    }
  avg = avg/(length-1);

  printf("The average of the integers recieved is: %.2f.\n",avg);
}

void *findMin(void *args)
{
  struct my_args* thing = args;
  int length = thing->length;
  char **av = thing->array;

  int min = atoi(av[1]);
  int n = 0;

  for(n = 1; n < length; n++)
    {
      int temp = atoi(av[n]);
      if (temp < min)
        {
          min = temp;
        }
    }
  printf("The minimum of the integers recieved is: %d.\n",min);
}

void *findMax(void *args)
{
  struct my_args* thing = args;
  int length = thing->length;
  char **av = thing->array;

  int max = atoi(av[1]);
  int n = 0;

  for(n = 1; n < length; n++)
    {
      int temp = atoi(av[n]);
      if (temp > max)
        {
          max = temp;
        }
    }
  printf("The maximum of the integers recieved is: %d.\n",max);
}
