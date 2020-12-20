#pragma once
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef union {
	short nb_repetition;
	time_t duree; //TODO: A voir et comprendre comment manipuler le temps en C. Adapter en consequence

} interval_duree;

typedef struct { //TODO: A voir pour merge avec struct: exercice_sheet
	char nom_exercice[100];
	short nb_set;
	time_t temps_recup;
	interval_duree interval; //TODO:A voir pour le nom de la variable
	float weight;

} exercice_template;

typedef struct {
	char nom_exercice[100];
	short nb_set_accompli;
	interval_duree interval[5]; //TODO: Voir Malloc pour reduire l'utilisation de memoire + ligne du dessous Code5
	float weight[5];

} exercice_sheet;

typedef struct {
	struct tm *tm; //TODO: A voir et comprendre comment manipuler le temps en C. Adapter en consequence//Date
	time_t starttime;
	time_t endtime;
	exercice_template type_exercice[10];	//TODO: Code5
	exercice_sheet sheet_exercice[10];		//TODO: Code5

} journee_entrainement;

char* concat(const char *s1, const char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	// in real code you would check for errors in malloc here
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}