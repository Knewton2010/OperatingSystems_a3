/*
Kyle Newton
CS570, Spring 2014
Assignment #3, Countdown Timer
a3.cc */

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

#include "forking.h"

int main(int argc, char* argv[])
{
	//Default time_length
	time_length = 6;

	/*
	Error checking for arguements:
		Only 1 arguement defaults to 6 seconds
		Two arguements has error checking to make sure
			that the 2nd arguement is valid
		Three or more arguements throws an error and
			provides the proper format
	*/
	if (argc > 2){
		cout << "Too many arguements." << endl;
		std::cerr << "Usage: " << argv[0] << " Seconds" << endl;
		return 1;
	}

	if (argc == 2){

		istringstream ss(argv[1]);
		if (!(ss >> time_length)){
   			 cerr << "Improper Argument: " << argv[1] << '\n';
			 cout << "Usage: " << argv[0] << " seconds" << endl;
			 return 1;
		}
	}

	forking();

	cout << "***************" << endl;
	cout << "Program complete!" << endl;

}

