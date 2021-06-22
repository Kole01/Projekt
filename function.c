#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>




static int idbroj = 0;
int mines = 0;
int fieldUser[20][20];
int field[20][20];
int size = 0;
int debug = 1;
int scoreMultiplier = 1;



void menu() { // Izbornik
	system("cls");
	int choice;
	char exitCheck[3];
	int temp;

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
		system("cls");
		menuScores();
		break;

	case 3://Izlaz iz programa!
		printf("Zelite izaci(da/ne)?");
		do {
			scanf("%2s", exitCheck);
			if (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1) printf("\nUnos nije dobar\n");

		} while (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1);

		if (strcmp(exitCheck, "da") == 0) {
			temp = 0;

		}
		else temp = 1;

		switch (temp) {
		case 1:
			menu();
			break;
		case 0:
			exit(EXIT_FAILURE);
		}
	}

}

void boardDifficulty() {
	system("cls");
	int choice;
	int score=0, timeInSeconds;
	clock_t start, end, total;
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
		scoreMultiplier = 1;
		start = clock();
		boardGenerate();
		boardPrintBlank();
		if ( boardGuess(score)==1) {
			end = clock();
			total = end - start;
			timeInSeconds = total / CLOCKS_PER_SEC;
			finalBoard();
			endGame(score,timeInSeconds);
		}
		if (boardGuess(score) == 2) {
			end = clock();
			total = end - start;
			timeInSeconds = total / CLOCKS_PER_SEC;
			win(score,timeInSeconds);
			
		}

		break;

	case 2:
		scoreMultiplier = 2;
		size = 16;
		mines = 40;
		start = clock();
		boardGenerate();
		boardPrintBlank();
		if (boardGuess(score) == 1) {
			end = clock();
			total = end - start;
			timeInSeconds = total / CLOCKS_PER_SEC;
			finalBoard();
			endGame(score,timeInSeconds);
		}
		if (boardGuess(score) == 2) {
			end = clock();
			total = end - start;
			timeInSeconds = total / CLOCKS_PER_SEC;
			win(score, timeInSeconds);

		}

	case 3:

		system("cls");
		menu();
		break;
	}


}

void boardGenerate() {
	srand(time(NULL));

	int i, j;
	int minesCheck = 0;

	//Postavljanje praznog boarda
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			field[i][j] = 48;

		}
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			fieldUser[i][j] = 45;
		}
	}



	//Postavljanje mina
	do {

		i = rand() % size;
		j = rand() % size;
		if (field[i][j] == 66) {
			i = rand() % size;
			j = rand() % size;
		}
		else {
			field[i][j] = 66;

			minesCheck++;
		}


	} while (minesCheck != mines);


	//Postavljanje brojeva koji oznacuju broj mina oko njih
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (field[i][j] != 66)
			{
				field[i][j] = 48;
			}
			if ((field[i - 1][j - 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i - 1][j] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i][j - 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i - 1][j + 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i + 1][j - 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i + 1][j] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i][j + 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i + 1][j + 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}

		}
	}
}

int boardGuess(int score) {
	int x, y;
	int i, j;
	int match = 0;


	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (fieldUser[i][j] == field[i][j]) match++;
		}
	}
	if (match == (size * size) - mines) return 2;



	do { // korisnik odabire koje polje ce se pogledati!
		printf("\n");
		printf("Zadaj koordinatu x: ");
		scanf("%d", &x);

		printf("Zadaj koordinatu y: ");
		scanf("%d", &y);
		if (x < 0 || (x > size - 1) && y<0 || y>size - 1) printf("\nUnesena vrijednost nije ispravana, unesite valjane koordiante!");
	} while (x<0 || x>size - 1 && y<0 || y>size - 1);


	boardMatch(x, y,score);




}

int boardMatch(int x, int y, int score) {



	if (field[x][y] == 66) {
		fieldUser[x][y] = field[x][y];
		return 1;
		
	}
	if (fieldUser[x][y] != 45) {
		printf("Odabrali ste polje koje je vec otkriveno!");
		boardGuess(score);

	}
	else {
		fieldUser[x][y] = field[x][y];
		score += 10;
		if (field[x][y] == 48) {


			//polja iznad odabranog polja
			if (field[x - 1][y - 1] == field[x][y])
			{
				fieldUser[x - 1][y - 1] = field[x - 1][y - 1];
				score += 10;
			}
			if (field[x - 1][y] == field[x][y])
			{
				fieldUser[x - 1][y] = field[x - 1][y];
				score += 10;
			}
			if (field[x - 1][y + 1] == field[x][y])
			{
				fieldUser[x - 1][y + 1] = field[x - 1][y + 1];
				score += 10;
			}
			//polja u ravnini zadanog polja
			if (field[x][y - 1] == field[x][y])
			{
				fieldUser[x][y - 1] = field[x][y - 1];
				score += 10;
			}
			if (field[x][y + 1] == field[x][y])
			{
				fieldUser[x][y + 1] = field[x][y + 1];
				score += 10;
			}
			//polja ispod odabrnog polja 
			if (field[x + 1][y - 1] == field[x][y])
			{
				fieldUser[x + 1][y - 1] = field[x + 1][y - 1];
				score += 10;
			}
			if (field[x + 1][y] == field[x][y])
			{
				fieldUser[x + 1][y] = field[x + 1][y];
				score += 10;
			}
			if (field[x + 1][y + 1] == field[x][y])
			{
				fieldUser[x + 1][y + 1] = field[x + 1][y + 1];
				score += 10;
			}
		}
		boardPrint(x, y,score);
	}
}

void win(int score, int timeInSeconds) {
	char check[3];
	int temp;
	printf("Pobjeda!");
	score += timeInSeconds * 10;
	printf("Za igru vam je trebalo %d sekundi", timeInSeconds);
	writeFile(score,timeInSeconds);
	printf("\nZelite li odigrati jos jednu igru(da/ne)?");
	do {
		scanf("%2s", check);
		if (strcmp(check, "da") == 1 && strcmp(check, "ne") == 1) printf("\nUnos nije dobar\n");

	} while (strcmp(check, "da") == 1 && strcmp(check, "ne") == 1);

	if (strcmp(check, "da") == 0) {
		temp = 1;
	}
	else temp = 0;

	switch (temp) {
	case 1:
		boardDifficulty();
		break;
	case 0:
		exit(EXIT_FAILURE);
	}

}

void finalBoard() {
	int i = 0, j = 0, k = 0;
	printf("\n");
	system("cls");
	for (i = 0; i < size; i++) {

		if (i < 9)printf("    %d", i);
		else if (i == 9)printf("    %d ", i);
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
		printf("%d", i);
		if (i < 10)printf(" ");
		for (j = 0; j < size; j++)
		{
			
			if(field[i][j]==66)printf("|  %c ", field[i][j]);
			else printf("|  %c ", fieldUser[i][j]);
		}
		printf("|\n");
		printf("  ");
		for (k = 0; k < size; k++) {

			printf("+----");

		}


		printf("+\n");
	}
}

void boardPrint(int x, int y, int score) {
	int i = 0, j = 0, k = 0;
	int debugMines = 0;
	printf("\n");
	system("cls");
	if (debug == 1) {
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				if (field[i][j] == 66) {
					debugMines++;
					printf("%d. mina se nalazi na: %d,%d\n", debugMines, i, j);

				}
			}
		}
	}
	printf("\n");
	printf("\n");
	printf("\n");
	for (i = 0; i < size; i++) {

		if (i < 9)printf("    %d", i);
		else if (i == 9)printf("    %d ", i);
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
		printf("%d", i);
		if (i < 10)printf(" ");
		for (j = 0; j < size; j++)
		{
			printf("|  %c ", fieldUser[i][j]);

		}
		printf("|\n");
		printf("  ");
		for (k = 0; k < size; k++) {

			printf("+----");

		}


		printf("+\n");
	}
	boardGuess(score);
}

void boardPrintBlank() { //pritanje igre
	system("cls");
	int i = 0, j = 0, k = 0;
	printf("\n");

	for (i = 0; i < size; i++) {

		if (i < 9)printf("    %d", i);
		else if (i == 9)printf("    %d ", i);
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
		printf("%d", i);
		if (i < 10)printf(" ");
		for (j = 0; j < size; j++)
		{

			printf("|  - ");
		}
		printf("|\n");
		printf("  ");
		for (k = 0; k < size; k++) {

			printf("+----");

		}


		printf("+\n");
	}
}

void endGame(int score, int timeInSeconds) {

	char check[3];
	int temp;
	score += (timeInSeconds * 10);
	printf("\nZa igru vam je trebalo %d sekudni", timeInSeconds);
	printf("\nPolje koje ste odabrali sadrzava minu! Igra je zavrsena!");
	writeFile(score,timeInSeconds);
	printf("\nZelite li odigrati jos jednu igru(da/ne)?");
	do {
		scanf("%2s", check);
		if (strcmp(check, "da") == 1 && strcmp(check, "ne") == 1) printf("\nUnos nije dobar\n");

	} while (strcmp(check, "da") == 1 && strcmp(check, "ne") == 1);

	if (strcmp(check, "da") == 0) {
		temp = 1;
	}
	else temp = 0;

	switch (temp) {
	case 1:
		boardDifficulty();
		break;
	case 0:

		exit(EXIT_FAILURE);
	}


}

void menuScores() {
	system("cls");
	int choice;
	int proba1, proba2;
	PLAYER* userField;
	int temp;
	char exitCheck[3];

	//Printanje podizbornika!
	printf("\n");
	printf("Opcije s rezultatima:\n");
	printf("\n");
	printf("1. Ispisati 10 najboljih rezultata!\n");
	printf("2. Obrisati trazeni rezultat!\n");
	printf("3. Obrisati sve rezultate!\n");
	printf("4. Dodavanje vlastitog rezultata(debug)\n");
	printf("5. Nazad na glavni izbornik\n");
	printf("\n");

	//provjera unosa
	do {
		printf("Odaberite opciju:");
		scanf("%d", &choice);
		if (choice < 1 || choice>5) printf("Unos nije ispravan!");
	} while (choice < 1 || choice>5);

	// izbor!
	switch (choice) {
	case 1:
		userField = allocateArray();
		if (userField == NULL) {
			printf("\nJos nema ni jednog rezultata zelite li odigrati igru? (da/ne)");
			do {
				scanf("%2s", exitCheck);
				if (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1) printf("\nUnos nije dobar\n");

			} while (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1);

			if (strcmp(exitCheck, "da") == 0) {
				temp = 0;

			}
			else temp = 1;

			switch (temp) {
			case 0:
				boardDifficulty();
				break;
			case 1:
				exit(EXIT_FAILURE);
			}
		}
		userField = sort(userField);
		outputFile(userField);
		free(userField);
		exit(EXIT_FAILURE);

	case 2:
		userField = allocateArray();
		if (userField == NULL) {
			printf("\nJos nema ni jednog rezultata zelite li odigrati igru? (da/ne)");
			do {
				scanf("%2s", exitCheck);
				if (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1) printf("\nUnos nije dobar\n");

			} while (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1);

			if (strcmp(exitCheck, "da") == 0) {
				temp = 0;

			}
			else temp = 1;

			switch (temp) {
			case 0:
				boardDifficulty();
				break;
			case 1:
				exit(EXIT_FAILURE);
			}
		}
		userField = sort(userField);
		deleteSpecificScore(userField);
		free(userField);
		exit(EXIT_FAILURE);

	case 3:
		deleteScores();
		exit(EXIT_FAILURE);

	case 4:
		if (debug == 1) {
			printf("Unesite rezultat: ");
			scanf("%d", &proba1);
			printf("Unesite vrijeme: ");
			scanf("%d", &proba2);
			writeFile(proba1,proba2);
		}
		else {
			printf("Nemate dopustenja za odabiranje ove opcije!");
			menuScores();
		}
	case 5:

		system("cls");
		menu();
		break;
	}


}

void* allocateArray() {
	FILE* file = fopen("scores.bin", "rb");
	if (file == NULL) {
		perror("Datoteka scores.bin ne postoji!!");
		printf("Odigrajte barem jednu igru!");
		return NULL;
	}
	fread(&idbroj, sizeof(int), 1, file);
	printf("Broj Clanova: %d\n", idbroj);
	PLAYER* userField = (PLAYER*)calloc(idbroj, sizeof(PLAYER));
	if (userField == NULL) {
		perror("Zauzimanje memorije za polje rezultata");
		return NULL;
	}
	fread(userField, sizeof(PLAYER), idbroj, file);
	return userField;
	
}

void fileOpening() {
	FILE* file = fopen("scores.bin", "ab+");
	fwrite(&idbroj, sizeof(int), 1, file);
	if (file == NULL) {
		perror("Kreiranje datoteke clanovi.bin");
		exit(EXIT_FAILURE);
	}
	fclose(file);
}

void writeFile(int score, int timeInSeconds) {
	fileOpening();
	FILE* file = fopen("scores.bin", "rb+");
	if (file == NULL) {
		perror("Dodavanje scora u scores.bin");
		exit(EXIT_FAILURE);
	}
	fread(&idbroj, sizeof(int), 1, file);
	PLAYER temp = {0};
	
	
	//printf("\nBroj unesenih rezultata je %d", idbroj);
	temp.id = idbroj;
	printf("\nUnesite username: ");
	scanf("%19s", temp.username);
	temp.score = score * scoreMultiplier;
	temp.timeNedded = timeInSeconds;
	fseek(file, sizeof(PLAYER) * idbroj, SEEK_CUR);
	fwrite(&temp, sizeof(PLAYER), 1, file);
	rewind(file);
	idbroj++;
	fwrite(&idbroj, sizeof(int), 1, file);
	fclose(file);
}

void outputFile(PLAYER* userField) {
	system("cls");
	char exitCheck[3];
	int temp;
	int i;
	if (userField == NULL) {
		printf("Polje je prazno!\n");
		return;
	}
	else {
		if (idbroj > 10) {
			for (i = 0; i < 10; i++) {
				printf("ID: %d\tUsername: %s\tScore: %d\tVrijeme igrano: %d sekunde\n", (userField + i)->id, (userField + i)->username, (userField + i)->score, (userField + i)->timeNedded);
				
			}
			printf("\n");
			printf("\nZelite li dabrati neu drugu opciju(da/ne)? ");
			do {
				scanf("%2s", exitCheck);
				if (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1) printf("\nUnos nije dobar\n");

			} while (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1);

			if (strcmp(exitCheck, "da") == 0) {
				temp = 0;

			}
			else temp = 1;

			switch (temp) {
			case 1:
				menuScores();
				break;
			case 0:
				exit(EXIT_FAILURE);
			}
		}
		if (idbroj < 10) {
			for (i = 0; i < idbroj; i++) {
				printf("ID: %d\tUsername: %s\tScore: %d\tVrijeme igrano: %d sekunde\n", (userField + i)->id, (userField + i)->username, (userField + i)->score, (userField + i)->timeNedded);
			}
			printf("\n");
			printf("\nZelite li dabrati neu drugu opciju(da/ne)?");
			do {
				scanf("%2s", exitCheck);
				if (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1) printf("\nUnos nije dobar\n");

			} while (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1);

			if (strcmp(exitCheck, "da") == 0) {
				temp = 0;

			}
			else temp = 1;

			switch (temp) {
			case 0:
				menuScores();
				break;
			case 1:
				exit(EXIT_FAILURE);
			}
		}
	}
	
	
}

void deleteSpecificScore(PLAYER* userField) {
	system("cls");
	FILE* pF = fopen("scores.bin", "wb");
	if (pF == NULL) {
		perror("Brisanje studenta iz datoteke studenti.bin");
		exit(EXIT_FAILURE);
	}

	int i;
	int temp;
	int trazeni_id;
	char exitCheck[3];
	PLAYER* deleteScore = (PLAYER*)calloc(1, sizeof(PLAYER));
	
	if (userField == NULL) {
		printf("Polje je prazno!");
		return;
	}
	else {
		for (i = 0; i < idbroj; i++) {
			printf("ID: %d\tUsername: %s\tScore: %d\tVrijeme igrano: %d sekunde\n", (userField + i)->id, (userField + i)->username, (userField + i)->score, (userField + i)->timeNedded);
		}

		do {
			printf("Unesite ID koji zelite obrisati: ");
			scanf("%d", &trazeni_id);
		} while (trazeni_id > idbroj);
		for (i = 0; i < idbroj; i++) {
			if (trazeni_id == (userField + i)->id) {
				deleteScore = (userField + i);
				printf("Rezultat je pronaden: \n");
				printf("ID: %d\tUsername: %s\tScore: %d\tVrijeme igrano: %d sekunde\n", (userField + i)->id, (userField + i)->username, (userField + i)->score, (userField + i)->timeNedded);
				printf("Zelite li obrisati ovaj rezultat?");
				do {
					scanf("%2s", exitCheck);
					if (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1) printf("\nUnos nije dobar\n");

				} while (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1);

				if (strcmp(exitCheck, "da") == 0) {
					temp = 0;

				}
				else temp = 1;

				switch (temp) {
				case 1:
					menuScores();
				case 0:

					fseek(pF, sizeof(int), SEEK_SET);
					int i;
					int newID = 0;
					for (i = 0; i < idbroj; i++)
					{
						if (deleteScore != (userField + i)) {
							fwrite((userField + i), sizeof(PLAYER), 1, pF);
							newID++;
						}
					}
					rewind(pF);
					fwrite(&newID, sizeof(int), 1, pF);
					fclose(pF);
					printf("Rezultat je obrisan!\n");
					deleteScore = NULL;
				}
			}

		}
		free(deleteScore);
	}
	
}

void deleteScores() {
	printf("Zelite li uistinu obrisati rezultate?\n");
	char potvrda[3] = { '\0' };
	scanf("%2s", potvrda);
	if (!strcmp("da", potvrda)) {
		remove("scores.bin") == 0 ? printf("Rezultati su obrisani!\n") : printf("Neuspjesno brisanje reezultata!\n");
	}
}

PLAYER* sort(PLAYER* userField) {

	PLAYER* temp1 = (PLAYER*)calloc(1, sizeof(PLAYER));
	int br = idbroj;
	if (temp1 == NULL) {
		perror("Zauzimanje memorije za temp");
		return NULL;
	}

	int i, j;
	
	for (i = 0; i < br - 1; i++)
	{
		for (j = 0; j < (br - 1 - i); j++)
		{
			if ((userField+j)->score < (userField + j+1)->score)
			{
				*temp1 = *(userField + j);
				*(userField + j) = *(userField + j + 1);
				*(userField + j + 1) = *temp1;
			}
		}
	}
	
	return userField;
}
