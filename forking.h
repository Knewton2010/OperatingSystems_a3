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
int minutes;
int seconds;

/*
Converts the value of time_length from seconds to minutes and seconds
adding 0's when numbers are under 10 to keep consistency
*/
void calc_time(){

	minutes = (time_length / 60) % 60;
	seconds = time_length % 60;
	//time_length--;

	if (minutes < 10)
		cout << "0" << minutes << ":";
	else
		cout << minutes << ":";

	if (seconds < 10)
		cout << "0" << seconds << endl;
	else
		cout << seconds << endl;
}

/*
output a converted time_length, wait one second
then subtract 1 from the input for the next pass
*/
void out_time_left(){

	calc_time();
	sleep(1);
	--time_length;
}

/*
Output the local time
*/
void output_clock(){

	time_t rawtime;
	struct tm * timeinfo;
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		printf("%s", asctime(timeinfo));
}
/*
A pipe is created, and then the parent is forked giving inheritance to
the child.  The parent then forks again, passing on the pipe again.
Each child continues to do their job.
*/
void forking(){
	int mypipefd[2];
	int ret;
	char buf;
	string done = "NotDoneYet";
	ret = pipe(mypipefd);

	if (fork()){

		//parent
		if (fork()){
			//cout << "I'm the parent" << endl;
			//printf("I'm pID %d\n",getpid());

			/*
			wait until both children are closed before continuing
			*/
			waitpid(-1, &status, 0);
			cout << "Children successfully closed." << endl;
		}

		/*
		child 2 calls out_time_length in order to get the time left
		from the input, and then signals child 1 to do its job.
		*/
		else{
			/*
			Child 2 doesn't read, it just writes to inform child 1 to continue
			*/
			close(mypipefd[0]);

			//cout << "I'm the second child" << endl;
			//printf("I'm pID %d\n",getpid());
			//cout << time_length << endl;

			do {
				write(mypipefd[1], &done, 2);
				out_time_left();
			} while (time_length > 0);

			cout << "00:00" << endl;

			close(mypipefd[1]);

			exit(3);
		}
	}

	/*
	child 1 waits for child 2 to signal it, and then runs output_clock
	Then it gets signaled when child 2 closes, and also closes.
	*/
	else{

		//cout << "I'm the first child" << endl;
		//printf("I'm pID %d\n",getpid());

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
