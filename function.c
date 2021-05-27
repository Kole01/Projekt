#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>


int id = 0;
int mines = 0;
int fieldUser[20][20];
int field[20][20];
int size=0;


void menu() { // Izbornik

	int choice;
	char exitCheck[3];

	//Printanje izbornika!
	printf("\n");
	printf("\n\t\tOdaberite jednu od opcija:");
	printf("\n");
	printf("\n\t\t1. Nova igra!");
	printf("\n\t\t2. Najbolji rezultati!");
	printf("\n\t\t3. Izlazak iz igre!");
	printf("\n");

	// Provjera unosa izbora!
	do {
		printf("\nOdaberite opciju :");
		scanf("%d", &choice);
		if (choice < 1 || choice>3) printf("Ta opcija ne postoji!");
	} while (choice < 1 || choice>3);

	//Odabir opcija!
	switch (choice) {
	case 1:

		boardDifficulty();
		break;

	case 2:

		break;

	case 3://Izlaz iz programa!
		
		//provjera izlaza!
		do {
			printf("\nZelite izaci?(da/ne):");
			scanf("%s", exitCheck);
			
			if (strcmp(exitCheck, "da")== 1 && strcmp(exitCheck, "ne") == 1) printf("Unos nije tocan pokusajte opet!");
		} while (strcmp(exitCheck, "ne") == 1 && strcmp(exitCheck, "da") == 1);

		//provjera odabrane opcije!
		if (strcmp(exitCheck, "da") == 0) break;
		if (strcmp(exitCheck, "ne") == 0) {
			system("cls");
			menu();
			break;

		}
	}

}

void boardDifficulty() {
	system("cls");
	int choice;
	//Printanje podizbornika!
	printf("\n");
	printf("\nOdaberite tezinu igre!\n");
	printf("1. Polje velicine 8x8 i 10 mina!\n");
	printf("2. Polje velicine 16x16 i 40 mina!\n");
	printf("3. Nazad na glavni izbornik\n");
	printf("\n");

	//provjera unosa
	do {
		printf("Odaberite opciju:");
		scanf("%d", &choice);
		if (choice < 1 || choice>3) printf("Unos nije ispravan!");
	} while (choice < 1 || choice>3);

	// izbor!
	switch (choice) {
	case 1:

		mines = 10;
		size = 8;
		boardGenerate();
		boardPrint();
		break;

	case 2:
		size = 16;
		mines = 40;
		
		boardGenerate();
		boardPrint();
		break;

	case 3:

		system("cls");
		menu();
		break;
	}
	

}


void boardGenerate() {

	srand(time(NULL));
	int randomNumber;
	int i, j;
	int minesCheck=0;
	int minesNumber;
	//Postavljanje mina na mjesta u polju, oznacena brojem 99
	do {
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				randomNumber = rand() % 101;
				if (randomNumber < 8) {
					field[i][j] = 99;
					minesCheck++;
				}

			}
		}

	} while (minesCheck != mines);


	//Postavljanje brojeva koji oznacuju broj mina oko njih
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			minesNumber = 0;
			if (field[i][j] == 99) {
				
			}
			else {
				if (i == 0 && j == 0) {
					if (field[i][j + 1] == 99)minesNumber++;
					if (field[i + 1][j] == 99)minesNumber++;
					if (field[i + 1][j + 1] == 99)minesNumber++;
					field[i][j] = minesNumber;
				}
				if (i == 0 && j > 0) {
					if (field[i][j-1] == 99)minesNumber++;
					if (field[i][j+1] == 99)minesNumber++;
					if (field[i+1][j] == 99)minesNumber++;
					if (field[i+1][j-1] == 99)minesNumber++;
					if (field[i+1][j+1] == 99)minesNumber++;
					field[i][j] = minesNumber;
				}
				if (j == 0 && i >0) {
					if (field[i-1][j] == 99)minesNumber++;
					if (field[i+1][j] ==99)minesNumber++;
					if (field[i][j+1] == 99)minesNumber++;
					if (field[i-1][j+1] == 99)minesNumber++;
					if (field[i+1][j+1] == 99)minesNumber++;
					field[i][j] = minesNumber;
				}
				if(i<size-1 && j<size-1) {
					if (field[i-1][j-1] == 99)minesNumber++;
					if (field[i-1][j] == 99)minesNumber++;
					if (field[i-1][j+1] == 99)minesNumber++;
					if (field[i][j-1] == 99)minesNumber++;
					if (field[i][j+1] == 99)minesNumber++;
					if (field[i+1][j-1] == 99)minesNumber++;
					if (field[i+1][j] == 99)minesNumber++;
					if (field[i+1][j+1] == 99)minesNumber++;
					field[i][j] = minesNumber;
				}
				if (i == size - 1 && j < size - 1) {
					if (field[i-1][j] == 99)minesNumber++;
					if (field[i-1][j-1] == 99)minesNumber++;
					if (field[i-1][j+1] == 99)minesNumber++;
					if (field[i][j-1] == 99)minesNumber++;
					if (field[i][j+1] == 99)minesNumber++;
					field[i][j] = minesNumber;
				}
				if (i < size - 1 && j == size - 1) {
					if (field[i-1][j] == 99)minesNumber++;
					if (field[i-1][j-1] == 99)minesNumber++;
					if (field[i][j-1] == 99)minesNumber++;
					if (field[i+1][j-1] == 99)minesNumber++;
					if (field[i+1][j] == 99)minesNumber++;
					field[i][j] = minesNumber;
					//if (field[i][j] == 99)minesNumber++;
				}
				if (i == size - 1 && j == size - 1) {
					if (field[i-1][j-1] == 99)minesNumber++;
					if (field[i][j-1] == 99)minesNumber++;
					if (field[i-1][j] == 99)minesNumber++;
					field[i][j] = minesNumber;
				}
			}
		}
	}
}

void boardGuess() {
	int x, y;
	do { // korisnik odabire koje polje ce se pogledati!
		printf("Zadaj koordinatu x: ");
		scanf("%d", &x);
		printf("Zadaj koordinatu y: ");
		scanf("%d", &y);
		if (field[x][y] == 99) {
			printf("Odabrali ste polje s minom!");
			break;	// Umetnit funckiju koja prati score i upisuje ga u datoteku!
		}

	} while (field[x][y] != 99);
	


}

void boardPrint() { //pritanje igre
	int i=0, j=0, k=0;
	printf("\n");
	
	for (i = 0; i < size; i++) {
		
		if(i<9)printf("    %d", i);
		else if(i==9)printf("    %d ", i);
		else printf("   %d", i);
		

	}
	printf("\n");
	printf("  ");
	for (i = 0; i < size; i++) {
		
		printf("+----");
	}
	printf("+\n");

	for (i = 0; i < size; i++)
	{
		printf("%d",i);
		if (i < 10)printf(" ");
		for (j = 0; j < size; j++)
		{
			
			printf("| .. ");
		}
		printf("|\n");
		printf("  ");
		for (k = 0; k < size; k++) {
			
			printf("+----");

		}
			

		printf("+\n");
	}
	

}



