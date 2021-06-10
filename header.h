#ifndef HEADER_H
#define HEADER_H

typedef struct player {
	int id;
	char username[20];
	int score;
	int timeNedded;

}PLAYER;

void menu();
void boardDifficulty();
void boardGenerate();
int boardGuess(int);
void boardPrint(int, int, int);
void boardPrintBlank();
int boardMatch(int, int,int);
void finalBoard();
void endGame(int, int);
void win(int,int);
void writeFile(int,int);
void fileOpening();
void outputFile(PLAYER*);
void menuScores();
void deleteScores();
void deleteSpecificScore();
void sort(PLAYER*);
void change(int* const, int* const);
void* allocateArray();



#endif
