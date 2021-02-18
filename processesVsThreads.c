/*Author: Michael Giancola
 *Date: 27/10/2019
 *Description: This file contains a program that will test data sharing ability of a thread and process.
 It uses global variables and data to show the difference between a thread and a process.
 **/

//included libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h> 

void *sum();								//function prototype

int x = 10;								//global variable delcarations
int y = 20;
int z = 0;

int main(){

	pid_t pid;
	pid = fork();							//creates a parent and child process

	if (pid < 0){							//unsuccessful fork check
		printf("fork unsuccessful");
		exit(1);
	}

	if (pid > 0){							//parent process will execute 
		wait(NULL);
		printf("\nThe value of z is: %d\n", z);			//prints the value of z which is 0 since processes dont share global data
		pthread_t thread_1;
		
		if(pthread_create(&thread_1, NULL, sum, NULL)){		//creates thread and calls sum() routine
			printf("Error while creating thread\n");	//error check for thread creation
			exit(1);
		}
		pthread_join(thread_1, NULL);				//indicates when thread is complete
		printf("\nThe value of z is: %d\n", z);			//prints z which is 30 because threads allow sharing of global data
	}

	if (pid == 0){							//child process will execute
		z = x + y;
	}
}

void *sum(){								//thread start routine function
	z = x + y;
}

