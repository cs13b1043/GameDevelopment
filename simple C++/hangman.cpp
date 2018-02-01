#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>

using namespace std;

int randRange(int high, int low=0){
	return rand()%high + low;
}

int main(){
	srand(static_cast<unsigned int>(time(0)));
	
	//game setup
	const int MAX_GUESSES = 8;
	vector<string> WORDS;
	WORDS.push_back("HELPING");
	WORDS.push_back("HANGMAN");
	WORDS.push_back("PILLOW");
	WORDS.push_back("EXAMINATION");
	random_shuffle(WORDS.begin(), WORDS.end());
	
	const string THE_WORD = WORDS[0];
	
	string used_letters = "";
	string so_far(THE_WORD.size(), '-');

	char user_input;
	int num_guesses = 0;
	cout << "\tWelcome to Hangman!!!" << endl;
	
	//game loop
	while(so_far!=THE_WORD && MAX_GUESSES - num_guesses > 0 ){
		cout << "\nYou have " << MAX_GUESSES - num_guesses << " guesses left" << endl;
		cout << "You have used these letters: " << used_letters << endl;
		cout << "The word guess so far is: " << so_far << endl;
		
		cout << "\nEnter your guess: ";
		cin >> user_input;
		user_input = toupper(user_input);
		num_guesses++;
		
		//check if the input is already entered
		while(used_letters.find(user_input)!=string::npos){
			cout << "You've already guessed " << user_input << endl;
			cout << "Enter your guess: ";
			cin >> user_input;
			user_input = toupper(user_input);
		}
		
		used_letters += user_input;
		
		//search for user input in the word
		if(THE_WORD.find(user_input)!=string::npos){
			cout << "\nThat's right! " << user_input << " is in the word." << endl;
			
			//update so_far
			for(unsigned int i=0; i<THE_WORD.length(); i++){
				if(THE_WORD[i]==user_input){
					so_far[i] = user_input;
				}
			}
		}
		else{
			cout << "\nSorry! " << user_input << " is not in the word." << endl;
		}
	}
	
	//exit
	if(so_far == THE_WORD){
		cout << "Congrats! You guessed in " << num_guesses << " guesses" << endl;
	}
	else{
		cout << "You've been hanged. The correct word is " << THE_WORD << endl;
	}
}
