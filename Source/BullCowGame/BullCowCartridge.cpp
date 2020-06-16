// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetUpGame();

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

    //Check if isogram
}

void UBullCowCartridge::SetUpGame ()
{
    PrintLine(TEXT("Welcome to the Bull Cow Game"));

    HiddenWord = TEXT("Cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
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
        PrintLine(TEXT("The word is %i characters long."), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives remaining"), Lives);
        PrintLine(TEXT("Try guessing again!"));
        return;
    }

    if (Guess != HiddenWord)
    {
        PrintLine(TEXT("You have %i lives remaining"), Lives);
        PrintLine(TEXT("Try guessing again!"));
        return;
    }

    //check if isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }

    PrintLine(TEXT("You lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives remaining"));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
        EndGame();
        return;
    }
}

bool UBullCowCartridge::IsIsogram(FString Word)
{
    /*for(int i = 0; i < Word.len(); i++)
    start at element [0]
    compare against the next letter
    until we reach [Word.Len() - 1]
    if any are same return false
    else true*/

    return true;
}
