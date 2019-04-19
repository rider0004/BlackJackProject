#include "Pro.h"
using namespace std;
int main(){
	srand(time(0));
	bool win = gamePlay();
	if (win){
		cout << "*------------------------------------------------*\n";
		cout << "|                                                |\n";
		cout << "|                  PLAYER WIN!!                  |\n";
		cout << "|                                                |\n";
		cout << "*------------------------------------------------*\n";
	}else{
		cout << "*------------------------------------------------*\n";
		cout << "|                                                |\n";
		cout << "|                  AZAEL  WIN!!                  |\n";
		cout << "|                                                |\n";
		cout << "*------------------------------------------------*\n";
	}
}
