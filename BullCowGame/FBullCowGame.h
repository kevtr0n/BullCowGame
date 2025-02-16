/*	The game logic (no view code or direct user interaction)
 *	The game is a simple guess the word game based on Mastermind
 */

#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Alpha,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:
	FBullCowGame(); // constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void Reset();
	FBullCowCount SubmitValidGuess(FString);
private:
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString Word) const;
	bool IsAlpha(FString Word) const;
	bool IsLowercase(FString Word) const;
};