/*
Kyle Newton
CS570, Spring 2014
Assignment #3, Countdown Timer
take_input.h */

int time_length;

void take_input()
{
	//user input requested
	cout << "How long should the countdown timer be?" << endl;
	//cin >> time_length;

	while (true)
	{
		cin >> time_length;

		if ((cin) && (time_length >= 0) && (time_length <= 60))
			break;

		cin.clear();
		cin.ignore( 1000, '\n' );
		cout << "Try again: " << flush;
	}

cout << "you entered: " << time_length << endl;
}
