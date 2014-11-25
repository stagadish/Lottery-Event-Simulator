#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
#include "LotteryTicket.h"
#include "LotteryMachine.h"

const double TICKETPRICE = 5.00;

int main () {
	
	srand(time(0));

	vector<LotteryMachine> weeks;
	int weekNum = 1;
	char yesOrNo = 'y';
	
	cout << endl << "Welcome to The Lottery Game!!\n"
		         << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
		 << "There are four different kinds of prizes for you to win,"
		 << " so your chances are pretty good:\n\n"
		 << "Golden Prize - A WHOOPING sum of $100 if you get a perfect match!\n"
		 << "Silver Prize - An IMPRESSIVE sum of $70 if you match 9 numbers out of 10! easy, right??\n"
		 << "Bronze Prize - $40 for getting the right numbers in ANY ORDER - practically free money...\n"
		 << "Lucky  Prize - $5 if your last number equals to the last two digits\n"
		 << "               of the sum of all the lucky numbers.";
	
	
	
	do {									//Begin game with the first week.
		
		int numOfTicketsPurchased = 0, choice = 0;
		int totalPlayers = rand()%15000+15001;			//between 15000 to 30000 players <-- adjust here for less.
		int playerTurn = rand()%totalPlayers+1;
		
		weeks.push_back(LotteryMachine(TICKETPRICE));
		
//		//test for wins									//Uncomment to print winning ticket for the week
//		cout << endl << "Winning Ticket:\n";			//And test for Gold/Silver/Bronze winners...
//		weeks.back().printWinningTicket();				//Which NEVER occurs.
		
		cout << "\n\n\n\n***********************\n";
		cout << "Welcome to week No. " << weekNum << endl
			 << "One ticket: $" << TICKETPRICE << endl
			 << "***********************\n"
			 << "How many would you like to purchase? ";
		cin >> numOfTicketsPurchased;
		
		for(int i = 0; i < totalPlayers; i++) {
			
			if(i == playerTurn) {
				for(int j = 0; j < numOfTicketsPurchased; j++) {
					cout << endl << "Ticket " << j+1 << ":\n";
					cout << endl << "Enter '1' for automatic values.\n"
					<< "Enter '2' for entering values manually.";
					cin >> choice;
					
					if(choice == 1)
						weeks.back().generateNewTicket(false);
					else
						weeks.back().generateNewTicket(true);
					
					cout << endl << "Your ticket:";
					weeks.back().printLastTicket();
				}
				
				i += numOfTicketsPurchased;
				
			} else 
				weeks.back().generateNewTicket(false);
		}
		
		cout << "\n\n\n\n$$$ $$$ $$$ $$$ $$$ $$$ WEEK [" << weekNum << "] WINNERS ARE: $$$ $$$ $$$ $$$ $$$ $$$\n"; 
	
		weeks.back().findWinners();
		weeks.back().printWins();
		
		cout << "\n$$$ $$$ $$$ $$$ $$$ $$$ WEEK [" << weekNum << "] END OF REPORT $$$ $$$ $$$ $$$ $$$ $$$\n\n"; 
		
		cout << "\n\n\n\n% % % % % % % % % % % % WEEK [" << weekNum << "] STATISTICS % % % % % % % % % % % %\n";
		cout << "Tickets sold this week: " << weeks.back().getNumOfTicketsSold() << endl;
		cout << "Total income from tickets sale: $" << weeks.back().getTotalIncome() << endl;
		cout << "Total amount of prizes distributed: $" << weeks.back().getTotalPrizeSum() << endl;
		cout << "\nProfit -> $" << weeks.back().getTotalIncome()-weeks.back().getTotalPrizeSum() << endl;
		cout << "\n% % % % % % % % % % % % WEEK [" << weekNum << "] END OF STATISTICS % % % % % % % % %\n\n";
		
		weekNum++;
		
		cout << "Would you like to play again? (y/n) ";
		cin >> yesOrNo;
		
	} while(yesOrNo == 'y' || yesOrNo == 'Y');

	cout << endl << "$$$ Thank you for playing! See you soon! $$$\n\n\n";
	
    return 0;
}

