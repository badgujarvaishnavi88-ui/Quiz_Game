#include <stdio.h>
#include <string.h>

#define NUM_Q 5
#define MAX_SCORES 100
#define FILE_NAME "leaderboard.txt"

struct Question {
    char text[100];
    char options[4][40];
    int answer;           
};

struct Player {
    char name[30];
    int score;
};

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readChoice(int low, int high) {
    int choice;
    while (1) {
        if (scanf("%d", &choice) == 1 && choice >= low && choice <= high) {
            clearBuffer();
            return choice;
        }
        clearBuffer();
        printf("Please enter a number from %d to %d: ", low, high);
    }
}

void saveScore(const char *name, int score) {
    FILE *fp = fopen(FILE_NAME, "a");
    if (fp == NULL) {
        printf("Could not save your score.\n");
        return;
    }
    fprintf(fp, "%s %d\n", name, score);
    fclose(fp);
}

int playQuiz(struct Question q[]) {
    int score = 0;

    for (int i = 0; i < NUM_Q; i++) {
        printf("\nQ%d. %s\n", i + 1, q[i].text);
        for (int j = 0; j < 4; j++) {
            printf("   %d) %s\n", j + 1, q[i].options[j]);
        }
        printf("Your answer: ");
        int choice = readChoice(1, 4);

        if (choice == q[i].answer) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong. The right answer was: %s\n", q[i].options[q[i].answer - 1]);
        }
    }
    return score;
}

void showLeaderboard() {
    struct Player list[MAX_SCORES];
    int count = 0;

    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("\nNo scores yet. Be the first to play!\n");
        return;
    }
    while (count < MAX_SCORES && fscanf(fp, "%29s %d", list[count].name, &list[count].score) == 2) {
        count++;
    }
    fclose(fp);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (list[j].score < list[j + 1].score) {
                struct Player temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    printf("\n===== TOP 5 LEADERBOARD =====\n");
    for (int i = 0; i < count && i < 5; i++) {
        printf("%d. %-15s %d/%d\n", i + 1, list[i].name, list[i].score, NUM_Q);
    }
}

int main() {
    struct Question questions[NUM_Q] = {
        {"Which symbol is used to get the address of a variable in C?",
         {"*", "&", "#", "%"}, 2},
        {"Which loop runs at least once, even if the condition is false?",
         {"for", "while", "do-while", "foreach"}, 3},
        {"What is the index of the first element in a C array?",
         {"0", "1", "-1", "Depends"}, 1},
        {"Which function is used to open a file in C?",
         {"open()", "fopen()", "file()", "start()"}, 2},
        {"What does 'break' do inside a loop?",
         {"Skips one round", "Restarts the loop", "Exits the loop", "Ends the program"}, 3}
    };

    char name[30];
    int choice;

    printf("=== C QUIZ CHALLENGE ===\n");

    while (1) {
        printf("\n1. Play Quiz\n2. View Leaderboard\n3. Exit\nChoose: ");
        choice = readChoice(1, 3);

        if (choice == 1) {
            printf("Enter your name (no spaces): ");
            scanf("%29s", name);
            clearBuffer();

            int score = playQuiz(questions);
            printf("\n%s, you scored %d out of %d!\n", name, score, NUM_Q);
            saveScore(name, score);
        } else if (choice == 2) {
            showLeaderboard();
        } else {
            printf("Thanks for playing. Goodbye!\n");
            break;
        }
    }
    return 0;
}
