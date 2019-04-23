#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<iomanip>

using namespace std;

string cardName[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
int cardScore[] = {11,2,3,4,5,6,7,8,9,10,10,10,10};
string itemName[] = {"2 - 4 Draw","5 - 7 Draw","8 - 10 Draw","Rival Draw","Change to 24 win","Steal 1 Card","Destroy Rival Card","Double Damage","Half Damage","Take no Damage","Damage Heal","Destory my Card"};
int winScore = 21;

class CardPlayer{
	string name;
	int hp;
	int hpmax;
	bool ai;
	vector<int> hand;
	vector<int> itemHand;
	public :
		CardPlayer(string,bool);
		void startGame(bool [],bool []);
		void endGame();
		void drawCard(bool [],bool []);
		void getCard(bool []);
		void getItem(bool []);
		void damage(int);
		void clearHand();
		string showName();
		int showHP();
		void showHand();
		void showItem();
		int showScore();
		void useItem(CardPlayer,int,int);
};

CardPlayer::CardPlayer(string text,bool bot){
	name = text;
	ai = bot;
	hp = hpmax = 1000;
}

void CardPlayer::useItem(CardPlayer you,int bet,int command){
	switch (command){
		case 0 :{
			
			break;
		}
		case 1 :{
			
			break;
		}
		case 2 :{
			
			break;
		}
		case 3 :{
			
			break;
		}
		case 4 :{
			
			break;
		}
		case 5 :{
			
			break;
		}
		case 6 :{
			
			break;
		}
		case 7 :{
			
			break;
		}
		case 8 :{
			
			break;
		}
		case 9 :{
			
			break;
		}
		case 10 :{
			
			break;
		}
		case 11 :{
			
			break;
		}
	}
}

string CardPlayer::showName(){
	return name;
}

int CardPlayer::showHP(){
	return hp;
}

void CardPlayer::startGame(bool deck[],bool item[]){
	for (int i = 0;i < 2;i++){
		drawCard(deck,item);
	}
}

void CardPlayer::drawCard(bool deck[],bool item[]){
	int get;
	getCard(deck);
	if (rand()%10 >= 5) getItem(item);
}

void CardPlayer::getCard(bool deck[]){
	int draw;
	do {
		draw = rand()%13;
	}while(deck[draw] == true);
	hand.push_back(draw);
	deck[draw] = true;
}

void CardPlayer::getItem(bool item[]){
	int get;
	do{
		get = rand()%12;
	}while(item[get] == true);
	itemHand.push_back(get);
}

void CardPlayer::showHand(){
	int i = 0;
	if (ai){
		cout << "? ";
		i = 1;
	}
	for (int j = i;j < hand.size();j++){
		cout << cardName[hand[j]] << " ";
	}
	cout << "\n";
}

void CardPlayer::showItem(){
	int i = 0;
	if (ai) i = itemHand.size();
	for (int j = i;j < itemHand.size();j++){
		cout << "[" << j+1 << "] : " << itemName[itemHand[j]] << "\n";
	}
}

void CardPlayer::damage(int bet){
	hp -= bet;
}

int CardPlayer::showScore(){
	bool haveA = false;
	int sum = 0;
	for (int i = 0;i < hand.size();i++){
		if (cardScore[hand[i]] == 11) haveA = true;
		sum += cardScore[hand[i]];
	}
	if (sum > winScore && haveA){
		sum -= 10;
	}
	return sum;
}

void CardPlayer::clearHand(){
	hand.clear();
}

void playTurn(CardPlayer &me,CardPlayer &you,bool deck[],bool item[],bool &pEnd,int &bet){
	int command;
	cout << me.showName() << " Turn\n" << " [1] to DRAW\n [2] to STAND\n [3] to USE ITEM\n >> ";
	cin >> command;
	switch (command) {
		case 1 : {
			me.drawCard(deck,item);
			int score = me.showScore();
			if (score > winScore){
				pEnd = false;
			}
			break;
		}
		case 2 : {
			cout << "Stand!!.\n";
			pEnd = false;
			break;
		}
		case 3 : {
			int get;
			cout << "Select item >> ";
			cin >> get;
			me.useItem(you,bet,get);
			pEnd = false;
			break;
		}
	}
	cout << "End Turn.\n";
	cout << me.showName() << "'s Current Hand >> ";
	me.showHand();
}

void botTurn(CardPlayer &me,CardPlayer &you,bool deck[],bool item[],bool &rEnd,int &bet){
	int command;
	cout << me.showName() << " Turn\n" << " [1] to DRAW\n [2] to STAND\n [3] to USE ITEM\n >> ";
	cin >> command;
	switch (command) {
		case 1 : {
			me.drawCard(deck,item);
			int score = me.showScore();
			if (score > winScore){
				rEnd = false;
			}
			break;
		}
		case 2 : {
			cout << "Stand!!.\n";
			rEnd = false;
			break;
		}
		case 3 : {
			int get;
			cout << "Select item >> ";
			cin >> get;
			me.useItem(you,bet,get);
			rEnd = false;
			break;
		}
	}
	cout << "End Turn.\n";
	cout << me.showName() << "'s Current Hand >> ";
	me.showHand();
}

void resetDeck(bool deck[]){
	for (int i = 0;i < 13;i++){
		deck[i] = false;
	}
}

void hpBar(CardPlayer p){
	string name = p.showName();
	cout << name << setw(10 - name.length());
	for (int i = 0;i < (p.showHP()/10);i++){
		cout << "|";
	}
}

void roundPlay(CardPlayer &p,CardPlayer &r,bool deck[],bool item[],int round,int &bet){
	bool pEnd = true;
	bool rEnd = true;
	int result;
	resetDeck(deck);
	p.startGame(deck,item);
	r.startGame(deck,item);
	cout << "*--------------------Round" << setw(3) << round;
	cout << "--------------------*\n";
	cout << r.showName() << "'s HP = " << r.showHP() << "Points\n";
	cout << r.showName() << "'s Hand >> ";r.showHand();
	cout << p.showName() << "'s HP = " << p.showHP() << "Points\n";
	cout << p.showName() << "'s Hand >> ";p.showHand();
	cout << p.showName() << "'s Item >> \n";p.showItem();
	do{
		if (pEnd) playTurn(p,r,deck,item,pEnd,bet);
		if (rEnd) botTurn(r,p,deck,item,rEnd,bet);
	}while(pEnd || rEnd);
	int pScore = p.showScore();
	int rScore = r.showScore();
	if ((pScore > winScore && rScore > winScore) || pScore == rScore){
		p.damage(bet);
		r.damage(bet);
		cout << "*----------------------DRAW----------------------*\n";
	}else if (pScore > winScore){
		p.damage(bet);
		cout << "*----------------------LOSE----------------------*\n";
	}else if (rScore > winScore){
		r.damage(bet);
		cout << "*----------------------WIN!----------------------*\n";
	}else if (pScore > rScore){
		r.damage(bet);
		cout << "*----------------------WIN!----------------------*\n";
	}else if (rScore > pScore){
		p.damage(bet);
		cout << "*----------------------LOSE----------------------*\n";
	}
	p.clearHand();
	r.clearHand();
	winScore = 21;	
}

bool gamePlay(void){
	bool cardDeck[13] = {};
	bool cardItem[12] = {};
	string s;
	cout << "Enter your name >> ";
	cin >> s;
	CardPlayer p(s,false);
	CardPlayer r("Azael",false);
	int i = 1,php,rhp,bet = 50;
	do{
		roundPlay(p,r,cardDeck,cardItem,i,bet);
		php = p.showHP();
		rhp = r.showHP();
		bet+=50;
		i++;
	}while(php > 0 && rhp > 0);
	if (php <= 0) return false;
	else if (rhp <= 0) return true;
}

