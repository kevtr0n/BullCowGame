/*	
 *	BullCowGame game logic
 */

#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,16 },{ 7,20 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {
	// this MUST be an isogram
	const FString HIDDEN_WORD = "plane"; 
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// Makes sure that the guess adheres to all conventions.
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) return EGuessStatus::Not_Isogram;
	else if (!IsAlpha(Guess)) return EGuessStatus::Not_Alpha;
	else if (!IsLowercase(Guess)) return EGuessStatus::Not_Lowercase;
	else if (Guess.length() != GetHiddenWordLength()) return EGuessStatus::Wrong_Length;
	else return EGuessStatus::OK;
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); 
	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) BullCowCount.Bulls++; 
				else BullCowCount.Cows++; 
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) bGameIsWon = true;
	else bGameIsWon = false;
	return BullCowCount;
}

// Checks to see if word is an isogram.
bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) {
		Letter = tolower(Letter); 
		if (LetterSeen[Letter]) return false; 
		else LetterSeen[Letter] = true;// add the letter to the map
	}
	return true; // for example in cases where /0 is entered
}

// Checks to see if word is all letters.
bool FBullCowGame::IsAlpha(FString Word) const {
	for (auto Letter : Word) if (!isalpha(Letter)) return false;
	return true;
}

// Checks to see if word is all lowercase.
bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) if (!islower(Letter)) return false;
	return true;
}