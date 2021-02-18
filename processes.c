/*Author: Michael Giancola
 *Date: 05/10/2019
 *Description: This program creates multiple parent and child processes and 
 prints out the specific PID number for each process. The third child created
 in this program will then call an external program.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	pid_t pid_one, pid_two, pid_three, i, j;//creating pid variables
	pid_one = fork();//first fork which creates a child process

	if (pid_one <  0){//if the pid is negative then the fork was unsuccessful
		printf("fork unsuccessful");
		exit(1);
	}

	if (pid_one > 0){ //this is what the parent process will execute since pid_one during the parent process if the fork is successful
		
		j = getpid();//j will be equal the current process's pid which will be the parent process's
		printf("\nparent process (PID %d) created child_1 (PID %d)\n", j, pid_one);
		printf("\nparent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", j, pid_one);

		wait(NULL);//this wait puts the parent process on hold and executes the child process for pid_one and will then return to the next line

		pid_three = fork();//once returned from the child process, this parent process creates a second child process 

		if (pid_three < 0){//unsuccessful fork check
        	        printf("fork unsuccessful");
                	exit(1);
        	}

       		if (pid_three > 0){//this is what the parent process of pid_three will execute
			j = getpid();
		 	printf("\nparent (PID %d) created child_2 (PID %d)\n", j, pid_three);//pid_three will be the pid number of the child process here
			wait(NULL);//this waits for the child process to execute (external program) and then comes back and completes this parent process
		 }

       		 if (pid_three == 0){//this is the child process for pid_three since pid_three is 0 during the child process
                	j = getpid();
                	printf("\nchild_2 (PID %d) is calling an external program external_program.out and leaving child_2...\n", j);
			printf("\n");

			execl("external_program.out", NULL);//this function will execute the external_program.out program and then this program will end
       		 }
	}	

	if (pid_one == 0){//this is what the child process will execute of pid_one since pid_one will be 0 during the child process

		pid_two = fork();//this child creates another child called child_1.1    
	
		if (pid_two < 0){//this checks for unsuccessful fork
        	        printf("fork unsuccessful");
                	exit(1);
        	}	

       		if (pid_two > 0){ //this is child_1 as a parent process for child_1.1  child_1.1 does not do anything in our case so no other block is needed
			j = getpid();//getpid will retrieve child_1's pid since it is acting as the parent process in this case
			printf("\nchild_1 (PID %d) created child_1.1 (PID %d)\n", j, pid_two);//this prints the child_1 pid and the child_1.1 pid
        	        printf("\nchild_1 (PID %d) is now completed\n", j);
        	}
	}	
}
