#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

int randRange(int high, int low=0){
	return rand()%high + low;
}

string jumble(string input){
	int len = input.length();
	for(int i=0; i<len; i++){
		int index1 = randRange(len);
		int index2 = randRange(len);
		
		char temp = input[index1];
		input[index1] = input[index2];
		input[index2] = temp;
	}
	return input;
}

int main(){
	srand(static_cast<unsigned int>(time(0)));
	
	// setup - generate a random number
	cout << "\tWelcome to Word Jumble!!!" << endl;
	cout << "Unscramble the letters to make a word" << endl;
	cout << "Type 'hint' to get a hint" << endl;
	cout << "Type 'quit' to end the game" << endl;
	
	const int NUM_WORDS = 5;
	enum fields{WORD, HINT, NUM_FIELDS};
	const string WORDS[NUM_WORDS][NUM_FIELDS] = {
		{"wall", "Do you feel you’re banging your head against something?"},
		{"glasses", "These might help you see the answer."},
		{"labored", "Going slowly, is it?"},
		{"persistent", "Keep at it."},
		{"jumble", "It’s what the game is all about."}};
	
	// select a word
	int choice = randRange(NUM_WORDS);
	string theWord = WORDS[choice][WORD];
	string theHint = WORDS[choice][HINT];
	
	// jumble the word
	string jumbled = jumble(theWord);
	cout << "The jumbled word: " << jumbled << endl;
	
	string user_input = "";
	int score = 100;
	
	// gameloop - take input from user till guess is correct
	do{
		cout << "Enter: " ;
		cin >> user_input;
		
		if(user_input == "hint"){
			cout << theHint << endl;
			score -= 20;
		}
		else if(user_input != theWord){
			cout << "Sorry, that's not it!" << endl;
			score -= 5;
		}
		else{	
			break;
		}
		
	}while(user_input != "quit");
	
	// exit - output score
	if(user_input == theWord){
		cout << "That's it! You made it.." << endl;
		cout << "Your score is " << score << endl;
	}
	
	cout << "Thanks for playing!" << endl;
}
