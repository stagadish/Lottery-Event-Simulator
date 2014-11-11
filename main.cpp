#include <iostream>
#include <cstdlib>
using namespace std;
#include "LotteryTicket.h"
#include "LotteryMachine.h"

int main () {
	
	srand(time(0));
	
	int choice = 0;
	
	cout << "Enter '1' for automatic values.\n"
		 << "Enter '2' for entering values manualy.";
	cin >> choice;
	
	if(choice == 1)
		LotteryTicket test1(1, false);
	else
		LotteryTicket test1(1, true);
	
	LotteryTicket test2 = LotteryTicket(2);
	
    return 0;
}
