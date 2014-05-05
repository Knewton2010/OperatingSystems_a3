/*
Kyle Newton
CS570, Spring 2014
Assignment #3, Countdown Timer
forking.h */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string>

int status;
int time_length;

void out_time_left(){

	/*
	subtract 1 from the input
	*/
	sleep(1);
	cout << --time_length << endl;
}

/*
Child 1 will call output_clock in order to output the time, then wait
until child 2 has told it to go again via pipe
*/
void output_clock(){

	time_t rawtime;
	struct tm * timeinfo;
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		printf("%s", asctime(timeinfo));
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

			/*
			wait until both children are closed before continuing
			*/
			waitpid(-1, &status, 0);
			cout << "Children successfully closed." << endl;
		}

		//child 2
		else{
			/*
			Child 2 doesn't read, it just writes to inform child 1 to continue
			*/
			close(mypipefd[0]);

			cout << "I'm the second child" << endl;
			printf("I'm pID %d\n",getpid());

			cout << time_length << endl;
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

		/*
		Child 1 doesn't write, it just reads from child 2 to know to continue
		*/
		close(mypipefd[1]);

		/*
		While child 2 continues to feed child 1 through the pipe,
		child 1 will keep running output_clock
		*/
		while (read(mypipefd[0], &buf, 10)>0)
			output_clock();

		close(mypipefd[0]);

		exit(3);


	}
}
