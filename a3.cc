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

using namespace std;

#include "take_input.h"
#include "forking.h"



int main()
{
	take_input();
	forking();

	cout << "Program complete!" << endl;

}
