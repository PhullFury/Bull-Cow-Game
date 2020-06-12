// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetUpGame();

    PrintLine((TEXT("The Hidden Word is: %s."), HiddenWord)); // Debug line
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
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You got it!\nGood Job!"));
            EndGame();
        }
        else
        {
            --Lives;
            if (Lives > 0)
            {
                if (Input.Len() != HiddenWord.Len())
                {
                    PrintLine(TEXT("The word is %i characters long."), HiddenWord.Len());
                }
                PrintLine(TEXT("You have %i lives remaining"), Lives);
                PrintLine(TEXT("Guess again..."));
            }
            else
            {
                PrintLine(TEXT("You have no lives remaining"));
                EndGame();
            }
        }
    }

    //Check if isogram
    //Check number of characters
    //Remove life

    //check if life > 0
    //if yes GuessAgain and show remaining life
    //if no show GameOver and show HiddenWord
    //prompt to PlayAgain
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