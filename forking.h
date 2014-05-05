/*
Kyle Newton
CS570, Spring 2014
Assignment #3, Countdown Timer
take_input.h */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string>

int status;

void out_time_left(){
	cout << time_length-- << endl;
	sleep(1);
}

void output_clock(){

	time_t rawtime;
	struct tm * timeinfo;
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		printf("%s", asctime(timeinfo));
	sleep(1);
}

void forking(){
	int mypipefd[2];
	int ret;
	char buf;
	string done = "blargalarg";
	ret = pipe(mypipefd);
	
	if (fork()){

		//parent
		if (fork()){
			cout << "I'm the parent" << endl;
			printf("I'm pID %d\n",getpid());
			waitpid(-1, &status, 0);
			cout << "Children successfully closed." << endl;
		}

		//child 2
		else{
			close(mypipefd[0]);	/* Child 2 doesn't read */
				
			cout << "I'm the second child" << endl;
			printf("I'm pID %d\n",getpid());
			
			do {
				write(mypipefd[1], &done, 2);
				out_time_left();
			} while (time_length > 0);
			
			cout << "It's Killing TIME" << endl;
			
			close(mypipefd[1]);
			
			cout << "DEAD!" << endl;
			
			exit(3);
		}
	}

	//child 1
	else{

		cout << "I'm the first child" << endl;
		printf("I'm pID %d\n",getpid());
		close(mypipefd[1]);		/* Child 1 doesn't write */
		
		
		do {
			output_clock();
		
					
		} while (read(mypipefd[0], &buf, 10)>0);
		close(mypipefd[0]);

		exit(3);
		
		
	}
}
