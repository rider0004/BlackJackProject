#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;

string cardName[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
int cardScore[] = {11,2,3,4,5,6,7,8,9,10,10,10,10};
vector<int> azaelCard;
vector<int> playerCard;
int score = 0,scoreAzael = 0;
bool cardDeck[13];
//unsigned int bet = 50,round = 1; 

void playGame(int &,int &);
int drawCard(void);
void showAzael(void);
void showPlayer(void);
int calScore(void);
void scoreCal(void);
void azaelPlay(void);

int main(){
	srand(time(0));
	int azaelHp = 1000,playerHp = 1000;
	do {
		for (int i = 0;i < 2;i++){
			azaelCard.push_back(drawCard());
			playerCard.push_back(drawCard());
		}
		//cout << "----------Round " << round << "----------\n";
		//cout << "BET : " << bet << " POINT\n" << "HP " << azaelHp << ":" << playerHp << "\n";
		playGame(azaelHp,playerHp);
		//round++;
		//bet+=50;
	} while (azaelHp > 0 && playerHp > 0);
	if (playerHp <= 0) cout << "Lose\n-------------------------\n";
	else cout << "Win\n-------------------------\n";
}
void playGame(int &azaelHp,int &playerHp){
	int input;
	do {
		scoreCal();
		showAzael();
		showPlayer();
		cout << "input 1 to Draw\n      2 to Stand\nInput : ";
		cin >> input;
		if (input == 1) playerCard.push_back(drawCard());
		azaelPlay();
	} while (input != 2);
	cout << "Azael's cards : ";
	for (int i = 0;i < azaelCard.size();i++){
		cout << azaelCard[i] << " ";
	}
	cout << "\nPlayer's' Cards : ";
	for (int i = 0;i < playerCard.size();i++){
		cout << playerCard[i] << " ";
	}
	scoreCal();
	cout << "\nAzael's score = " << scoreAzael << "\nPlayer's score = " << score << "\n";
	switch (calScore()) {
		case 1 : cout << "Round Lose\n\n";playerHp -= 1000;playerCard.clear();azaelCard.clear();break;
		case 2 : cout << "Round Draw\n\n";playerCard.clear();azaelCard.clear();break;
		case 3 : cout << "Round Win\n\n";azaelHp -= 1000;playerCard.clear();azaelCard.clear();break;
	}
}
int drawCard(void){
	int draw;
	do {
		draw = rand()%13;
		if (cardDeck[draw] == 0){
			cardDeck[draw] = true;
			break;
		}
	} while (true);
	return cardScore[draw];
}
void showAzael(void){
	cout << "Azael's cards : ? ";
	for (int i = 1;i < azaelCard.size();i++){
		cout << azaelCard[i] << " ";
	}
	cout << "\n";
}
void showPlayer(void){
	cout << "Player's cards : ";
	for (int i = 0;i < playerCard.size();i++){
		cout << playerCard[i] << " ";
	}
	cout << "\nPlayerScore = " << score << "\n";
}
int calScore(void){
	if (score == scoreAzael || (score > 21 && scoreAzael > 21)) return 2;
	else if (scoreAzael > 21) return 3;
	else if (score > 21) return 1;
	else if (score < scoreAzael) return 1;
	else return 3;
}
void scoreCal(void){
	scoreAzael = 0;
	score = 0;
	for (int i = 0;i < azaelCard.size();i++){
		scoreAzael += azaelCard[i];
	}
	for (int j = 0;j < playerCard.size();j++){
		score += playerCard[j];
	}
}
void azaelPlay(void){
	if (scoreAzael <= 16) azaelCard.push_back(drawCard());
}
