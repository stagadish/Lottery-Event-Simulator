/*
 *  LotteryTicket.h
 *  Lottery
 *
 *  Created by Gil Dekel on 11/8/14.
 *  Copyright 2014 Happy Palm Tree. All rights reserved.
 *
 */
#ifndef LOTTERYTICKET_H
#define LOTTERYTICKET_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


class LotteryTicket
{
public:
	int getTicketNumber();
	
	bool getWinStatus();
	void setWinStatus(bool);
	
	char getTypeOfPrize();
	void setTypeOfPrize(char);
	//G - Golden, S - Silver, B - Bronze, L - Lucky, X - no win
	
	vector<int> getLuckyNumbersList();
	void inputLuckyNumbers();
	void generateLuckyNumbers();
	
	//Constructors:
	LotteryTicket(int);
	LotteryTicket(int, bool);
	
private:
	int ticketNumber;
	bool winner;
	char winnerType;
	vector<int>luckyNumbers;
	
	bool checkRepetitionOf(int);
	
	//print test
	//Just a blackbox vector printing function.
	void printVector();
	
	
};


#endif