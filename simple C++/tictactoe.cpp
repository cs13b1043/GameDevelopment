#include <iostream>
#include <vector>
#include <algorithm>

const char EMPTY = ' ';
const char X = 'X';
const char O = 'O';
const char TIE = 'T';
const char NO_ONE = 'N';

using namespace std;

void instructions();
char humanPiece();
char opponentPiece(char piece);
char askYesOrNo(string question);
int askNumber(string question, int number);
void displayBoard(vector<char> &board);
char winner(vector<char> &board);
inline bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void displayWinner(char winner, char computer, char human);


int main(){
	//game setup
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);
	
	instructions();
	char human = humanPiece();
	char computer = opponentPiece(human);
	
	char turn = X;
	displayBoard(board);
	int move;
	
	//game loop
	while(winner(board)==NO_ONE){
		if(turn==human){
			move = humanMove(board, human);
		}
		else{
			move = computerMove(board, computer);
			cout << "Ok! I shall take square " << move << endl;
		}
		board[move] = turn;
		displayBoard(board);
		turn = turn==X ? O : X;
	}
	
	//exit
	displayWinner(winner(board), computer, human);
	return 0;
}

void instructions(){
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "--where human brain is pit against silicon processor\n\n";
	cout << "Make your move known by entering a number, 0 - 8. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	cout << " 0 | 1 | 2\n";
	cout << "------------\n";
	cout << " 3 | 4 | 5\n";
	cout << "------------\n";
	cout << " 6 | 7 | 8\n";
	cout << "------------\n";
	cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}

char humanPiece(){
	char first = askYesOrNo("Do you want the first move(y/n) ");
	if(first=='y'){
		cout << "\nThen take the first move. You will need it.\n";
		return X;
	}
	else{
		cout << "\nYour bravery will be your undoing. . . I will go first.\n";
		return O;
	}
}

char askYesOrNo(string question){
	char response;
	cout << question;
	cin >> response;
	while(response != 'y' && response != 'n'){
		cout << "Please enter 'y' or 'n'" << endl;
		cout << question;
		cin >> response;
	}
	return response;
}

int askNumber(string question, int number){
	int response;
	cout << question;
	cin >> response;
	while(response < 0 && response > number){
		cout << "Please enter the number in range 0 - " << number << endl;
		cout << question;
		cin >> response;
	}
	return response;
}

char opponentPiece(char piece){
	return piece==X ? O : X;
}

void displayBoard(vector<char> &board){
	cout << endl;
	cout <<  board[0] << " | " << board[1] << " | " << board[2] << endl;
	cout << "------------\n";
	cout <<  board[3] << " | " << board[4] << " | " << board[5] << endl;
	cout << "------------\n";
	cout <<  board[6] << " | " << board[7] << " | " << board[8] << endl;
	cout << "------------\n";
}

char winner(vector<char> &board){
	const int WINNING_ROWS[8][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
	const int TOTAL_ROWS = 8;
	
	// all possible winning rows
	for(int i=0; i<TOTAL_ROWS; i++){
		if(board[WINNING_ROWS[i][0]] != EMPTY && 
			board[WINNING_ROWS[i][0]]==board[WINNING_ROWS[i][1]] && 
			board[WINNING_ROWS[i][1]]==board[WINNING_ROWS[i][2]]){
				return board[WINNING_ROWS[i][0]];
			}
	}
	//tie - no empty
	if(count(board.begin(), board.end(), EMPTY)==0){
		return TIE;
	}
	
	return NO_ONE;
}

inline bool isLegal(const vector<char>& board, int move){
	return board[move]==EMPTY;
}

int humanMove(const vector<char>& board, char human){
	int move = askNumber("Where will you move?", board.size()-1);
	while(!isLegal(board, move)){
		cout << "\nThat square is already occupied, foolish human.\n";
		move = askNumber("Where will you move?", board.size()-1);
	}
	cout << "Fine...\n";
	return move;
}

int computerMove(vector<char> board, char computer){
	// see if computer can win
	for(unsigned int move=0; move<board.size(); move++){
		if(isLegal(board, move)){
			board[move] = computer;
			if(winner(board)==computer){
				board[move] = EMPTY;
				return move;
			}
			board[move] = EMPTY;
		}
	}
	
	// stop if human can win
	char human = opponentPiece(computer);
	
	for(unsigned int move=0; move<board.size(); move++){
		if(isLegal(board, move)){
			board[move] = human;
			if(winner(board)==human){
				board[move] = EMPTY;
				return move;
			}
			board[move] = EMPTY;
		}
	}
	
	// best possible move
	const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
	
	for(unsigned int i=0; i<board.size(); i++){
		int move = BEST_MOVES[i];
		if(isLegal(board, move)){
			return move;
		}
	}
	return -1;
}

void displayWinner(char winner, char computer, char human){
	if (winner == computer)
	{
		cout << winner << "’s won!\n";
		cout << "As I predicted, human, I am triumphant once more -- proof\n";
		cout << "that computers are superior to humans in all regards.\n";
	}
	else if (winner == human)
	{
		cout << winner << "’s won!\n";
		cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
		cout << "But never again! I, the computer, so swear it!\n";
	}
	else
	{
		cout << "It’s a tie.\n";
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		cout << "Celebrate. . . for this is the best you will ever achieve.\n";
	}
}
