/**
 *Programmer: Adam Page 
 *
 *Class: CSCI480
 *
 *Date Due 9/26/2020
 *Assignment: 2
 *practice system calls such as fork(), pipe()
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	setbuf(stdout, NULL);
	char write_msg[BUFFER_SIZE] = "Go do some chores...";
	char read_msg[BUFFER_SIZE];
	pid_t pidChild1, pidChild2;
	//pipe_a where pipe_a[0] for read end and pipe_a[1] for write end.
	int pipe_a[2];
	//pipe_b where pipe_b[0] for read end and pipe_b[1] for write end.
	int pipe_b[2];
	//create the pipe
	if (pipe(pipe_a) == -1)
	{
		fprintf(stderr, "Pipe_a failed");
		return 1;
	}
	if (pipe(pipe_b) == -1)
	{
		fprintf(stderr, "Pipe_b failed");
		return 1;
	}
	// now fork a child process 
	//Creates child of the initial process.
	pidChild1 = fork();
	//The process above executes this line along with the main process,
	//thus creating it's own child and becomes intermediate process and initial process creates
	//second child
	pidChild2 = fork();

	if (pidChild1 < 0)
	{
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pidChild1 > 0 && pidChild2 > 0)
	{  
		// parent process 
		// close the unused read end of the pipe 
		close(pipe_a[READ_END]);
		//display message
		printf("\nParent: My PID is %d, my parent's PID is %d. My children are %d, %d.  I write to pipe A: %s. \n", getpid(), getppid(), pidChild1, pidChild2, write_msg);

		char command[100];
		// Create the ps command 
		sprintf(command, "ps -f --ppid %d,%d,%d,%d", getppid(), getpid(), pidChild1, pidChild2);

		//Invoke the command
		system(command);

		// write to the pipe 
		write(pipe_a[WRITE_END], write_msg, strlen(write_msg));

		// close the write end of the pipe 
		close(pipe_a[WRITE_END]);

		// Wait untill all children finish execution 
		while (waitpid(pidChild1, NULL, 0) > 0 || waitpid(pidChild2, NULL, 0) > 0);
		printf("\nParent: Child processes finished their work. ");
	}
	else if (pidChild1 == 0 && pidChild2 > 0)
	{   
		// Intermediate Parent 
		// close the unused read end of the pipe 
		close(pipe_b[READ_END]);

		printf("\nIntermediate Parent: My PID is %d, my parent's PID is %d. My child is %d. I write to pipe B: %s.\n", getpid(), getppid(), pidChild2, write_msg);

		// write into the pipe 
		write(pipe_b[WRITE_END], write_msg, strlen(write_msg));

		// close the write end of the pipe 
		close(pipe_b[WRITE_END]);
		//Sleep for 3 seconds.
		sleep(3);
		printf("\nIntermediate Process: %d is awake", getpid());
	}
	else if (pidChild1 > 0 && pidChild2 == 0)
	{
		// Child Process 
		// close the unused end of the pipe 
		close(pipe_a[WRITE_END]);

		// read from the pipe 
		read(pipe_a[READ_END], read_msg, BUFFER_SIZE);

		printf("\nChild: My PID is %d, my parent's PID is %d. I read from pipe A: %s.\n", getpid(), getppid(), read_msg);

		// close the read end of the pipe 
		close(pipe_a[READ_END]);
		//Sleep for 3 seconds.
		sleep(3);
		printf("\nChild: %d is awake", getpid());
	}
	else
	{
		// Child Process 
		// close the unused end of the pipe 
		close(pipe_b[WRITE_END]);

		// read from the pipe 
		read(pipe_b[READ_END], read_msg, BUFFER_SIZE);

		printf("\nChild: My PID is %d, my parent's PID is %d. I read from pipe A: %s.\n", getpid(), getppid(), read_msg);

		// close the read end of the pipe 
		close(pipe_b[READ_END]);
		//Sleep for 3 seconds.
		sleep(3);
		printf("\nChild: %d is awake", getpid());
	}

	return 0;
}

