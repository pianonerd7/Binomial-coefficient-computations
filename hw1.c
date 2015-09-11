#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_FORKS 4

int binomialCoefficient(int n, int k) {

	int factN;
	int factK;
	int factNK;

	int denom;
	int quotient;

	factN = factorial(n);
	factK = factorial(k);
	factNK = factorial(n-k);
	
	denom = factK * factNK;
	quotient = factN/denom;

	return quotient;
}

int factorial(int n) {

	if (n == 0) {
		return 1;
	}

	int product = 1;
	int i;

	for (i = n; i > 0; i--) {
		product = product * i;
	}
	return product;
}

int main() {
	int i;

	//for (i = 2; i < 10; i++) {
		printf("binomailcoef of %d is %d \n", 10, binomialCoefficient(10, 8));
		//printf("factorial of %d is %d \n", 10, factorial(10));
	//}


/*
	pid_t pid;
	int status;
	int fork_count;

	int count = 0;
	int i;

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
			sleep(3);
			for(i = count; i < 10; i+=2) {
			printf("%d\n", i);
			sleep(4);
			}
		}
	
		else if (fork_count == 3) {
	
			sleep(5);
			for(i = count+1; i < 10; i+=2) {
				printf("%d\n", i);
				sleep(4);
			}
		}

		else if (fork_count == 4) {
			sleep(15);
		}
}


	else { //Parent
		printf("I am the parent, my pid is %d\n.", getpid());

		for (fork_count = 0; fork_count < NUM_FORKS; fork_count++) {
			pid = wait(&status);
			printf("my child %d with fork %d has terminated! \n", pid, fork_count);
		}
	}
*/
}
		
