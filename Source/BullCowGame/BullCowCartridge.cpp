// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    GetValidWords(Words);
    SetUpGame();
    
    PrintLine(TEXT("The number of possible words is %i."), Words.Num());
    PrintLine(TEXT("The numner of valid words is %i."), GetValidWords(Words).Num());
    PrintLine(TEXT("The Hidden Word is: %s."), *HiddenWord); // Debug line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
    }
    else // Cheking player guess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetUpGame ()
{
    PrintLine(TEXT("Welcome to the Bull Cow Game"));

    HiddenWord = TEXT("Cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type your guess.\nPress enter to continue..."));//prompt player to guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You got it!\nGood Job!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        --Lives;
        PrintLine(TEXT("The word is %i characters long."), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives remaining."), Lives);
        PrintLine(TEXT("Try guessing again!"));
        if (Lives <= 0)
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives remaining."));
            PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
            EndGame();
        }
        return;
    }

    if (Guess != HiddenWord)
    {
        --Lives;
        PrintLine(TEXT("You have %i lives remaining."), Lives);
        PrintLine(TEXT("Try guessing again!"));
        if (Lives <= 0)
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives remaining."));
            PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
            EndGame();
            return;
        }
        return;
    }

    //check if isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    /*int32 Index = 0;
    int32 Comparison = Index + 1;*/

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 6)
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}