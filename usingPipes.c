/*Author: Michael Giancola
 *Date: 06/10/2019
 *Description: This file contains a program that accepts two integer values from the user as command line 
arguments and it will then create a parent and child process. The child and parent communicate through a pipe
and share values over it to acheive an end goal which is to calculate the sum of the two integer values.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char*argv[]){

	int x, y;
	int fd[2];								//this intializes the pipe
	pid_t pid, i, j;							//these are pid numbers that will be useful when outputting 
	int sum;								//this sum integer will hold the sum of the two inputted numbers
	
	if (argc != 3){								//this is a check to ensure the correct number of command line arguments were entered
		printf("\nIncorrect number of command line arguments!\n");
		exit(1);
	}	
	
	if (pipe(fd) < 0){							//this is a check to ensure the pipe is created correctly and if not the program ends
		perror("pipe error");
	    	exit(1);
  	}

	pid = fork();								//this forks the process creating a child along with the parent process

	if (pid < 0) {								//checks if there is an error when forking
    		perror("fork error");
    		exit(1);
 	}

	if (pid > 0){								//this block is what is executed during the parent process since the pid will be positive
		j = getpid();							//gets the parents pid number and sets it to pid_t j
		printf("\nA pipe is created for communication between parent (PID %d) and child\n", j);
		printf("\nparent (PID %d) created a child (PID %d)\n", j, pid);

		x = atoi(argv[1]);						//x will hold the first integer value (X) and atoi is a function which converts the string argument to an integer
		printf("\nparent (PID %d) Reading X = %d from the user\n", j, x);

		wait(NULL);							//function call makes this process wait until the child process is finished executing
		read (fd[0],&y, sizeof(y));					//once the child process is done, this reads in the integer value (Y) that was written to the pipe by the child process

		printf("\nparent (PID %d) Reading Y from the pipe (Y = %d)\n", j, y);
		sum = x + y;							//calculates the sum of the integer x and y and stores it in the sum variable
		printf("\nparent (PID %d) adding X + Y = %d\n", j, sum);	//outputs the sum
	}

	if (pid == 0){								//this block is what the child process executes since pid is 0 during this process
		j = getpid();
		y = atoi(argv[2]);						//will hold the second integer value (Y) and atoi function again converts the string argument to an integer

		printf("\nchild (PID %d) Reading Y = %d from the user\n", j, y);
		write(fd[1], &y, sizeof(y));					//this is when the child process writes integer Y into the pipe for the parent to eventually retrieve it
		printf("\nchild (PID %d) Writing Y into the pipe\n", j);
	}
}
