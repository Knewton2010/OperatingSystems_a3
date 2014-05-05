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

//#include "take_input.h"
#include "forking.h"

int main(int argc, char* argv[])
{
	time_length = 6;
	cout << time_length << endl;


	if (argc > 2){
		cout << "Too many arguements." << endl;
		std::cerr << "Usage: " << argv[0] << " Seconds" << endl;
		return 1;
	}

	if (argc == 2){

		istringstream ss(argv[1]);
		if (!(ss >> time_length)){
   			 cerr << "Improper Argument: " << argv[1] << '\n';
			 cout << "Usage: a3 seconds" << endl;
			 return 1;
		}
	}

	/*if (argc > 2){
		cout << "Too many arguements." << endl;
		std::cerr << "Usage: " << argv[0] << " Seconds" << endl;
		return 1;
	}

	if (argc == 2){
		time_length = atoi(argv[1]);
		cout << time_length << endl;
	}
	*/
	//take_input();
	forking();

	cout << "***************" << endl;
	cout << "Program complete!" << endl;

}

