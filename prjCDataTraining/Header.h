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
	short id; //TODO: Must add an ID, Update Adding exercice, Read_exercise (update index)
	char nom_exercice[100];
	short nb_set;
	short temps_recup;
	activity_measure quantity;
	type_measure measure;
	float weight;

} exercice_template;

//exercice_template default values
void exercice_template_default(exercice_template *exercice)
{
	exercice->id = NULL;
	exercice->nom_exercice[0] = NULL;
	exercice->nb_set = 0;
	exercice->temps_recup = 0;
	exercice->weight = 0;
	exercice->measure = 0;
}

typedef struct {
	short id;
	short exercise_count;
	char name[50];
	exercice_template *templates[10];//TODO: Code5
} training_program;	

void training_program_default(training_program *program)
{
	program->id = NULL;
	program->name[0] = NULL;
	program->templates[0] = NULL;
}

typedef struct {
	short nb_set_accompli;
	activity_measure quantity[5]; //TODO: Voir Malloc pour reduire l'utilisation de memoire Code5
	float weight[5];
	training_program *program;
} exercice_sheet;

typedef struct {
	struct tm *tm;
	time_t starttime;//TODO: Creer fonction afin de retourner le format Date Heure en String pour insertion SQL
	time_t endtime;
	float weight;
	training_program exercise_list;
} training_day;

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
void createtemplate_loop(exercice_template);
void read_exercises(exercice_template *exercices);
void printtemplatelist(exercice_template *templates);
void menu_training(exercice_template *exercices);
void menu_exercises(exercice_template *exercices);
void menu_trainingday();
void printExercise(exercice_template* exercise);
void deleteExercise(exercice_template* exercise);

