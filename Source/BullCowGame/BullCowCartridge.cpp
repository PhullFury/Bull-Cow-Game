// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidWords(Words);
    SetUpGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
    }
    else // Cheking player guess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetUpGame ()
{
    PrintLine(TEXT("Welcome to the Bull Cow Game"));

    int32 Number = FMath::RandRange(0, Isograms.Num() - 1);

    HiddenWord = Isograms[Number];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("The Hidden Word is: %s."), *HiddenWord); // Debug line
    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type your guess.\nPress enter to continue..."));//prompt player to guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
        return;
    }

    //check if isogram
    if (!IsIsogram(Guess))
    {
        --Lives;
        PrintLine(TEXT("No repeating letters, guess again!"));
        PrintLine(TEXT("You have %i lives remaining."), Lives);
        return;
    }

    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives remaining."));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
        EndGame();
        return;
    }

    //show the player Bulls Cows
    FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("You have %i bulls and %i cows."), Score.Bulls, Score.Cows);
    PrintLine(TEXT("You have %i lives remaining."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 6 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}