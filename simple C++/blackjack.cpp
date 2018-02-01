#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int askRange(string question, int min, int max);
char askYesOrNo(string name, string question);

class Card{
	private:
		char m_suite;
		int m_rank;
		bool m_faceUp;
	
	public:
		Card(int rank, char suite, bool faceUp=true);
		int getValue() const;
		void flip();
		bool isFaceUp();
		friend ostream& operator<<(ostream &os, const Card &card);
};

Card::Card(int rank, char suite, bool faceUp): m_suite(suite), m_rank(rank), m_faceUp(faceUp){}

int Card::getValue() const{
	if(m_rank <= 10)
		return m_rank;
	else
		return 10;
}

void Card::flip(){
	m_faceUp = !m_faceUp;
}

bool Card::isFaceUp(){
	return m_faceUp;
}

ostream& operator<<(ostream &os, const Card &card){
	const string kind[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	if(card.m_faceUp){
		os << kind[card.m_rank-1] << card.m_suite;
	}
	else{
		os << "XX";
	}
	return os;
}

class Hand{
	private:
		vector<Card> m_cards;
		int m_total;
		
	public:
		Hand(int spaces=2);
		void addCard(Card card);
		int getTotal() const;
		void flip(int cardno=0);
		friend ostream& operator<<(ostream &os, const Hand &hand);
};

Hand::Hand(int spaces){
	m_total = 0;
	m_cards.reserve(spaces);
}

void Hand::addCard(Card card){
	m_cards.push_back(card);
	m_total += card.getValue();
}

int Hand::getTotal() const{
	return m_total;
}

void Hand::flip(int cardno){
	m_cards[cardno].flip();
}

ostream& operator<<(ostream &os, const Hand &hand){
	for(vector<Card>::const_iterator iter=hand.m_cards.begin(); iter!=hand.m_cards.end(); *iter++){
		os << *iter << '\t';
	}
	os << "(" << hand.getTotal() << ")\n";
	return os;
}

class Deck{
	private: 
		vector<Card> m_cards;
		int randRange(int high, int low=0){
			return rand()%high + low;
		}
	
	public:
		Deck();
		void populate();
		void shuffle();
		void deal(Hand &hand);
		Card getCard();
};

Deck::Deck(){
	m_cards.reserve(52);
}
void Deck::populate(){
	char suites[] = {'c', 's', 'd', 'h'};
	for(int i=1; i<=13; i++){
		for(int j=0; j<4; j++){
			Card temp_card(i, suites[j]);
			m_cards.push_back(temp_card);
		}
	}
}

void Deck::shuffle(){
	//shuffle m_cards
	int len = m_cards.size();
	for(int i=0; i<len; i++){
		int index1 = randRange(len);
		int index2 = randRange(len);
		
		Card temp = m_cards[index1];
		m_cards[index1] = m_cards[index2];
		m_cards[index2] = temp;
	}
}
void Deck::deal(Hand &hand){
	hand.addCard(getCard());
	hand.addCard(getCard());
}

Card Deck::getCard(){
	Card temp_card = m_cards.back();
	m_cards.pop_back();
	return temp_card;
}

class GPlayer{
	protected:
		Hand m_hand;
		string m_name;
		bool m_busted;
		
	public:
		GPlayer(string name, bool busted=false);
		virtual void playNext(Deck& deck)=0;
		Hand& getHand();
		bool isBusted();
		friend ostream& operator<<(ostream &os, const GPlayer &player);	
};

GPlayer::GPlayer(string name, bool busted): m_name(name), m_busted(busted){}

Hand& GPlayer::getHand(){
	return m_hand;
}

bool GPlayer::isBusted(){
	return m_busted;
}

ostream& operator<<(ostream &os, const GPlayer &player){
	os << player.m_name << ":\t" << player.m_hand << endl;
	return os;
}

class Player:public GPlayer{
	public:
		Player(string name);
		virtual void playNext(Deck& deck);
		void announce(string status);
};

Player::Player(string name): GPlayer(name){}
void Player::playNext(Deck& deck){
	char response = askYesOrNo(m_name, "Do you want a hit(y/n): ");
	while(response == 'y'){
		m_hand.addCard(deck.getCard());
		cout << *this;
		if(m_hand.getTotal() > 21){
			cout << m_name << " busts\n";
			m_busted = true;
			break;
		}
		response = askYesOrNo(m_name, "Do you want a hit(y/n): ");
	}
}

void Player::announce(string status){
	cout << m_name << " " << status << endl;
}

class House: public GPlayer{
	public:
		House();
		virtual void playNext(Deck& deck);
};

House::House(): GPlayer("House"){}
void House::playNext(Deck& deck){
	cout << "House is playing now!!\n";
	m_hand.flip();
	while(m_hand.getTotal() < 16){
		m_hand.addCard(deck.getCard());
		cout << *this;
	}
	if(m_hand.getTotal() > 21){
		cout << "House busts\n";
		m_busted = true;
	}
}

class Game{
	private:
		int m_numplayers;
		Deck m_deck;
		vector<Player> m_players;
		House m_house;	
	
	public:
		Game(int numplayers);
		void setup();
		void play();
		void announceWinners();
};

Game::Game(int numplayers): m_numplayers(numplayers){
	m_players.reserve(numplayers);
}

void Game::setup(){
	m_deck.populate();
	m_deck.shuffle();
	
	for(int i=0; i<m_numplayers; i++){
		string pname;
		cout << "Enter Player name " << i+1 << ": ";
		cin >> pname;
		Player p(pname);
		m_players.push_back(p);
	}
	
	for(vector<Player>::iterator iter=m_players.begin(); iter!=m_players.end(); *iter++){
		m_deck.deal(iter->getHand());
		cout << *iter;
	}
	m_deck.deal(m_house.getHand());
	m_house.getHand().flip();
	cout << m_house;
}

void Game::play(){
	for(vector<Player>::iterator iter=m_players.begin(); iter!=m_players.end(); *iter++){
		iter->playNext(m_deck);
	}
	m_house.playNext(m_deck);
}

void Game::announceWinners(){
	cout<<"Winners:\n";
	if(m_house.isBusted()){
		//all players not busted win
		for(vector<Player>::iterator iter=m_players.begin(); iter!=m_players.end(); *iter++){
			if(!iter->isBusted()){
				iter->announce("wins");
			}
			else{
				iter->announce("loses");
			}
		}
	}
	else{
		//If the player’s total is greater than the house’s, he wins
		//If the two totals are the same, the player ties the house
		for(vector<Player>::iterator iter=m_players.begin(); iter!=m_players.end(); *iter++){
			if(!iter->isBusted() && iter->getHand().getTotal() > m_house.getHand().getTotal()){
				iter->announce("wins");
			}
			else if(!iter->isBusted() && iter->getHand().getTotal() == m_house.getHand().getTotal()){
				iter->announce("pushes");
			}
			else{
				iter->announce("loses");
			}
		}
	}
}

int main(){
	srand(static_cast<unsigned int>(time(0)));
	
	int num_players = askRange("Enter number of players(2-7) : ", 2, 7);
		
	Game game(num_players);
	game.setup();
	game.play();
	game.announceWinners();
}

char askYesOrNo(string name, string question){
	char response;
	cout << name << ", " << question;
	cin >> response;
	while(response != 'y' && response != 'n'){
		cout << "Please enter 'y' or 'n'" << endl;
		cout << question;
		cin >> response;
	}
	return response;
}

int askRange(string question, int min, int max){
	int num;
	cout << question;
	cin >> num;
	while(num < min || num > max){
		cout << "Please enter the number within the range " << min << " and " << max << endl;
		cout << question;
		cin >> num;
	}
	return num;
}
