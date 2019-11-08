#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <map>

//Make syntax Unreal friendly
#define TMap std::map 
using FString = std::string;  //IVAN NOTE: Always add this at the top of a file, even if it was #included from another.
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLenToMaxTriesRatio    //This is a way to initialize multiple values into a TMap
	{
		{3,5}, {4,5}, {5,5}, {6,5}
	};
	
	return MyMaxTries; //Ivan Version 
	//return WordLenToMaxTriesRatio[MyHiddenWord.length()]; //Lector Version (Not used. Remove comment and comment out Ivan version to use)
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTries;
}

int32 FBullCowGame::GetHiddenWordLenght() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bMyGameWon;
}

void FBullCowGame::Reset()
{
	//IVAN NOTE: Make sure you use "constexpr" when defining magic numbers that shouldn't be changed...? Not sure.
	
	//Set Word (must be an ISOGRAM)
	const FString HIDDEN_WORD = "planet"; //TODO: Remove Magic word. Randomize word from list.
	
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = (HIDDEN_WORD.length()*2); //See Lector version in GetMaxTries() definition.
	MyCurrentTries = 1;
	bMyGameWon = false;
	return;
}

//IVAN VERSION// Guess Checking function, returns Enum EWordStatusValue 
/*
EGuessStatus FBullCowGame::CheckGuessValidity(FString GuessWord) const  
{
	int32 HiddenWordLen = MyHiddenWord.length();
	int32 GuessWordLen = GuessWord.length();

	if (HiddenWordLen == GuessWordLen) 
	{
		for (int32 i = 0; i < GuessWordLen; i += 1) // If its a Isogram, return early
		{
			for (int32 j = 0; j < GuessWordLen; j += 1)
			{
				if (i != j)
				{
					if (GuessWord[i] == GuessWord[j])
					{
						return EGuessStatus::Not_Isogram;
					}
				}
			}
		}
		return EGuessStatus::OK; // If not a early return (is a Isogram), return ok
	}
	else 
	{
		return EGuessStatus::Wrong_Length;
	}
	
}
*/

//LECTOR VERSION// Guess Checking function, returns Enum EWordStatusValue 
EGuessStatus FBullCowGame::CheckGuessValidity(FString GuessWord) const
{
	if (!IsIsogram(GuessWord)) //If guess isn't a isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(GuessWord)) //If guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GuessWord.length() != GetHiddenWordLenght()) //If guess isn't correct length
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}


// Receives a VALID guess, increment tries, returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString GuessWord)
{
	
	//Increment the tries
	MyCurrentTries += 1;   //This is a member var of FBullCowGame class where this func lives.
	
	//Create return value var
	FBullCowCount BullCowCountVar;

	//Get Bulls and Cows Counts
	//Loop through all letters in the Hidden word
	int32 HiddenWordLen = MyHiddenWord.length();
	int32 GuessWordLen = GuessWord.length();

	for (int32 i = 0; i < HiddenWordLen; i += 1)
	{
		//Compare each letter of Guessword against letter of the hidden word
		for (int32 j = 0; j < GuessWordLen; j += 1)
		{
			//if letter matches a letter in the word
			if (MyHiddenWord[i] == GuessWord[j])			
			{
				//if they are in the same place
				if (i == j)
				{
					//Increment bulls
					BullCowCountVar.Bulls += 1;
				}
				else
				{
					//increment cows
					BullCowCountVar.Cows += 1;
				}
			}
		}
	}

	//Is the the guess correct? (game won?)
	if (GuessWord == MyHiddenWord)
	{
		bMyGameWon = true;
	}

	return BullCowCountVar;

}

bool FBullCowGame::IsIsogram(FString GuessWord) const
{
	// IVAN VERSION // - For Loop with TMAP
	/*
	//Establish TMap container
	TMap<char, bool> GuessMap;

	//Loop through each letter
	for (int32 i = 0; i < GuessWord.length(); i += 1) 
	{
		//Set the var
		char CharLetter = GuessWord[i];
		CharLetter = tolower(Letter); //This makes the character a lower case if it isn't.

		//If the letter seen == false
		if (GuessMap[CharLetter] == false)
		{
			//Mark the letter seen as == true
			GuessMap[CharLetter] = true;
		}
		else
		{
			//return false;     //Exit the function early
			return false;
		}
	
	}*/
	
	// LECTOR VERSION // 
	// treat 0 and 1 letter words as isograms (this skips the rest of the function)
	if (GuessWord.length() <= 1)
	{
		return true;
	}

	//Establish TMap container
	TMap<char, bool> LetterSeen;

	//Loop through each character, and check if it was seen
	for (auto Letter : GuessWord) //IVAN NOTE: Ranged-based For Loop. This line means: for (type var in':' GuessWord) each character of GuessWord string. auto lets the compiler figure out the type var (char in this case).
	{
		Letter = tolower(Letter); //This makes the character a lower case if it isn't.
		
		//If the letter seen == false
		if (LetterSeen[Letter] == false)
		{
			//Mark the letter seen as == true
			LetterSeen[Letter] = true;
		}
		else
		{
			//return false;     //Exit the function early
			return false;
		}
	}
	//If loop completes without early return, exit with true (as this is an isogram)
	return true;
}

bool FBullCowGame::IsLowerCase(FString GuessWord) const
{
	for (auto Letter : GuessWord)
	{
		//Check if its nots a lowercase letter (this is a <iostream> function).
		if (!islower(Letter))
		{
			return false;
		}
	}
	
}
