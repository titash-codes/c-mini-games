#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void clearScreen() {
    system("cls");
}

int getRandomNumber(int diff) {
    if (diff == 1) {
        return (rand() % 50) + 1;
    } else if (diff == 2) {
        return (rand() % 450) + 50;
    } else {
        return (rand() % 9000) + 1000;
    }
}

int main() {
    int choice;
    int personalBest = 0;

    srand((unsigned int)time(NULL));

    while (1) {
        clearScreen();
        printf("========================================\n");
        printf("               MINDCARE                 \n");
        printf("========================================\n");
        printf("1. Odd-Even Sorting Game\n");
        printf("2. Exit\n");
        printf("----------------------------------------\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        if (choice == 2) {
            break;
        }

        if (choice == 1) {
            int difficulty = 0;
            int round = 0;
            int totalScore = 0;
            int correctAnswers = 0;
            int speedBonusTotal = 0;
            double totalResponseTime = 0.0;

            clearScreen();
            printf("========================================\n");
            printf("           SELECT DIFFICULTY            \n");
            printf("========================================\n");
            printf("1. Easy   (Numbers 1 - 50)\n");
            printf("2. Medium (Numbers 50 - 500)\n");
            printf("3. Hard   (Numbers 1000 - 9999)\n");
            printf("----------------------------------------\n");
            printf("Choice: ");
            scanf("%d", &difficulty);

            if (difficulty < 1 || difficulty > 3) {
                difficulty = 1;
            }

            for (round = 1; round <= 10; round++) {
                int number = getRandomNumber(difficulty);
                int expected = (number % 2 == 0) ? 2 : 1;
                int playerChoice = 0;
                time_t startTime, endTime;
                double elapsed;

                clearScreen();
                printf("========================================\n");
                printf("Round %d / 10\n", round);
                printf("========================================\n\n");
                printf("          NUMBER: [ %d ]\n\n", number);
                printf("----------------------------------------\n");
                printf("1. ODD\n");
                printf("2. EVEN\n");
                printf("Select (1 or 2): ");

                startTime = time(NULL);
                scanf("%d", &playerChoice);
                endTime = time(NULL);

                elapsed = difftime(endTime, startTime);
                totalResponseTime += elapsed;

                if (playerChoice == expected) {
                    int pts = 100;
                    int bonus = 0;

                    if (elapsed <= 2.0) {
                        bonus = 50;
                    } else if (elapsed <= 4.0) {
                        bonus = 20;
                    }

                    totalScore += (pts + bonus);
                    speedBonusTotal += bonus;
                    correctAnswers++;

                    printf("\nResult: CORRECT!\n");
                    if (bonus > 0) {
                        printf("Speed Bonus: +%d points! (Time: %.1f sec)\n", bonus, elapsed);
                    } else {
                        printf("Time taken: %.1f sec\n", elapsed);
                    }
                } else {
                    printf("\nResult: INCORRECT!\n");
                    printf("Time taken: %.1f sec\n", elapsed);
                }

                printf("\nPress any key for next round...");
                getch();
            }

            clearScreen();
            {
                double accuracy = ((double)correctAnswers / 10.0) * 100.0;
                double avgTime = totalResponseTime / 10.0;

                printf("========================================\n");
                printf("           FINAL PERFORMANCE            \n");
                printf("========================================\n");
                printf("Total Score        : %d\n", totalScore);
                printf("Correct Answers    : %d / 10\n", correctAnswers);
                printf("Accuracy           : %.1f%%\n", accuracy);
                printf("Avg Response Time  : %.2f sec\n", avgTime);
                printf("Speed Bonus Earned : %d\n", speedBonusTotal);
                printf("----------------------------------------\n");

                if (totalScore > personalBest) {
                    printf("NEW PERSONAL BEST! Old Best: %d\n", personalBest);
                    personalBest = totalScore;
                } else {
                    printf("Personal Best      : %d\n", personalBest);
                }
                printf("========================================\n\n");
                printf("Press any key to return to main menu...");
                getch();
            }
        }
    }

    return 0;
}
