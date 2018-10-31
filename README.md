# OS - A3

Operating Systems Design and Systems Programming

Assignment #3 - SYST 44288

XGit bash was used to push the code to this repository.

## Question 1

Write a multithreaded program that calculates various statistical values 
for a list of numbers. This program will be passed a series of numbers 
on the command line and will then create three separate worker threads.
One thread will determine the average of the numbers, the second will 
determine the maximum value, and the third will determine the minimum 
value. For example, suppose your program is passed the integers

  90 81 78 95 79 72 85

The program will report:
- The average value is 82
- The minimum value is 72
- The maximum value is 95

The variables representing the average, minimum, and maximum values will 
be stored globally. The worker threads will set these values, and the 
parent thread will output the values once the workers have exited. (We 
could obviously expand this program by
creating additional threads that determine other statistical values, 
such as median and standard deviation.)

Apply appropriate error handling.

## Question 2
Assignment 2, Question 1, involved designing an echo server using the 
Java threading API. This server is single-threaded, meaning that the 
server cannot respond to concurrent echo clients until the current 
client exits. Modify your solution to Assignment 2, Question 1, so that 
the echo server services each client in a separate request.

Apply appropriate error handling, see the General Notes Section below.

Input sanitizing - While it is always recommended to sanitize input, the 
fact that this program will compile and execute any code it is sent over 
the Internet basically makes it impossible to secure properly. Just do 
basic sanitizing and don’t worry too much.
