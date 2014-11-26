/* ****************************************************************************
 *  LotteryTicket.cpp
 *  Lottery
 *
 *  Created by Gil Dekel on 11/8/14.
 *  Copyright 2014 aClass. All rights reserved.
 * ****************************************************************************
 * Implementation of LotteryTicket.h
 * ****************************************************************************
 */
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "LotteryTicket.h"

//*************
//Constructors:
//*************

//Initialize an instance with a ticket number given as an argument.
//Generate numbers automatically.
LotteryTicket::LotteryTicket(int ticketNum)
		:ticketNumber(ticketNum), winner(false), winnerType('X')
{
	generateLuckyNumbers();
}

//Initialize an instance with a ticket number given as an argument,
//and a boolean stating the user's choice regarding the method of
//value inputs (manually/automatically).
//Generate numbers manually if true, automatically if false.
LotteryTicket::LotteryTicket(int ticketNum, bool fillOrGenerate)
		:ticketNumber(ticketNum), winner(false), winnerType('X')
{
	if(fillOrGenerate)
		inputLuckyNumbers();
	else
		generateLuckyNumbers();
}

//************************
//Public Function Members:
//************************

//Accessors
int LotteryTicket::getTicketNumber()
{
	return ticketNumber;
}

bool LotteryTicket::getWinStatus()
{
	return winner;
}

char LotteryTicket::getTypeOfPrize()
{
	return winnerType;
}

vector<int>& LotteryTicket::getLuckyNumbersList()
{
	return luckyNumbers;
}
//end of Accessors.


//Mutators
void LotteryTicket::setWinStatus(bool isWinner)
{
	winner = isWinner;
}

void LotteryTicket::setTypeOfPrize(char typeOfPrize)
{
	winnerType = typeOfPrize;
}
//end of Mutators.



//Traverse the vector and place user defined
//values. 1 to 60. No repetition allowed.
void LotteryTicket::inputLuckyNumbers()
{
	int counter = 1, nextNum = 0;
	
	cout << endl << "Please choose 10 numbers between 1 and 60:\n"
		 << "(No repetition of numbers is allowed.)\n";
	
	while(luckyNumbers.size() < 10) {
		cout << "Lucky number No." << counter << ": ";
		cin >> nextNum;
		
		if(nextNum >= 1 && nextNum <= 60) {
			if(checkRepetitionOf(nextNum)) {
				cout << "I am sorry. The number " << nextNum << " is already in your list.\n"
					 << "Please try a different one.\n";
			} else {
				luckyNumbers.push_back(nextNum);
				counter++;
			}
		} else {
			cout << "I am sorry. You chose an invalid entry.\nPlease try again.\n";
		}
	}
}

//Traverse the vector and place auto generated
//values. 1 to 60. No repetition allowed.
void LotteryTicket::generateLuckyNumbers()
{
	int nextNum = 0;
	
	while(luckyNumbers.size() < 10) {
		nextNum = rand()%60+1;
		
		if(nextNum >= 1 && nextNum <= 60) {
			if(!(checkRepetitionOf(nextNum))) 
				luckyNumbers.push_back(nextNum);
		}
	}
}



//*************************
//Private Member Functions:
//*************************

//Traverse the vector and look for given argument.
//If found, break the iteration and return true.
//If not, return false.
bool LotteryTicket::checkRepetitionOf(int nextNum)
{
	bool numFound = false;
	
	for(int i = 0; i < luckyNumbers.size(); i++) {
		if(luckyNumbers[i] == nextNum) {
			numFound = true;
			break;
		}
	}
	
	return numFound;
}

