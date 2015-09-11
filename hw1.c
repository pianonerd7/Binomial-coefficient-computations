#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_FORKS 4

int main() {

	pid_t pid;
	int status;
	int fork_count;

	for (fork_count = 1; fork_count <= NUM_FORKS; fork_count++) {
		pid = fork();

		if (pid > 0) {//Parent process
			
		}
		else if (pid == 0) { //Child process
			break;
		}
		else {
			perror("fork() failed \n");
			exit(EXIT_FAILURE);
		}
	}


	if (pid == 0) { //Child
		printf("I am child #%d and my pid is %d. My parent is %d. \n", fork_count, getpid(), getppid());
	


	if (fork_count == 1) {
		printf("%d - (n(n-2)) binomial coefficient computations of integers n=2, 3, 10, start now! \n", getpid());
		exit(0);
	}

	else if (fork_count == 2) {
		sleep(10);
	}
	
	else if (fork_count == 3) {
	
		sleep(10);
	}

	else if (fork_count == 4) {
		sleep(10);
	}
}


	else { //Parent
		printf("I am the parent, my pid is %d\n.", getpid());

		for (fork_count = 0; fork_count < NUM_FORKS; fork_count++) {
			pid = wait(&status);
			printf("my child %d has terminated! \n", pid);
		}
	}

}
		
