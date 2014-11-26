/* ****************************************************************************
 *  main.cpp
 *  Lottery
 *
 *  Created by Gil Dekel on 11/8/14.
 *  Copyright 2014 aClass. All rights reserved.
 * ****************************************************************************
 * On my honor,
 * The following program is a result of personal effort. I have not discussed
 * with anyone other than my instructor or any appropriate person in charge
 * of the class. I have not used code or portion of code from another student,
 * or any other unauthorized source, either modified or unmodified.
 *
 * If any C++ language code or documentation used in my program was obtained
 * from another source, such as a text book or course notes, that has been
 * clearly noted with a proper citation in the comments of my program.
 *
 * I have not designed this program in such a way as to defeat or
 * interfere with the normal operation of the eniac system or cslab
 * machines at Hunter College .
 *
 * This is a solution to Professor Ngnosse's
 * Fall2014 Project 2 - Choice B: The Lottery Machine Simulator.
 * ****************************************************************************
 * This program simulates a weekly Lottery event. Each week, a new game begins
 * with new winning numbers.
 * 
 * This is the driver program. It interact with the user.
 * The main method holds a vector of `LotteryGame` objects. With each iteration
 * of the program, a new instance of `LotteryGame` is created and all
 * operations are made on it. At the end of each iteration, the a winning
 * tickets are printed with some additional statistics. In addition, the 
 * week counter is incremented and the user is asked if he would like
 * to play again. The program ends when the user choose no for an answer.
 * ****************************************************************************
 */

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
#include "LotteryTicket.h"
#include "LotteryGame.h"

const double TICKETPRICE = 5.00;

int main () {
	
	srand(time(0));
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	vector<LotteryGame> weeks;
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
	
	
	
	do {								//Begin game with the first week.
		
		int numOfTicketsPurchased = 0, choice = 0;
		int totalPlayers = rand()%15000+15001;			//between 15000 to 30000 players <-- adjust here for more/less.
		
		int playerTurn = rand()%totalPlayers+1;			//Simulate a random entry point for the user so his ticket will
									//not always be the first ticket.
		
		weeks.push_back(LotteryGame(TICKETPRICE, weekNum));		//Add a new game. Generate new lucky numbers.
		
//		//test for wins						//Uncomment to print winning ticket for the week
//		cout << endl << "Winning Ticket:\n";			//And test for Gold/Silver/Bronze winners...
//		weeks.back().printWinningTicket();			//Which NEVER occurs.
		
		cout << "\n\n\n\n***********************\n";				//How many tickets
		cout << "Welcome to week No. " << weeks.back().getWeekNumber() << endl	//would the user like
			 << "One ticket: $" << TICKETPRICE << endl			//to buy?
			 << "***********************\n"
			 << "How many would you like to purchase? ";
		cin >> numOfTicketsPurchased;
		
		for(int i = 0; i < totalPlayers; i++) {			//Begin mass purchase of tickets.
			
			if(i == playerTurn) {								//If it's the user's turn
				for(int j = 0; j < numOfTicketsPurchased; j++) {			//begin interaction
					cout << endl << "Ticket " << j+1 << ":\n";
					cout << endl << "Enter '1' for automatic values.\n"
					<< "Enter '2' for entering values manually.";
					cin >> choice;
					
					if(choice == 1)
						weeks.back().generateNewTicket(false);
					else
						weeks.back().generateNewTicket(true);
					
					cout << endl << "Your ticket:";
					weeks.back().printLastTicket();			//print the user's new ticket.
				}
				
				i += numOfTicketsPurchased;
				
			} else 
				weeks.back().generateNewTicket(false);
		}

		weeks.back().findWinners();
		weeks.back().printWinningTickets();
		weeks.back().printStatistics();
		weekNum++;
		
		cout << "Would you like to play again? (y/n) ";
		cin >> yesOrNo;
		
	} while(yesOrNo == 'y' || yesOrNo == 'Y');

	cout << endl << "$$$ Thank you for playing! See you soon! $$$\n\n\n";
	
    return 0;
}

