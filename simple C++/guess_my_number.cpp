#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
	// setup - generate a random number
	cout << "\tWelcome to Guess My Number!!!" << endl;
	
	srand(static_cast<unsigned int>(time(0)));
	const int NUMBER = rand() % 100 + 1;
	
	int tries = 0;
	int guess;
	
	// gameloop - take input from user till guess is correct
	do{
		cout << "Enter your guess: " ;
		cin >> guess;
		tries++;
		
		if(guess < NUMBER){
			cout << "Your guess is too low!" << endl;
		}
		else if(guess > NUMBER){
			cout << "Your guess is too high!" << endl;
		}		
	}while(guess!=NUMBER);
	
	// exit - output message and number of guesses
	cout << "Congrats! You guessed the number in " << tries << " trials" << endl;
}
