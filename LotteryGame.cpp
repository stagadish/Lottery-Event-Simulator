/* ****************************************************************************
 *  LotteryGame.cpp
 *  Lottery
 *
 *  Created by Gil Dekel on 11/8/14.
 *  Copyright 2014 aClass. All rights reserved.
 * ****************************************************************************
 * Implementation of LotteryGame.h
 * ****************************************************************************
 */
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "LotteryGame.h"
#include "LotteryTicket.h"

//*************
//Constructors:
//*************

//Initialize an instance with a price and the number of the
//current week.
//Initialize a dynamically allocated instance of LotteryTicket to
// hold a lucky numbers ticket and set a pointer to it.
LotteryGame::LotteryGame(double ticketPrice, int weekNumber)
		:pricePerTicket(ticketPrice), totalPrizeSum(0.0),
		 ticketNumCounter(1), weekNum(weekNumber)
{
	winningTicket = new LotteryTicket(0, false);
}

//Initialize an instance with default values.
//Initialize a dynamically allocated instance of LotteryTicket to
//hold a lucky numbers ticket and set a pointer to it.
LotteryGame::LotteryGame()
		:pricePerTicket(5.0), totalPrizeSum(0.0),
		 ticketNumCounter(1), weekNum(1)
{
	winningTicket = new LotteryTicket(0, false);
}

//************************
//Public Function Members:
//************************

//Accessors
double LotteryGame::getPricePerTicket()
{
	return pricePerTicket;
}

double LotteryGame::getTotalIncome()
{
	return allTickets.size()*pricePerTicket;
}

double LotteryGame::getTotalPrizeSum()
{
	return totalPrizeSum;
}

int LotteryGame::getNumOfTicketsSold()
{
	return allTickets.size();
}

int LotteryGame::getWeekNumber()
{
	return weekNum;
}
//end of Accessors.



//Work functions:

//Instantiate a new LotteryTicket object and push
//it to the end of the LotteryTicket vector.
//True for manual input of numbers,
//False for automatic generation of numbers.
void LotteryGame::generateNewTicket(bool fillOrGenerate)
{
	allTickets.push_back(LotteryTicket(ticketNumCounter, fillOrGenerate));
	ticketNumCounter++;
}

//Traverse the LotteryTicket vector
//and check for winners. It will check for a lesser
//type of prize only if higher ones were not find for
//each ticket.
void LotteryGame::findWinners()
{
	for(int i = 0; i < allTickets.size(); i++) {
		if(!(goldOrSilverWinner(allTickets[i])))
			 if(!(bronzeWinner(allTickets[i])))
				luckyTenWinner(allTickets[i]);
	}
}

//Traverse the LotteryTicket pointer vector and print
//all the winning ticket in a nice report format.
void LotteryGame::printWinningTickets()
{
	cout << "\n\n\n\n$$$ $$$ $$$ $$$ $$$ $$$ WEEK [" << weekNum << "] WINNERS ARE: $$$ $$$ $$$ $$$ $$$ $$$\n"; 
	
	if(!(winners.empty())) {
		for(int i = 0; i < winners.size(); i++) {
			printTicket(*winners[i]);
			cout << "Congratulations!! ";

		switch (winners[i]->getTypeOfPrize())
			{
				case 'G':
					cout << "IS A GOLD WINNER!! -> $100 <-\n";
					break;
				case 'S':
					cout << "IS A SILVER WINNER!! -> $70 <-\n";
					break;
				case 'B':
					cout << "IS A BRONZE WINNER!! -> $40 <-\n";
					break;
				case 'L':
					cout << "IS A LUCKY WINNER!! -> $5 <-\n";
					break;
			}

		}
		
	} else
	   cout << endl << "No winning tickets this week.\nBetter luck next time!\n";
	
	cout << "\n$$$ $$$ $$$ $$$ $$$ $$$ WEEK [" << weekNum << "] END OF REPORT $$$ $$$ $$$ $$$ $$$ $$$\n\n"; 
	
}

//Print general statistics about this specific
//Lottery event/game.
void LotteryGame::printStatistics()
{
	cout << "\n\n\n\n% % % % % % % % % % % % WEEK [" << weekNum << "] STATISTICS % % % % % % % % % % % %\n";
	cout << "Tickets sold this week: " << getNumOfTicketsSold() << endl;
	cout << "Total income from tickets sale: $" << getTotalIncome() << endl << endl;
	
	cout << "Number of winning tickets: " << winners.size() << endl;
	cout << "Total amount of prizes distributed: $" << getTotalPrizeSum() << endl;
	cout << "That is " << (static_cast<double>(winners.size())/getNumOfTicketsSold())*100
		 << "% win rate." << endl << endl;
	
	cout << "\nProfit -> $" << getTotalIncome()-getTotalPrizeSum() << endl;
	cout << "Which is " << ((getTotalIncome()-getTotalPrizeSum())/getTotalIncome())*100
		 << "% profit.";
	cout << "\n% % % % % % % % % % % % WEEK [" << weekNum << "] END OF STATISTICS % % % % % % % % %\n\n";
}

//Temp test
//Use this print to print the ticket holding
//the lucky numbers. Useful for tests of the
//algorithm.
void LotteryGame::printWinningTicket()
{
	printTicket(*winningTicket);
}


//Take in an object of kind Lottery Ticket.
//Print it in a nice ticket format.
void LotteryGame::printTicket(LotteryTicket ticket)
{
	cout << endl << "**********************************************";
	cout << endl << "* Ticket number " 
	<< ticket.getTicketNumber() << ": ";
	
	for(int i = 0; i < ticket.getLuckyNumbersList().size(); i++) {
		if (i == 0 && i == ticket.getLuckyNumbersList().size()-1)
			cout << endl << "* {" << ticket.getLuckyNumbersList()[i] << "}\n";
		else if(i == 0)
			cout << endl << "* {" << ticket.getLuckyNumbersList()[i] << ", ";
		else if(i == ticket.getLuckyNumbersList().size()-1)
			cout << ticket.getLuckyNumbersList()[i] << "}\n";
		else
			cout << ticket.getLuckyNumbersList()[i] << ", ";
	}
	cout << "**********************************************\n";
}

//Print the last ticket that was pushed to the
//LotteryTicket vector.
void LotteryGame::printLastTicket()
{
	printTicket(allTickets.back());
}

//Travers the LotteryTicket vector and
//print ALL tickets.
void LotteryGame::printAllTickets()
{
	for(int i = 0; i < allTickets.size(); i++) {
		printTicket(allTickets[i]);
	}
}




//*************************
//Private Member Functions:
//*************************

//Take in an instance of a LotteryTicket.
//Return true if a winner, False otherwise.
//This is done by one-to-one comparison and
//counting the differences:
//If the number of differences is equal to 0,
//then the ticket is a perfect match and
//is a GOLD winner.
//If the number of differences is equal to 1,
//then the ticket is a SILVER winner.
//If the number of differences is larger than 1,
//break the iteration and return false.
bool LotteryGame::goldOrSilverWinner(LotteryTicket& ticket)
{
	int numOfDifferentElements = 0;
	
	for(int j = 0; j < winningTicket->getLuckyNumbersList().size(); j++) {
			if(winningTicket->getLuckyNumbersList()[j] - ticket.getLuckyNumbersList()[j] != 0) {
				numOfDifferentElements++;
				if(numOfDifferentElements > 1)
					break;
			}
		}
		
		switch (numOfDifferentElements)
		{
			case 0: //100% one-to-one match -> Gold winner
				ticket.setWinStatus(true);
				ticket.setTypeOfPrize('G');
				totalPrizeSum += 100;
				winners.push_back(&ticket);
				return true;
				break;
				
			case 1: //90% 9 positions match -> Silver winner
				ticket.setWinStatus(true);
				ticket.setTypeOfPrize('S');
				totalPrizeSum += 70;
				winners.push_back(&ticket);
				return true;
				break;
				
			default: return false;
				
		}
		
}



//Take in an instance of a LotteryTicket.
//Return true if a winner, False otherwise.
//This is done by sorting (a copy of) the
//lucky numbers ticket and (a copy of) the
//competing ticket, and them comparing them.
//If the two sets are equal, the ticket is a
//BRONZE winner. If one difference is found,
//the sets are not equal and the iteration is
//stopped.
bool LotteryGame::bronzeWinner(LotteryTicket& ticket)
{
	bool bronzePrize = true;
	
	LotteryTicket winTicket = *winningTicket;
	LotteryTicket tempTicket = ticket;
	
	sortTicket(winTicket);
	sortTicket(tempTicket);
	
	
	for(int i = 0; i < winTicket.getLuckyNumbersList().size(); i++) {
		if(winTicket.getLuckyNumbersList()[i] - tempTicket.getLuckyNumbersList()[i] != 0) {
			bronzePrize = false;
			break;
		}
	}
	
	if(bronzePrize) {
		ticket.setWinStatus(true);
		ticket.setTypeOfPrize('B');
		totalPrizeSum += 40;
		winners.push_back(&ticket);
	}
	
	return bronzePrize;
}

//Take in an instance of a LotteryTicket.
//Return true if a winner, False otherwise.
//This is done by comparing the competing
//ticket's last number with the last two digits
//of the sum of all the lucky numbers.
bool LotteryGame::luckyTenWinner(LotteryTicket& ticket)
{
	int luckyNum = 0;
	bool luckyPrize = false;
	
	for(int i = 0; i < winningTicket->getLuckyNumbersList().size(); i++)
		luckyNum += winningTicket->getLuckyNumbersList()[i];
	
	luckyNum = luckyNum%100;
	
	if(ticket.getLuckyNumbersList().back() == luckyNum) {
		ticket.setWinStatus(true);
		ticket.setTypeOfPrize('L');
		totalPrizeSum += 5;
		winners.push_back(&ticket);
		luckyPrize = true;
	}
	
	return luckyPrize;
}


//A simple bubble sort.
void LotteryGame::sortTicket(LotteryTicket& ticket)
{
	for(int i = ticket.getLuckyNumbersList().size()-1; i >= 0; i--) {
		for(int j = 0; j < i; j++) {
			if(ticket.getLuckyNumbersList()[j] > ticket.getLuckyNumbersList()[j+1])
				swap(ticket.getLuckyNumbersList()[j], ticket.getLuckyNumbersList()[j+1]);
		}
	}
}

//Bitwise operation swap.
void LotteryGame::swap(int& a, int& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

