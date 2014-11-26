/* ****************************************************************************
 *  LotteryTicket.h
 *  Lottery
 *
 *  Created by Gil Dekel on 11/8/14.
 *  Copyright 2014 aClass. All rights reserved.
 * ****************************************************************************
 * This class imitates one ticket within a Lottery event. Each ticket holds a
 * vector of integers that holds the player's numbers.
 *
 * Each instance of this class is initialized with either user input numbers,
 * or automatically generated ones and are saved within the vector. Whether the
 * values should be given by the user or automatically generated is decided by
 * a boolean value within the constructor's arguments. The other takes in the
 * ticket's number. Both should be passed by an instance of 'LotteryGame' class.
 * ****************************************************************************
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
	char getTypeOfPrize();
	vector<int>& getLuckyNumbersList();
	
	void setWinStatus(bool);
	void setTypeOfPrize(char);
	//G - Golden, S - Silver, B - Bronze, L - Lucky, X - no win
	
	
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
	  
};


#endif

