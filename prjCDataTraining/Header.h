#pragma once
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef union {
	short nb_repetition;
	short duree;

} activity_measure;

typedef enum {
	REPETITION, DUREE
}type_measure;

typedef struct {
	char nom_exercice[100];
	short nb_set;
	short temps_recup;
	activity_measure quantity;
	type_measure measure;
	float weight;

} exercice_template;

//Struct default values
exercice_template exercice_template_default(exercice_template *exercice)
{
	exercice->nom_exercice[0] = NULL;
	exercice->nb_set = 0;
	exercice->temps_recup = 0;
	exercice->weight = 0;
	exercice->measure = 0;
}

typedef struct {
	char nom_exercice[100];
	short nb_set_accompli;
	activity_measure interval[5]; //TODO: Voir Malloc pour reduire l'utilisation de memoire + ligne du dessous Code5
	float weight[5];
	exercice_template *template;

} exercice_sheet;

typedef struct {
	char nom[50];
	exercice_sheet sheet_exercice[10];//TODO: Code5
} journee_template;

typedef struct {
	struct tm *tm;
	time_t starttime;//TODO: Creer fonction afin de retourner le format Date Heure en String pour insertion SQL
	time_t endtime;
	float weight;
	journee_template exercise_list;
} journee_training;

char* concat(const char *s1, const char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	// in real code you would check for errors in malloc here
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

//Function signatures
void now(char *time_string);
int menu_main();
void fprint_exercice(exercice_template *temp_exercice, FILE *ptrTemplate);
void choixInterval(exercice_template *temp_exercice);
void cleanNewline(char *line);
exercice_template remplir_template();
int askquestion(char *question);
void createtemplate_loop();
void read_exercises(exercice_template *exercices);
void printtemplatelist(exercice_template *templates);
void menu_training(exercice_template *exercices);
void menu_exercises(exercice_template *exercices);
void menu_trainingday();


