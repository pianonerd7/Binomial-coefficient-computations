#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>


#define NUM_FORKS 4

int print_if_error(int syscall) {
	
	if (syscall < 0) {
		perror("fork");
		exit(errno);
	}
	else {
		return syscall;
	}
}

void check_id_error(int id) {

	if (id < 0) {
		perror("id error");
		exit(errno);
	}
}


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
	pid_t ppid;
	int status;
	int fork_count;
	int i;

	const char * cat_file = "ls";
	char * const cat_args [] = {"ls -l", NULL};

	for (fork_count = 1; fork_count <= NUM_FORKS; fork_count++) {
		
		pid = print_if_error(fork());

		if (pid > 0) {//Parent process
			
		}
		else if (pid == 0) { //Child process
			break;
		}
	}


	if (pid == 0) { //Child

		pid = getpid();
		ppid = getppid();

		printf("I am child #%d and my pid is %d. My parent is %d. \n", fork_count, pid, ppid);

		if (fork_count == 1) {

			pid = getpid();
			check_id_error(pid);

			printf("%d - (n(n-2)) binomial coefficient computations of integers n=2, 3, 10, start now! \n", pid);
			exit(0);
		}

		else if (fork_count == 2) {

			sleep(3);
			
			pid = getpid();
			check_id_error(pid);

			for (i = 2; i <= 10; i+=2) {
				printf("The process id %d (fork#%d) produced the binomial coefficient %d for integer %d. \n", pid, fork_count, binomialCoefficient(i, i-2), i);
				sleep(4);
			}
			exit(0);
		}
	
		else if (fork_count == 3) {

			sleep(5);

			pid = getpid();
			check_id_error(pid);

			for (i = 3; i < 10; i+=2) {
				printf("The process id %d (fork#%d) produced the binomial coefficient %d for integer %d. \n", pid, fork_count, binomialCoefficient(i, i-2), i);
				sleep(4);
			}
			exit(0);
		}

		else if (fork_count == 4) {

			sleep(30);
			execvp(cat_file, cat_args);
			exit(0);
		}
	}


	else { //Parent
		pid = getpid();
		check_id_error(pid);
		printf("I am the parent, my pid is %d\n.", pid);

		pid = wait(&status);
		check_id_error(pid);
		printf("process %d exited with status %d \n", pid, WEXITSTATUS(status));

		pid = wait(&status);
		check_id_error(pid);
		printf("process %d exited with status %d \n", pid, WEXITSTATUS(status));

		pid = wait(&status);
		check_id_error(pid);
		printf("process %d exited with status %d \n", pid, WEXITSTATUS(status));

		pid = wait(&status);
		check_id_error(pid);
		printf("process %d exited with status %d \n", pid, WEXITSTATUS(status));
	
	}

}
		
