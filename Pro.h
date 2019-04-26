#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<conio.h>
using namespace std;

string cardName[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
int cardScore[] = {1,2,3,4,5,6,7,8,9,10,10,10,10};
string itemName[] = {"2 - 4 Draw","5 - 7 Draw","8 - 10 Draw","Rival Draw","Change to 24 win","Steal 1 Card","Destroy Rival Card","Double Damage","Half Damage","Take no Damage","Damage Heal","Destory my Card"};
int winScore = 21;
bool healGet = false;

class CardPlayer{
	string name;
	int hp;
	int hpmax;
	public :
		bool ai;
		bool safe;
		vector<int> hand;
		vector<int> itemHand;
		CardPlayer(string,bool);
		void startGame(bool [],bool []);
		void endGame();
		void drawCard(bool [],bool []);
		void getCard(bool []);
		void getItem(bool []);
		void damage(CardPlayer &,int);
		void heal(int);
		void clearHand();
		string showName();
		int showHP();
		void showHand();
		void showItem();
		int showScore();
		void useItem(CardPlayer &,bool [],int &,int);
		void item1(bool []); //2 - 4 draw//
		void item2(bool []); //5 - 7 draw//
		void item3(bool []); //8 - 10 draw//
		void item4(CardPlayer &,bool []); //rival draw
		void item5(); //Change to 24 win// 
		void item6(CardPlayer &); //Steal 1 card//
		void item7(CardPlayer &,bool []); //Destroy rival card//
		void item8(int &); //Double Damage//
		void item9(int &); //Half Damage
		void item10(int &); //Take no damage
		void item11(); //Damage heal//
		void item12(bool []); //Destroy my card//
		void deleteItem(int,bool []);
		void hpBar();
};

CardPlayer::CardPlayer(string text,bool bot){
	name = text;
	ai = bot;
	hp = hpmax = 1000;
	safe = false;
}

void CardPlayer::item1(bool deck[]){
	bool found = false;
	for(int i = 1;i <= 3;i++){
		if(deck[i]==false) found = true;
	}
	if (found){
		int draw;
		do {
			draw = rand()%3+1;
		} while(deck[draw] == true);
		hand.push_back(draw);
		deck[draw] = true;
	} else {
		cout << " >> Card 2,3 and 4 aren't in the DECK!!\n";
	}
}

void CardPlayer::item2(bool deck[]){
	bool found = false;
	for(int i = 4;i <= 6;i++){
		if(deck[i]==false) found = true;
	}
	if (found){
		int draw;
		do {
			draw = rand()%3+4;
		} while(deck[draw] == true);
		hand.push_back(draw);
		deck[draw] = true;
	} else {
		cout << " >> Card 5,6 and 7 aren't in the DECK!!\n";
	}
}

void CardPlayer::item3(bool deck[]){
	bool found = false;
	for(int i = 7;i <= 12;i++){
		if(deck[i]==false) found = true;
	}
	if (found){
		int draw;
		do {
			draw = rand()%6+7;
		} while(deck[draw] == true);
		hand.push_back(draw);
		deck[draw] = true;
	} else {
		cout << " >> Card 8,9,10,J,Q,K aren't in the DECK!!\n";
	}
}

void CardPlayer::item4(CardPlayer &r,bool deck[]){
	cout << " >> Opponent Draw Card!!\n";
	r.getCard(deck);
}

void CardPlayer::item5(){
	cout << "Win Score change to 24\n";
	winScore = 24;
}

void CardPlayer::item6(CardPlayer &r){
	int choose;
	cout << "Choose card number >> ";
	cin >> choose;
	if (choose == 1) cout << "You can't steal first card\n";
	else {
		hand.push_back(r.hand[choose - 1]);
		r.hand.erase(r.hand.begin()+(choose - 1));
	}
}

void CardPlayer::item7(CardPlayer &r,bool deck[]){
	int choose;
	cout << "Choose card number >> ";
	cin >> choose;
	if (choose == 1) {
		cout << "You can't destroy first card\n";
	} else {
		for (int i = 0;i < 13;i++){
			if (deck[i] == r.hand[choose - 1]) deck[i] == false;
		}
		r.hand.erase(r.hand.begin() + (choose - 1));
		cout << "Azael selected card was destroy!\n";
	}
}

void CardPlayer::item8(int &bet){
	bet *= 2;
	cout << "This Round Damage * 2\n";
}

void CardPlayer::item9(int &bet){
	bet /= 2;
	cout << "This Round Damage / 2\n";
}

void CardPlayer::item10(int &bet){
	safe = true;
}

void CardPlayer::item11(){
	healGet = true;
	cout << "This Round Damge will heal winner\n";
}

void CardPlayer::item12(bool deck[]){
	int choose;
	cout << "Choose card number >> ";
	cin >> choose;
	for (int i = 0;i < 13;i++){
		if (deck[i] == hand[choose - 1]) deck[i] == false;
	}
	hand.erase(hand.begin() + (choose - 1));
	cout << "Your selected card was destroy!\n";
} 

void CardPlayer::useItem(CardPlayer &you,bool deck[],int &bet,int command){
	switch (command){
		case 0 :{
			item1(deck);
			break;
		}
		case 1 :{
			item2(deck);
			break;
		}
		case 2 :{
			item3(deck);
			break;
		}
		case 3 :{
			item4(you,deck);
			break;
		}
		case 4 :{
			item5();
			break;
		}
		case 5 :{
			item6(you);
			break;
		}
		case 6 :{
			item7(you,deck);
			break;
		}
		case 7 :{
			item8(bet);
			break;
		}
		case 8 :{
			item9(bet);
			break;
		}
		case 9 :{
			item10(bet);
			break;
		}
		case 10 :{
			item11();
			break;
		}
		case 11 :{
			item12(deck);
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
	if (rand()%10 >= 2) getItem(item);
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

void CardPlayer::heal(int bet){
	hp+=bet;
}

void CardPlayer::damage(CardPlayer &r,int bet){
	if (healGet) r.heal(bet);
	else if (!safe) hp-=bet;
}

int CardPlayer::showScore(){
	bool haveA = false;
	int sum = 0;
	for (int i = 0;i < hand.size();i++){
		if (cardScore[hand[i]] == 1) haveA = true;
		sum += cardScore[hand[i]];
	}
	if (sum <= winScore - 10 && haveA){
		sum += 10;
	}
	return sum;
}

void CardPlayer::clearHand(){
	hand.clear();
}

void playTurn(CardPlayer &me,CardPlayer &you,bool deck[],bool item[],bool &pEnd,int &bet){
	int command;
	do {
		cout << me.showName() << " Turn\n" << " [1] to DRAW\n [2] to STAND\n [3] to USE ITEM\n >> ";
		cin >> command;
		if (command < 1 || command > 3) cout << "Please Enter Again???\n";
	} while (command < 1 || command > 3);
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
			me.useItem(you,deck,bet,me.itemHand[get-1]);
			me.itemHand.erase(me.itemHand.begin()+get-1);
			//pEnd = false;
			break;
		}
	}
	cout << "End Turn.\n";
	cout << me.showName() << "'s Current Hand >> ";
	me.showHand();
}

void checkItem(CardPlayer me,bool list[]){
	for (int i = 0;i < 12;i++){
		for (int j = 0;j < me.itemHand.size();j++){
			if (me.itemHand[j] == i) list[i] = true; 
		}
	}
}

void CardPlayer::deleteItem(int num,bool list[]){
	list[num] = false;
	for (int j = 0;j < itemHand.size();j++){
		if (itemHand[j] == num) {
			itemHand.erase(itemHand.begin()+j);
		}
	}
}

void botTurn(CardPlayer &me,CardPlayer &you,bool deck[],bool item[],bool &rEnd,int &bet,int r){
	int score = me.showScore();
	bool godMode = false;
	int n = 6;
	for (int i = 0;i < 90;i++) cout << " ";
	cout << "Azael Turn\n";
	if (me.showHP() <= 500){
		n = 3;
		for (int i = 0;i < 90;i++) cout << " ";
		cout << "Azael Berserk Mode!!\n";
	}else if (me.showHP() <= 250){
		godMode = true;
		for (int i = 0;i < 90;i++) cout << " ";
		cout << "Azael God Mode!!!\n";
	}
	int i = rand()%n;
	bool found  = false;
		if (i == 0 || godMode == true){
			int dif = winScore - score;
			for (int i = 0;i < 13;i++){
				if (cardScore[i] == dif && deck[i] == false){
					me.hand.push_back(i);
					deck[i] = true;
					found = true;
					for (int i = 0;i < 90;i++) cout << " ";
					cout << "Azael Demonic Draw!!\n";
				}	
			}
		}else if (i == 1){
			int max = you.hand.size();
			int pos = rand()%max;
			you.hand.erase(you.hand.begin()+pos);
			for (int i = 0;i < 90;i++) cout << " ";
			cout << "Azael Burning Force!!\n";
			for (int i = 0;i < 13;i++){
				if (deck[i] == you.hand[pos]) deck[i] == false;
			}
		}else if (i == 2 && me.showHP() <= 800){
			me.safe = true;
			me.heal(200);
			for (int i = 0;i < 90;i++) cout << " ";
			cout << "Azael Cast Barrier!!\n";
		}
	if (score < 16){
		if (!found){
			me.drawCard(deck,item);
			score = me.showScore();
			for (int i = 0;i < 90;i++) cout << " ";
			cout << "Azael Draw!!\n";
		}
		if (score > winScore) rEnd = false;
	}else{
		for (int i = 0;i < 90;i++) cout << " ";
		cout << "Azael Stand!!\n";
		rEnd = false;
	}
}

void resetDeck(bool deck[]){
	for (int i = 0;i < 13;i++){
		deck[i] = false;
	}
}

void hpBar(CardPlayer p){
	string name = p.showName();
	int hp = p.showHP();
	cout << name << setw(10 - name.length());
	for (int i = 0;i < (p.showHP()/10);i++){
		cout << "|";
	}
	cout << setw(5) << hp << "\n\n";
}

void roundPlay(CardPlayer &p,CardPlayer &r,bool deck[],bool item[],int round,int &bet){
	bool pEnd = true;
	bool rEnd = true;
	r.ai = true;
	p.safe = false;
	r.safe = false;
	int result;
	healGet = false;
	resetDeck(deck);
	p.startGame(deck,item);
	r.startGame(deck,item);
	cout << "*----------------------------------------------------Round" << setw(3) << round;
	cout << "----------------------------------------------------*\n\n";
	cout << "*----------------------------------------------------BET" << setw(5) << bet;
	cout << "----------------------------------------------------*\n\n";
	hpBar(p);
	hpBar(r);
	do{
		cout << p.showName() << "'s Hand >> ";p.showHand();
		cout << p.showName() << "'s Item >> \n";p.showItem();
		for (int i = 0;i < 80;i++) cout << " ";
		cout << r.showName() << "'s Hand >> ";r.showHand();
		/*if (pEnd)*/ playTurn(p,r,deck,item,pEnd,bet);
		/*if (rEnd)*/ botTurn(r,p,deck,item,rEnd,bet,round);
	}while(pEnd || rEnd);
	cout << p.showName() << "'s Hand >> ";p.showHand();
	for (int i = 0;i < 80;i++) cout << " ";
	r.ai = false;
	cout << r.showName() << "'s Hand >> ";r.showHand();
	int pScore = p.showScore();
	int rScore = r.showScore();
	if ((pScore > winScore && rScore > winScore) || pScore == rScore){
		p.damage(r,bet);
		r.damage(p,bet);
		cout << "*------------------------------------------------------DRAW------------------------------------------------------*\n";
		cout << "Press any key to countinue....";
		getch();
	}else if (pScore > winScore){
		p.damage(r,bet);
		cout << "*------------------------------------------------------LOSE------------------------------------------------------*\n";
		cout << "Press any key to countinue....";
		getch();
	}else if (rScore > winScore){
		r.damage(p,bet);
		cout << "*------------------------------------------------------WIN!------------------------------------------------------*\n";
		cout << "Press any key to countinue....";
		getch();
	}else if (pScore > rScore){
		r.damage(p,bet);
		cout << "*------------------------------------------------------WIN!------------------------------------------------------*\n";
		cout << "Press any key to countinue....";
		getch();
	}else if (rScore > pScore){
		p.damage(r,bet);
		cout << "*------------------------------------------------------LOSE------------------------------------------------------*\n";
		cout << "Press any key to countinue....";
		getch();
	}
	p.clearHand();
	r.clearHand();
	winScore = 21;	
}

bool gamePlay(void){
	bool cardDeck[13] = {};
	bool cardItem[12] = {};
	string s;
	int keys;
	cout << "*----------------------------------------------------------------------------------------------------------------*\n";
	cout << "|                                            *** Effect Cards ***                                                |\n";
	cout << "*----------------------------------------------------------------------------------------------------------------*\n";
	cout << "| I.    2 - 4 Draw         ::  Your next draw card will be card that have score 2 to 4.                          |\n";
	cout << "| II.   5 - 7 Draw         ::  Your next draw card will be card that have score 5 to 7.                          |\n";
	cout << "| III.  8 - 10 Draw        ::  Your next draw card will be card that have score 8 to 10.                         |\n";
	cout << "| IV.   Rival Draw         ::  Make Your opponent draw 1 card.                                                   |\n";
	cout << "| V.    Change to 24 win   ::  Win point will change from 21 to 24.                                              |\n";
	cout << "| VI.   Steal 1 Card       ::  Steal 1 Card from your opponent's hand.                                           |\n";
	cout << "| VII.  Destroy Rival Card ::  Destroy 1 of your opponent card.                                                  |\n";
	cout << "| VIII. Double Damage      ::  Damage that the loser will take in this trun become double.                       |\n";
	cout << "| IX.   Half Damage        ::  Damage that the loser will take in this trun become half.                         |\n";
	cout << "| X.    Take no Damage     ::  This turn you will have no damage when you lose.                                  |\n";
	cout << "| XI.   Damage Heal        ::  This turn damage point will become heal point.                                    |\n";
	cout << "| XII.  Destory my Card    ::  Destroy 1 of your card.                                                           |\n";
	cout << "*----------------------------------------------------------------------------------------------------------------*\n";
	cout << "*                                              *** Azael Skills ***                                              *\n";
	cout << "*----------------------------------------------------------------------------------------------------------------*\n";
	cout << "| I.    Azael Demonic Draw :: If he can he will draw card that make him to win score.                            |\n";
	cout << "| II.   Azael Burning Force:: He random destroy your card.                                                       |\n";
	cout << "| III.  Azael Cast Barrier :: He nullifier damage this turn and heal 200.                                        |\n";
	cout << "*----------------------------------------------------------------------------------------------------------------*\n";
	cout << "|                                       *** Let's Go To Win Azael ***                                            |\n";
	cout << "*----------------------------------------------------------------------------------------------------------------*\n";
	cout << "[1] Let's Go!!!                                                                                     [2] Surrender" << endl;
	cout << "                                                   ----> ";
	cin >> keys;
	for(int l = 0;l<150;l++) cout << "\n";
	if(keys != 1){
		return 0;
	}
	do {
		cout << "Enter your name >> ";
		cin >> s;
		if (s.length() >= 8) cout << "Please Enter name less than 8 character.\n";
	} while (s.length() >= 8);
	CardPlayer p(s,false);
	CardPlayer r("Azael",true);
	int i = 1,php,rhp,bet;
	do{
		bet = 20 * i;
		roundPlay(p,r,cardDeck,cardItem,i,bet);
		php = p.showHP();
		rhp = r.showHP();
		i++;
		for(int l = 0;l<150;l++) cout << "\n";
	}while(php > 0 && rhp > 0);
	if (php <= 0) return false;
	else if (rhp <= 0) return true;
}
