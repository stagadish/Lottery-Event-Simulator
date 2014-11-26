/* ****************************************************************************
 *  LotteryGame.h
 *  Lottery
 *
 *  Created by Gil Dekel on 11/8/14.
 *  Copyright 2014 aClass. All rights reserved.
 * ****************************************************************************
 * This class imitates one event of Lottery. Each event holds a vector of
 * lottery tickets purchased by all players, including our user. Each instance
 * of this class is initialized containing a lottery ticket that holds the lucky
 * numbers. This ticket is marked by a pointer and is not pushed to the vector.
 * All the other tickets are compared to the lucky numbers ticket. Should one of
 * these tickets match the lucky numbers (in one way out of four), its state will
 * be changed to a winnig ticket accordingly.
 * After winners have veen located, their location is kept in a pointer vector.
 * ****************************************************************************
 */

#ifndef LOTTERYGAME_H
#define LOTTERYGAME_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "LotteryTicket.h"


class LotteryGame
{
public:
	double getPricePerTicket();
	double getTotalIncome();
	double getTotalPrizeSum();
	int getNumOfTicketsSold();
	int getWeekNumber();
	
	void generateNewTicket(bool);
	void findWinners();
	
	//print methods
	void printWinningTickets();
	void printStatistics();
	void printTicket(LotteryTicket);
	void printLastTicket();
	void printAllTickets();
	
	//Constructors
	LotteryGame(double, int);
	LotteryGame();
	
	//test print to show the lucky numbers
	void printWinningTicket();

	
private:
	double pricePerTicket, totalPrizeSum;
	int ticketNumCounter, weekNum;
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

