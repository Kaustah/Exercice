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

typedef struct {
	char nom_exercice[100];
	short nb_set_accompli;
	activity_measure interval[5]; //TODO: Voir Malloc pour reduire l'utilisation de memoire + ligne du dessous Code5
	float weight[5];
	exercice_template *template;

} exercice_sheet;

typedef struct {
	struct tm *tm;
	time_t starttime;//TODO: Creer fonction afin de retourner le format Date Heure en String pour insertion SQL
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

//Functions
void now(char *time_string);
int menu_main();
void print_exercice(exercice_template *temp_exercice);
void choixInterval(exercice_template *temp_exercice);
void cleanNewline(char *line);
void remplir_template();
int askquestion(char *question);
void createtemplate_loop();
int read_exercises(exercice_template *exercices);
void printtemplatelist(exercice_template *templates, int nb_exercises);
void menu_training(exercice_template *exercices);
void menu_exercises();
void menu_trainingday();


