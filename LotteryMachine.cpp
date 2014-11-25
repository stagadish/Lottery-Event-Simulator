/*
 *  LotteryMachine.cpp
 *  Lottery
 *
 *  Created by Gil Dekel on 11/8/14.
 *  Copyright 2014 Happy Palm Tree. All rights reserved.
 *
 */
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "LotteryMachine.h"
#include "LotteryTicket.h"


LotteryMachine::LotteryMachine(double ticketPrice)
		:pricePerTicket(ticketPrice), totalPrizeSum(0.0),
		 ticketNumCounter(1)
{
	winningTicket = new LotteryTicket(0, false);
}

LotteryMachine::LotteryMachine()
		:pricePerTicket(5.0), totalPrizeSum(0.0),
		 ticketNumCounter(1)
{
	winningTicket = new LotteryTicket(0, false);
}

double LotteryMachine::getPricePerTicket()
{
	return pricePerTicket;
}

double LotteryMachine::getTotalIncome()
{
	return allTickets.size()*pricePerTicket;
}

double LotteryMachine::getTotalPrizeSum()
{
	return totalPrizeSum;
}

int LotteryMachine::getNumOfTicketsSold()
{
	return allTickets.size();
}

void LotteryMachine::generateNewTicket(bool fillOrGenerate)
{
	allTickets.push_back(LotteryTicket(ticketNumCounter, fillOrGenerate));
	ticketNumCounter++;
}

void LotteryMachine::findWinners()
{
	for(int i = 0; i < allTickets.size(); i++) {
		if(!(goldOrSilverWinner(allTickets[i])))
			 if(!(bronzeWinner(allTickets[i])))
				luckyTenWinner(allTickets[i]);
	}
}

	
void LotteryMachine::printWins()
{
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
	
}

//Temp test
void LotteryMachine::printWinningTicket()
{
	printTicket(*winningTicket);
}


//Just a blackbox vector printing function.
void LotteryMachine::printTicket(LotteryTicket ticket)
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

void LotteryMachine::printLastTicket()
{
	printTicket(allTickets.back());
}

void LotteryMachine::printAllTickets()
{
	for(int i = 0; i < allTickets.size(); i++) {
		printTicket(allTickets[i]);
	}
}

//Private methods
bool LotteryMachine::goldOrSilverWinner(LotteryTicket& ticket)
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

bool LotteryMachine::bronzeWinner(LotteryTicket& ticket)
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

bool LotteryMachine::luckyTenWinner(LotteryTicket& ticket)
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

void LotteryMachine::sortTicket(LotteryTicket& ticket)
{
	for(int i = ticket.getLuckyNumbersList().size()-1; i >= 0; i--) {
		for(int j = 0; j < i; j++) {
			if(ticket.getLuckyNumbersList()[j] > ticket.getLuckyNumbersList()[j+1])
				swap(ticket.getLuckyNumbersList()[j], ticket.getLuckyNumbersList()[j+1]);
		}
	}
}

void LotteryMachine::swap(int& a, int& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

