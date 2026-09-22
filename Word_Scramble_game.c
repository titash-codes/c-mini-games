#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TOTAL_ROUNDS 5
#define WORDS_PER_CATEGORY 10
#define MAX_WORD_LENGTH 30

typedef struct
{
    char word[MAX_WORD_LENGTH];
    int difficulty;
} Word;

Word animals[WORDS_PER_CATEGORY] =
{
    {"cat", 1},
    {"dog", 1},
    {"lion", 1},
    {"tiger", 1},
    {"horse", 1},
    {"rabbit", 2},
    {"elephant", 2},
    {"giraffe", 2},
    {"crocodile", 3},
    {"chimpanzee", 3}
};

Word food[WORDS_PER_CATEGORY] =
{
    {"rice", 1},
    {"cake", 1},
    {"apple", 1},
    {"pizza", 1},
    {"bread", 1},
    {"banana", 2},
    {"burger", 2},
    {"sandwich", 2},
    {"pineapple", 3},
    {"chocolate", 3}
};

Word objects[WORDS_PER_CATEGORY] =
{
    {"pen", 1},
    {"book", 1},
    {"chair", 1},
    {"table", 1},
    {"phone", 1},
    {"bottle", 2},
    {"pencil", 2},
    {"computer", 2},
    {"television", 3},
    {"refrigerator", 3}
};

Word places[WORDS_PER_CATEGORY] =
{
    {"park", 1},
    {"school", 1},
    {"hotel", 1},
    {"market", 1},
    {"beach", 1},
    {"hospital", 2},
    {"airport", 2},
    {"museum", 2},
    {"restaurant", 3},
    {"university", 3}
};

void clearInputBuffer();
void toLowerCase(char str[]);
void removeNewline(char str[]);
void scrambleWord(char original[], char scrambled[]);
void displayInstructions();
void displayCategories();
void displayDifficulty();
int getDifficulty();
int getCategory();

void getWordFromCategory(
    int category,
    int difficulty,
    char selectedWord[],
    int usedIndices[]
);

int calculateBaseScore(int difficulty);
int calculateSpeedBonus(double timeTaken);
void giveHint(char word[], char hint[]);
void displayFinalResult(
    int score,
    int correct,
    int total,
    int hintsUsed,
    double totalTime
);

void clearInputBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void removeNewline(char str[])
{
    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

void toLowerCase(char str[])
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

void scrambleWord(char original[], char scrambled[])
{
    int length;
    int i;
    int j;
    char temp;

    strcpy(scrambled, original);

    length = strlen(scrambled);

    for (i = length - 1; i > 0; i--)
    {
        j = rand() % (i + 1);

        temp = scrambled[i];
        scrambled[i] = scrambled[j];
        scrambled[j] = temp;
    }

    if (length > 1 && strcmp(original, scrambled) == 0)
    {
        temp = scrambled[0];
        scrambled[0] = scrambled[1];
        scrambled[1] = temp;
    }
}

void displayInstructions()
{
    printf("\n====================================================\n");
    printf("              MINDCARE WORD SCRAMBLE\n");
    printf("====================================================\n");

    printf("\nPURPOSE:\n");
    printf("This game is designed as a cognitive training activity\n");
    printf("for word recognition, language processing, memory,\n");
    printf("problem-solving and mental flexibility.\n");

    printf("\nHOW TO PLAY:\n");
    printf("1. Select a difficulty level.\n");
    printf("2. Select a category.\n");
    printf("3. A scrambled word will appear.\n");
    printf("4. Type the correct word.\n");
    printf("5. You can use one hint during the game.\n");
    printf("6. Faster correct answers can receive a speed bonus.\n");
    printf("7. The game contains 5 rounds.\n");

    printf("\nIMPORTANT:\n");
    printf("This game is a cognitive training activity and is NOT\n");
    printf("a medical diagnostic test for Mild Cognitive Impairment.\n");

    printf("\n====================================================\n");
}

void displayDifficulty()
{
    printf("\nSelect Difficulty:\n");
    printf("------------------\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
}

int getDifficulty()
{
    int choice;

    while (1)
    {
        displayDifficulty();

        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter 1, 2 or 3.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (choice >= 1 && choice <= 3)
        {
            return choice;
        }

        printf("\nPlease select 1, 2 or 3.\n");
    }
}

void displayCategories()
{
    printf("\nSelect Category:\n");
    printf("----------------\n");
    printf("1. Animals\n");
    printf("2. Food\n");
    printf("3. Objects\n");
    printf("4. Places\n");
}

int getCategory()
{
    int choice;

    while (1)
    {
        displayCategories();

        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter 1 to 4.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (choice >= 1 && choice <= 4)
        {
            return choice;
        }

        printf("\nPlease select a number from 1 to 4.\n");
    }
}

void getWordFromCategory(
    int category,
    int difficulty,
    char selectedWord[],
    int usedIndices[]
)
{
    Word *list;
    int validIndices[WORDS_PER_CATEGORY];
    int validCount = 0;
    int i;
    int randomIndex;

    if (category == 1)
        list = animals;
    else if (category == 2)
        list = food;
    else if (category == 3)
        list = objects;
    else
        list = places;

    for (i = 0; i < WORDS_PER_CATEGORY; i++)
    {
        if (list[i].difficulty == difficulty &&
            usedIndices[i] == 0)
        {
            validIndices[validCount] = i;
            validCount++;
        }
    }

    if (validCount == 0)
    {
        for (i = 0; i < WORDS_PER_CATEGORY; i++)
        {
            if (usedIndices[i] == 0)
            {
                validIndices[validCount] = i;
                validCount++;
            }
        }
    }

    randomIndex = validIndices[rand() % validCount];

    usedIndices[randomIndex] = 1;

    strcpy(selectedWord, list[randomIndex].word);
}

int calculateBaseScore(int difficulty)
{
    if (difficulty == 1)
        return 100;

    if (difficulty == 2)
        return 150;

    return 200;
}

int calculateSpeedBonus(double timeTaken)
{
    if (timeTaken <= 3.0)
        return 50;

    if (timeTaken <= 6.0)
        return 30;

    if (timeTaken <= 10.0)
        return 15;

    return 0;
}

void giveHint(char word[], char hint[])
{
    int length;
    int i;

    length = strlen(word);

    for (i = 0; i < length; i++)
    {
        if (i == 0 || i == length - 1)
        {
            hint[i] = word[i];
        }
        else
        {
            hint[i] = '_';
        }
    }

    hint[length] = '\0';
}

void displayFinalResult(
    int score,
    int correct,
    int total,
    int hintsUsed,
    double totalTime
)
{
    double accuracy;
    double averageTime;

    accuracy = ((double)correct / total) * 100.0;
    averageTime = totalTime / total;

    printf("\n\n====================================================\n");
    printf("                  FINAL PERFORMANCE\n");
    printf("====================================================\n");

    printf("\nTotal Score       : %d\n", score);
    printf("Correct Answers   : %d / %d\n", correct, total);
    printf("Accuracy          : %.2f%%\n", accuracy);
    printf("Hints Used        : %d\n", hintsUsed);
    printf("Total Time        : %.2f seconds\n", totalTime);
    printf("Average Response  : %.2f seconds\n", averageTime);

    printf("\n====================================================\n");

    if (accuracy == 100)
    {
        printf("Excellent! All answers were correct.\n");
    }
    else if (accuracy >= 60)
    {
        printf("Good work! Keep practicing.\n");
    }
    else
    {
        printf("Keep practicing and try again.\n");
    }

    printf("\nNOTE:\n");
    printf("The score is a game performance measure only.\n");
    printf("It should not be used to diagnose or rule out\n");
    printf("Mild Cognitive Impairment or any medical condition.\n");

    printf("\n====================================================\n");
}

int main()
{
    int difficulty;
    int category;

    int score = 0;
    int correctAnswers = 0;
    int hintsUsed = 0;

    int round;

    double totalTime = 0.0;

    char selectedWord[MAX_WORD_LENGTH];
    char scrambledWord[MAX_WORD_LENGTH];
    char answer[MAX_WORD_LENGTH];
    char hint[MAX_WORD_LENGTH];

    int usedAnimals[WORDS_PER_CATEGORY] = {0};
    int usedFood[WORDS_PER_CATEGORY] = {0};
    int usedObjects[WORDS_PER_CATEGORY] = {0};
    int usedPlaces[WORDS_PER_CATEGORY] = {0};

    int *usedIndices;

    char playAgain;

    static int personalBest = 0;

    srand((unsigned int)time(NULL));

    printf("\n\n");
    printf("====================================================\n");
    printf("                  MINDCARE PROJECT\n");
    printf("                WORD SCRAMBLE GAME\n");
    printf("====================================================\n");

    displayInstructions();

    printf("\nPress ENTER to continue...");
    getchar();

    difficulty = getDifficulty();

    category = getCategory();

    if (category == 1)
        usedIndices = usedAnimals;
    else if (category == 2)
        usedIndices = usedFood;
    else if (category == 3)
        usedIndices = usedObjects;
    else
        usedIndices = usedPlaces;

    for (round = 1; round <= TOTAL_ROUNDS; round++)
    {
        int baseScore;
        int speedBonus;
        int roundScore;

        clock_t startTime;
        clock_t endTime;

        double responseTime;

        printf("\n\n====================================================\n");
        printf("                     ROUND %d OF %d\n",
               round, TOTAL_ROUNDS);
        printf("====================================================\n");

        getWordFromCategory(
            category,
            difficulty,
            selectedWord,
            usedIndices
        );

        scrambleWord(selectedWord, scrambledWord);

        printf("\nUnscrambled word has %lu letters.\n",
               (unsigned long)strlen(selectedWord));

        printf("\nSCRAMBLED WORD:\n");
        printf("\n        >>> %s <<<\n", scrambledWord);

        printf("\nYou have ONE hint available for the game.\n");
        printf("Enter H if you want to use the hint.\n");
        printf("Otherwise enter your answer.\n");

        startTime = clock();

        printf("\nYour answer: ");
        fgets(answer, sizeof(answer), stdin);
        removeNewline(answer);

        if (answer[0] == 'h' ||
            answer[0] == 'H')
        {
            if (hintsUsed == 0)
            {
                hintsUsed = 1;

                giveHint(selectedWord, hint);

                printf("\nHINT: %s\n", hint);

                printf("\nYour answer: ");
                fgets(answer, sizeof(answer), stdin);
                removeNewline(answer);
            }
            else
            {
                printf("\nYou have already used your hint.\n");

                printf("\nYour answer: ");
                fgets(answer, sizeof(answer), stdin);
                removeNewline(answer);
            }
        }

        endTime = clock();

        responseTime =
            ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

        totalTime += responseTime;

        toLowerCase(answer);

        printf("\nResponse Time: %.2f seconds\n", responseTime);

        if (strcmp(answer, selectedWord) == 0)
        {
            baseScore = calculateBaseScore(difficulty);
            speedBonus = calculateSpeedBonus(responseTime);

            roundScore = baseScore + speedBonus;

            if (hintsUsed == 1)
            {
            }

            printf("\nCORRECT!\n");
            printf("Base Score  : %d\n", baseScore);
            printf("Speed Bonus : %d\n", speedBonus);

            if (strchr(answer, '\0') != NULL)
            {
            }

            score += roundScore;
            correctAnswers++;

            printf("Round Score : %d\n", roundScore);
        }
        else
        {
            printf("\nINCORRECT.\n");
            printf("Correct Answer: %s\n", selectedWord);
            printf("Round Score: 0\n");
        }

        printf("\nPress ENTER for the next round...");
        getchar();
    }

    displayFinalResult(
        score,
        correctAnswers,
        TOTAL_ROUNDS,
        hintsUsed,
        totalTime
    );

    if (score > personalBest)
    {
        personalBest = score;

        printf("\n*** NEW PERSONAL BEST! ***\n");
        printf("Personal Best: %d points\n", personalBest);
    }
    else
    {
        printf("\nPersonal Best: %d points\n", personalBest);
    }

    printf("\nWould you like to play again? (Y/N): ");
    scanf(" %c", &playAgain);
    clearInputBuffer();

    if (playAgain == 'Y' || playAgain == 'y')
    {
        printf("\nStarting a new game...\n");

        main();
        return 0;
    }

    printf("\nThank you for playing MindCare Word Scramble!\n");
    printf("\nPress ENTER to exit...");
    getchar();

    return 0;
}
