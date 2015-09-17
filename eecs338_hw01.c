#define _XOPEN_SOURCE

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

time_t time_wrapper() {
	
	time_t val = time(NULL);
	if (val == ((time_t) -1)) {
		perror("time_wrapper");
		exit(errno);
	}
	else {
		return val;
	}	
}

char* cuserid_wrapper() {
	char* val = cuserid(NULL);
	if (val == NULL) {
		perror("cuserid");
		exit(errno);
	}
	else {
		return val;
	}
}

void getrusage_wrapper(struct rusage* output) {
	int val = getrusage(RUSAGE_SELF, output);
	if (val == -1) {
		perror("getrusage_wrapper");
		exit(errno);
	}
}

void print_uids_gids(const char* proc_name) {
	
	printf("[%s] username: %s\n", proc_name, cuserid_wrapper());

	//no error check necessary. syscalls always succeed.
	printf("[%s] user id: %d\n", proc_name, getuid());
	printf("[%s] effective user id: %d\n", proc_name, geteuid());
	printf("[%s] group id: %d\n", proc_name, getgid());
	printf("[%s] efffective group id: %d\n", proc_name, getegid());
	printf("[%s] pid: %d\n", proc_name, getpid());
}

void print_exec_times(const char* proc_name) {

	const int constant = 1<<30;
	int k = 0;
	int i;

	//accumulate some CPU time
	for (i = 0; i < constant; i++) {
		k++;
	}
	
	time_t cur_time;
	struct rusage res_usage;

	cur_time = time_wrapper();
	getrusage_wrapper(&res_usage);

	printf("[%s] seconds since epoch: %d\n", proc_name, (int)cur_time);
	printf("[%s] current time is %s", proc_name, ctime(&cur_time));
	printf("[%s] user CPU time: %d us\n", proc_name, (int)res_usage.ru_utime.tv_usec);
	printf("[%s] system CPU time: %d us\n", proc_name, (int)res_usage.ru_stime.tv_usec);

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

char* get_proc_name(const char* base, char* buff) {
	sprintf(buff, "%s, PID=%d", base, (int) getpid());
	return (char*) buff;
}

int main() {

	pid_t pid;
	pid_t ppid;
	int status;
	int fork_count;
	int i;

	char parent_proc_name[255];
	get_proc_name("parent", parent_proc_name);
	print_uids_gids(parent_proc_name);

	char proc_name1[255];
	char proc_name2[255];
	char proc_name3[255];
	char proc_name4[255];

	const char * cat_file = "ls";
	char * const cat_args [] = {"ls", "-l", NULL};

	for (fork_count = 1; fork_count <= NUM_FORKS; fork_count++) {
		
		pid = print_if_error(fork());

		if (pid > 0) {//Parent process

		}
		else if (pid == 0) { //Child process

			switch(fork_count) {
				case 1:
					get_proc_name("child 1", proc_name1);
				case 2:
					get_proc_name("child 2", proc_name2);
				case 3:
					get_proc_name("child 3", proc_name3);
				case 4:
					get_proc_name("child 4", proc_name4);
				default:
					break;
			}

			break;
		}
	}


	if (pid == 0) { //Child

		if (fork_count == 1) {

			sleep(9);

			print_uids_gids(proc_name1);
			printf("[child %d, PID=%d] parent PID: %d. \n", fork_count, getpid(), getppid());


			pid = getpid();
			check_id_error(pid);

			printf("[child %d, PID=%d] The process id %d (fork#%d) announce that (n(n-2)) binomial coefficient computations of integers n=2, 3, 10, start now! \n", fork_count, pid, pid, fork_count);

			print_exec_times(proc_name1);
			exit(0);
		}

		else if (fork_count == 2) {

			sleep(7);

			print_uids_gids(proc_name2);
			printf("[child %d, PID=%d] parent PID: %d. \n", fork_count, getpid(), getppid());
			
			pid = getpid();
			check_id_error(pid);

			sleep(5);

			for (i = 2; i <= 10; i+=2) {
				printf("[child %d, PID=%d] The process id %d (fork#%d) produced the binomial coefficient %d for integer %d. \n",fork_count, pid, pid, fork_count, binomialCoefficient(i, i-2), i);
				sleep(4);
			}

			print_exec_times(proc_name2);
			exit(0);
		}
	
		else if (fork_count == 3) {
			
			sleep(5);

			print_uids_gids(proc_name3);
			printf("[child %d, PID=%d] parent PID: %d. \n", fork_count, getpid(), getppid());

			sleep(5);

			pid = getpid();
			check_id_error(pid);

			sleep(5);

			for (i = 3; i < 10; i+=2) {
				printf("[child %d, PID=%d] The process id %d (fork#%d) produced the binomial coefficient %d for integer %d. \n", fork_count, pid, pid, fork_count, binomialCoefficient(i, i-2), i);
				sleep(4);
			}
			sleep(4);

			print_exec_times(proc_name3);
			exit(0);
		}

		else if (fork_count == 4) {

			print_uids_gids(proc_name4);
			printf("[child %d, PID=%d] parent PID: %d. \n", fork_count, getpid(), getppid());

			sleep(50);

			print_exec_times(proc_name4);
			execvp(cat_file, cat_args);

			exit(0);
		}
	}


	else { //Parent

		
		ppid = getpid();
		check_id_error(ppid);	

		pid = wait(&status);
		check_id_error(pid);
		printf("[parent, PID=%d] process %d exited with status %d \n", ppid, pid, WEXITSTATUS(status));

		pid = wait(&status);
		check_id_error(pid);
		printf("[parent, PID=%d] process %d exited with status %d \n", ppid, pid, WEXITSTATUS(status));

		pid = wait(&status);
		check_id_error(pid);
		printf("[parent, PID=%d] process %d exited with status %d \n", ppid, pid, WEXITSTATUS(status));

		pid = wait(&status);
		check_id_error(pid);
		printf("[parent, PID=%d] process %d exited with status %d \n", ppid, pid, WEXITSTATUS(status));
	
		print_exec_times(parent_proc_name);
	}

}
		
