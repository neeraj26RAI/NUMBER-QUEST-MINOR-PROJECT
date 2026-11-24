
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function declarations
int getInteger();
void displayMenu();
void setDifficulty(int choice, int *maxNumber,
                   int *maxAttempts, int *points);
int playGame(int maxNumber, int maxAttempts, int points);

// Function to accept valid integer input
int getInteger()
{
    int number;
    char extra;
    char input[100];

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nInput ended. Exiting game.\n");
            exit(0);
        }

        if (sscanf(input, " %d %c", &number, &extra) == 1)
        {
            return number;
        }

        printf("Invalid input! Please enter a valid number: ");
    }
}

// Function to display game menu
void displayMenu()
{
    printf("\n====================================\n");
    printf("          NUMBER QUEST              \n");
    printf("       GUESS THE SECRET NUMBER      \n");
    printf("====================================\n");

    printf("\nSelect Difficulty Level:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
}

// Function to set difficulty level
void setDifficulty(int choice, int *maxNumber,
                   int *maxAttempts, int *points)
{
    switch (choice)
    {
        case 1:
            *maxNumber = 50;
            *maxAttempts = 10;
            *points = 10;
            break;

        case 2:
            *maxNumber = 100;
            *maxAttempts = 7;
            *points = 15;
            break;

        case 3:
            *maxNumber = 200;
            *maxAttempts = 6;
            *points = 20;
            break;
    }
}

// Function to play the game
int playGame(int maxNumber, int maxAttempts, int points)
{
    int secretNumber;
    int guess;
    int attempts = 0;
    int score = 0;
    int won = 0;

    // Generate random secret number
    secretNumber = rand() % maxNumber + 1;

    printf("\n------------------------------------\n");
    printf("Guess a number between 1 and %d\n", maxNumber);
    printf("You have %d attempts.\n", maxAttempts);
    printf("------------------------------------\n");

    // Guessing loop
    while (attempts < maxAttempts)
    {
        printf("\nEnter your guess: ");
        guess = getInteger();

        // Validate guessing range
        if (guess < 1 || guess > maxNumber)
        {
            printf("Invalid range! Try again.\n");
            continue;
        }

        attempts++;

        // Check the guess
        if (guess == secretNumber)
        {
            printf("\nCongratulations! You won!\n");
            won = 1;
            break;
        }
        else if (guess < secretNumber)
        {
            printf("Too Low! Try a higher number.\n");
        }
        else
        {
            printf("Too High! Try a lower number.\n");
        }

        printf("Attempts remaining: %d\n",
               maxAttempts - attempts);
    }

    // Display result and calculate score
    if (won == 1)
    {
        score = (maxAttempts - attempts + 1) * points;

        printf("\n========== GAME RESULT ==========\n");
        printf("Correct Number: %d\n", secretNumber);
        printf("Attempts Used: %d\n", attempts);
        printf("Your Score: %d\n", score);
        printf("=================================\n");
    }
    else
    {
        printf("\n========== GAME OVER ============\n");
        printf("You have used all your attempts.\n");
        printf("Correct Number was: %d\n", secretNumber);
        printf("Your Score: 0\n");
        printf("=================================\n");
    }

    return score;
}

// Main function
int main()
{
    int choice;
    int maxNumber;
    int maxAttempts;
    int points;
    int score;
    int bestScore = 0;
    int playAgain = 1;

    // Initialise random number generator
    srand((unsigned int)time(NULL));

    printf("\nWelcome to NUMBER QUEST!\n");

    // Main game loop
    while (playAgain == 1)
    {
        displayMenu();

        printf("\nEnter your choice: ");
        choice = getInteger();

        // Validate difficulty selection
        if (choice < 1 || choice > 3)
        {
            printf("\nInvalid choice! Please select 1, 2 or 3.\n");
            continue;
        }

        // Set selected difficulty
        setDifficulty(choice, &maxNumber,
                      &maxAttempts, &points);

        // Start the game
        score = playGame(maxNumber, maxAttempts, points);

        // Update best score
        if (score > bestScore)
        {
            bestScore = score;
            printf("\nCongratulations! New Best Score!\n");
        }

        printf("\nYour Best Score: %d\n", bestScore);

        // Ask to play again
        while (1)
        {
            printf("\nDo you want to play again?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            printf("Enter your choice: ");

            playAgain = getInteger();

            if (playAgain == 1 || playAgain == 2)
            {
                break;
            }

            printf("Invalid choice! Enter 1 or 2.\n");
        }
    }

    // Exit message
    printf("\n====================================\n");
    printf("     THANK YOU FOR PLAYING!\n");
    printf("          NUMBER QUEST\n");
    printf("====================================\n");
    printf("Your Final Best Score: %d\n", bestScore);
    printf("See you again!\n");

    return 0;
}

