/* The Game logic (no view code or direct user interaction)      //IVAN NOTE: Always introduce your class at the top with Block Comments. This file and its .cpp handles the class.
The game is a simple guess game based on mastermind. */

#pragma once
#include <string>

// IVAN NOTE: Never use "using namespace" in header files. Infact, avoid using namespace alltogether.
//Make syntax Unreal friendly
using FString = std::string;
using int32 = int;

//IVAN NOTE: A struct is like a class, but its member vars are public. This is ideal to use instead of class when simple data types are needed & no functions.
struct FBullCowCount    //All values initialized to 0
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

//IVAN NOTE: When you add 'class' to an enum, it ensures its values aren't global. This is called a strongly typed enum, and won't interfere with other enums.
enum class EGuessStatus
{
	Invalid,				//IVAN NOTE: Its good practise to start a enum with 'Invalid'
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:							//IVAN NOTE: Ideally, we only want Methods(Funtions) in our public interface. Vars in Private.
	FBullCowGame(); //This is the Contructor (Instance Creation code)

	int32 GetMaxTries() const;	//IVAN NOTE: using 'const' at the end of a MEMBER FUNCTION, will ensure the vars in it can't be changed. Good safety, use frequently.
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;

	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;
	void Reset();				// TODO: Make a more rich return value
	FBullCowCount SubmitValidGuess(FString GuessWord);



private:
	//  See Constructor code (Instance Creation Code) for value initialization
	int32 MyCurrentTries;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bMyGameWon;
	
	//Helper Methods, are private methods in a class. They are below:
	bool IsIsogram(FString GuessWord) const;
	bool IsLowerCase(FString GuessWord) const;
};

