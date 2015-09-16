#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_FORKS 4

int binomialCoefficient(int n, int k) {

	int factN;
	int factK;
	int factNK;

	int denom;

	factN = factorial(n);
	factK = factorial(k);
	factNK = factorial(n-k);
	
	denom = factK * factNK;

	return factN/denom;
}

int factorial(int n) {

	int product = 1;
	int i;

	for (i = n; i > 0; i--) {
		product = product * i;
	}
	return product;
}

int main() {

	pid_t pid;
	int status;
	int fork_count;

	int count = 0;
	int i;

	int fork1_pid;
	int fork2_pid;
	int fork3_pid;
	int fork4_pid;

	const char * cat_file = "ls";
	char * const cat_args [] = {"ls -l", NULL};

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
			fork1_pid = getpid();
			printf("%d - (n(n-2)) binomial coefficient computations of integers n=2, 3, 10, start now! \n", getpid());
			exit(0);
		}

		else if (fork_count == 2) {
			fork2_pid = getpid();
			sleep(3);

			for (i = 2; i <= 10; i+=2) {
				printf("%d binomailcoef of %d is %d \n", fork_count, i, binomialCoefficient(i, i-2));
				sleep(4);
			}
			sleep(4);
			exit(0);
		}
	
		else if (fork_count == 3) {
			fork3_pid = getpid();
			sleep(5);

			for (i = 3; i < 10; i+=2) {
				printf("%d binomailcoef of %d is %d \n", fork_count, i, binomialCoefficient(i, i-2));
				sleep(4);
			}
			exit(0);
		}

		else if (fork_count == 4) {
			fork4_pid = getpid();
			sleep(30);
			execvp(cat_file, cat_args);
			exit(0);
		}
}


	else { //Parent
		printf("I am the parent, my pid is %d\n.", getpid());
		
/*
		waitpid(fork1_pid, &status, 0);
		printf("my child %d with fork %d has terminated. \n", 1, fork1_pid);

		waitpid(fork2_pid, &status, 0);
		printf("my child %d with fork %d has terminated. \n", 2, fork2_pid);

		waitpid(fork3_pid, &status, 0);
		printf("my child %d with fork %d has terminated. \n", 3, fork3_pid);

		waitpid(fork4_pid, &status, 0);
		printf("my child %d with fork %d has terminated. \n", 4, fork4_pid);
		*/
		
		for (fork_count = 1; fork_count <= NUM_FORKS; fork_count++) {
			pid = wait(&status);
			printf("my child %d with fork %d has terminated! \n", pid, fork_count);
		}
		
	}

}
		
