/*
This is the console executable, that makes use of the BullCow class.
This acts as the view in the MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//Make Syntax Unreal Friendly
using int32 = int;
using FText = std::string;

//Declare Functions outside a class
void PrintIntro();
void PlayGame();
void PrintGameEnd();
bool AskPlayAgain();
FText GetValidGuess();

FBullCowGame BCGame;		//Creates an instance of this class thats reused / called.

//Start Application
int main()  //Never use int32 for main, as this is called by the OS.
{
	bool bWantsToPlay = true;

	do 
	{
		PrintIntro();
		PlayGame();
		bWantsToPlay = AskPlayAgain();
	} 
	while(bWantsToPlay);

	std::cout << std::endl;
	return 0; //Exit Application
}

void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "\n     Welcome to Bulls & Cows!\n\n";
	std::cout << "             /( ,,,,, )\\				\n";
	std::cout << "            _\\,;;;;;;;,/_				\n";
	std::cout << "         .--; ;;;;;;;;; ;--.			\n";
	std::cout << "         '.__/`_ / \\ _`\\__.'			\n";
	std::cout << "            | (')| |(')  |			\n";
	std::cout << "            | .--' '--.  |			\n";
	std::cout << "            |/ o     o \\ |			\n";
	std::cout << "            |            |			\n";
	std::cout << "           / \\ _..=.._ / \\			\n";
	std::cout << "          /:. '._____.'   \\			\n";
	std::cout << "         ;::'    / \\      .;			\n";
	std::cout << "         |     _|_ _|_   ::|			\n";
	std::cout << "       .-|     '==o=='    '|-.		\n";
	std::cout << "      /  |  . /       \\    |  \\		\n";
	std::cout << "      |  | ::|         |   | .|		\n";
	std::cout << "      |  (  ')         (.  )::|		\n";	
	std::cout << "      |: |   |; U U U ;|:: | `|		\n";
	std::cout << "      |' |   | \\ U U / |'  |  |		\n";
	std::cout << "      ##V|   |_/-----\\_|   |V##		\n";
	std::cout << "         ##V##         ##V##			\n";
	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter word?\n";
	return;
}

//Play a single game until you lose/win.
void PlayGame()
{
	BCGame.Reset(); //Reset the game instance (which also sets the core values to default)

	int32 const MaxTries = BCGame.GetMaxTries();
	
	//While there are try's remaining, and Game NOT won, loop this
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		//Get VALID input from user
		FText Guess = GetValidGuess();
		
		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;	//Print the number of Bulls and Cows
		std::cout << ". Cows = " << BullCowCount.Cows;	//Print the number of Bulls and Cows
		std::cout << std::endl;
	}

	PrintGameEnd();
	std::cout << std::endl;
	return;
}

//Print Game Won summary when done.
void PrintGameEnd()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\n** You won! Congratulations! ** ";
	}
	else
	{
		std::cout << "\n** You ran out of tries! :( ** ";
	}
}

//Loop until a Valid guess is entered.
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		//Get a guess from User
		std::cout << std::endl;
		std::cout << "Try(" << CurrentTry << "/" << BCGame.GetMaxTries() << "): " << "Enter your Guess: ";
		std::getline(std::cin, Guess);			//Get input from user and assign it to the var 'Guess'

		//Validate Guess
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters (isogram). \n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Wrong word lenght. Try a " << BCGame.GetHiddenWordLenght() << " letter word. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please only use lowercase letters. \n";
			break;
		default:
			//Assume Guess is Valid
			break;
		}
	} while (Status != EGuessStatus::OK);  //Keep looping until no errors are picked up
	
	return Guess;
}

bool AskPlayAgain()
{
	std::cout << "\n\nDo you want to play again? (y/n)\n";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');  //IVAN NOTE: When you are comparing characters, use '' not "". "" for strings only.
	
}