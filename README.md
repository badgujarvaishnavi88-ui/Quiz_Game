# C Quiz Challenge

A simple command-line quiz game written in C. Answer five multiple-choice questions about C programming, then view the leaderboard.

## Features

- Five multiple-choice questions
- Input validation for menu and quiz answers
- Scores saved to `leaderboard.txt`
- Displays the top five scores

## Requirements

- A C compiler, such as GCC
- A terminal or command prompt

## Compile

From the project folder, run:

```bash
gcc quiz.c -o quiz


On Windows with MinGW, you can also name the executable quiz.exe:
gcc quiz.c -o quiz.exe

Run
On Windows PowerShell:
.\quiz.exe

On macOS or Linux:
./quiz


How to Play
1. Choose 1 to play the quiz.
2. Enter your name without spaces.
3. Answer each question by entering a number from 1 to 4.
4. Choose 2 from the menu to view the leaderboard.
5. Choose 3 to exit.
Each correct answer earns one point. Your score is saved in leaderboard.txt when the quiz ends.
Project Files
- quiz.c — quiz game source code
- leaderboard.txt — score records, created when a score is saved
- quiz.exe — compiled Windows executable (if included)
Notes
- Player names must not contain spaces.
- The leaderboard displays up to five highest scores from the first 100 records it reads.
