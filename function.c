#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>


int id = 0;
int mines = 0;

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

		difficulty();
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

void difficulty() {
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

		game8x8();
		break;

	case 2:

		game16x16();
		break;

	case 3:

		system("cls");
		menu();
		break;
	}
	

}

void game8x8() {
	int i, j, k;
	mines = 10;

	for (i = 0; i < 8; i++)
		printf("+---");
	printf("+\n");

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			printf("| . ");
		}
		printf("|\n");
		for (k = 0; k < 8; k++)
			printf("+---");

		printf("+\n");
	}

}



void game16x16() {

	int i, j, k;
	mines = 40;

	for (i = 0; i < 16; i++)
		printf("+---");
	printf("+\n");

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			printf("| . ");
		}
		printf("|\n");
		for (k = 0; k < 16; k++)
			printf("+---");

		printf("+\n");
	}
}