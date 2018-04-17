
/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FString GetValidGuess();
void PrintGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main() 
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "		      Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "			          }   {         ___ " << std::endl;
	std::cout << "			          (o o)        (o o) " << std::endl;
	std::cout << "			   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "			  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << "			 *  |-,--- |              |------|  * " << std::endl;
	std::cout << "			    ^      ^              ^      ^ " << std::endl;
	std::cout << "		  Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame() 
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		PrintGuess();
	}

	PrintGameSummary();
}

FString GetValidGuess()
{
	FString Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		std::cout << std::endl;

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram, a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase letter word. \n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintGuess() 
{
	FString Guess = GetValidGuess();

	FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

	std::cout << "Bulls =  " << BullCowCount.Bulls;
	std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FString Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You Win! \n\n";
	}
	else
	{
		std::cout << "You Lose. Try again with the same word? \n\n";
	}
}