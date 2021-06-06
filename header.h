#ifndef HEADER_H
#define HEADER_H

typedef struct player {
	int id;
	char username[20];
	int score;
	float time;

}PLAYER;

void menu();
void boardDifficulty();
void boardGenerate();
void boardGuess();
void boardPrint(int, int);
void boardPrintBlank();
void boardMatch(int, int);
void finalBoard();
void endGame();
void boardMine();
void win();
void writeFile();
void fileOpening();
void outputFile();
void menuScores();
void loadFile();
void deleteScores();
void deleteSpecificScore();
void sort();
void change();



#endif
