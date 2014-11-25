/*
 *  LotteryMachine.h
 *  Lottery
 *
 *  Created by Gil Dekel on 11/8/14.
 *  Copyright 2014 Happy Palm Tree. All rights reserved.
 *
 */
#ifndef LOTTERYMACHINE_H
#define LOTTERYMACHINE_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "LotteryTicket.h"


class LotteryMachine
{
public:
	double getPricePerTicket();
	double getTotalIncome();
	double getTotalPrizeSum();
	int getNumOfTicketsSold();
	
	void generateNewTicket(bool);
	void findWinners();
	void printWins();	
	void printTicket(LotteryTicket);
	void printLastTicket();
	void printAllTickets();
	
	//Constructors
	LotteryMachine(double);
	LotteryMachine();
	
	//Temp test
	void printWinningTicket();

	
private:
	double pricePerTicket, totalPrizeSum;
	int ticketNumCounter;
	LotteryTicket *winningTicket;
	
	bool goldOrSilverWinner(LotteryTicket&);
	bool bronzeWinner(LotteryTicket&);
	bool luckyTenWinner(LotteryTicket&);
	void sortTicket(LotteryTicket&);
	void swap(int&, int&);
	
	vector<LotteryTicket> allTickets;
	vector<LotteryTicket*> winners;
};


#endif

