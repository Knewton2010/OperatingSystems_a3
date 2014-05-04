
#include <time.h>

int status;

void out_time_left(){
	cout << time_length-- << endl;
	sleep(1);
}

void output_clock(){

	time_t rawtime;
	struct tm * timeinfo;
	do {
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		printf("%s", asctime(timeinfo));
	sleep(1);
	} while (time_length-- >0);
}
#include <time.h>

int status;

void out_time_left(){
	cout << time_length-- << endl;
	sleep(1);
}

void output_clock(){

	time_t rawtime;
	struct tm * timeinfo;
	do {
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		printf("%s", asctime(timeinfo));
	sleep(1);
	} while (time_length-- >0);
}


void forking(){

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
			cout << "I'm the second child" << endl;
			printf("I'm pID %d\n",getpid());
			
			do {
				out_time_left();
			} while (time_length > 0);
			
			exit(3);
		}
	}

	//child 1
	else{
		cout << "I'm the first child" << endl;
		printf("I'm pID %d\n",getpid());
		output_clock();
		
		exit (3);
		
	}
}
