/*
 *  LotteryTicket.cpp
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
#include "LotteryTicket.h"

LotteryTicket::LotteryTicket(int ticketNum)
		:ticketNumber(ticketNum), winner(false), winnerType('X')
{
	generateLuckyNumbers();
}

LotteryTicket::LotteryTicket(int ticketNum, bool fillOrGenerate)
:ticketNumber(ticketNum), winner(false), winnerType('X')
{
	if(fillOrGenerate)
		inputLuckyNumbers();
	else
		generateLuckyNumbers();
}

int LotteryTicket::getTicketNumber()
{
	return ticketNumber;
}

bool LotteryTicket::getWinStatus()
{
	return winner;
}

void LotteryTicket::setWinStatus(bool isWinner)
{
	winner = isWinner;
}

char LotteryTicket::getTypeOfPrize()
{
	return winnerType;
}

void LotteryTicket::setTypeOfPrize(char typeOfPrize)
{
	winnerType = typeOfPrize;
}

vector<int> LotteryTicket::getLuckyNumbersList()
{
	return luckyNumbers;
}

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
	
	//print test
	cout << endl << "Your Ticket (No." << ticketNumber << "):\n";
	printVector();
}

void LotteryTicket::generateLuckyNumbers()
{
	int nextNum = 0;
	
	while(luckyNumbers.size() < 10) {
		nextNum = rand()%60+1;
		
		if(nextNum >= 1 && nextNum <= 60) {
			if(checkRepetitionOf(nextNum)) 
				continue;
			else
				luckyNumbers.push_back(nextNum);
		}
	}
	
	//print test
	cout << endl << "Your Ticket (No." << ticketNumber << "):\n";
	printVector();
}

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

//Just a blackbox vector printing function.
void LotteryTicket::printVector()
{
	for(int i = 0; i < luckyNumbers.size(); i++) {
		if (i == 0 && i == luckyNumbers.size()-1)
			cout << endl << "{" << luckyNumbers[i] << "}\n";
		else if(i == 0)
			cout << endl << "{" << luckyNumbers[i] << ", ";
		else if(i == luckyNumbers.size()-1)
			cout << luckyNumbers[i] << "}\n";
		else
			cout << luckyNumbers[i] << ", ";
	}
}
