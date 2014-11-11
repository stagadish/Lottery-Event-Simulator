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
	double getTotalPriceSum();
	int getNumOfTicketsSold();
	
	LotteryTicket generateNewTicket();
	void findWinners();
	void printWins();

	
private:
	double pricePerTicket, totalIncome, totalPriceSum;
	int numOfTicketsSold, ticketNumCounter;
	LotteryTicket winningTicket;
	
	vector<LotteryTicket>allTickets;
//	vector<LotteryTicket>winningTickets;
};


#endif