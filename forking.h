int status;

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
		}
	}

	//child 1
	else{
		cout << "I'm the first child" << endl;
		printf("I'm pID %d\n",getpid());
	}
}
