#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Header.h"


//Receives ptrChar and modifies it as: (SQL format) "2020-12-25" 
void now(char *time_string)
{
	time_t t;
	struct tm *time_struct;
	time(&t);
	time_struct = localtime(&t);

	sprintf(time_string, "%i-%i-%i", 
		(time_struct->tm_year +1900),	//Year + Epoch
		(time_struct->tm_mon +1),		//Month + Epoch
		time_struct->tm_mday);			//Day
}

//Function to welcome user, get date(entered or auto), choose program day 
void welcome_screen(char *current_time)
{
	now(current_time);

	puts("Programme initialisé. \n\n Veuillez entrer la date de l'entrainement. (Pour saisi automatique, Enter)");
	
}

void print_exercice(exercice_template *temp_exercice)
{
	FILE *ptrTemplate = fopen("Templates_Exercice.csv", "w");

	if (temp_exercice->type_interval == 1)
	{
		fprintf(ptrTemplate, "'repetition','%s',%hu,%hu,%hu,%.2f\n",	temp_exercice->nom_exercice,
																		temp_exercice->nb_set,
																		temp_exercice->temps_recup,
																		temp_exercice->interval.nb_repetition,
																		temp_exercice->weight);
	}
	else if (temp_exercice->type_interval == 2)
	{
		fprintf(ptrTemplate, "'duree','%s',%hu,%hu,%hu,%.2f\n",	temp_exercice->nom_exercice,
																temp_exercice->nb_set,
																temp_exercice->temps_recup,
																temp_exercice->interval.duree,
																temp_exercice->weight);
		
	}
	
}

void choixInterval(exercice_template *temp_exercice)
{
	int choix = 0;

	while ((choix < 1) || (choix > 2))
	{
		printf("\nL'intervalle est-elle un nombre de repetitions ou une duree?\t1- Repetition\t2-Duree\n");
		scanf("%i", &choix);
	}

	//Type_interval 1 == Repetitions, Type_interval 2== Duree
	switch (choix)
	{
	case 1:
		temp_exercice->type_interval = 1;
		printf("\nEntrer le nombre de repetition: ");
		scanf("%hu", &temp_exercice->interval.nb_repetition);
		break;
	case 2:
		temp_exercice->type_interval = 2;
		printf("\nEntrer la duree: ");
		scanf("%hu", &temp_exercice->interval.duree);
		break;
	}

}

void cleanNewline(char *line)
{
	int i = strlen(line);
	line[i - 1] = '\0';
}

void remplir_template()
{
	exercice_template temp_exercice;

	printf("\nQuel est le nom de votre exercice (100char max): ");
	fgets(temp_exercice.nom_exercice, 100, stdin);	/*Retirer '\n'*/ cleanNewline(&temp_exercice.nom_exercice);
	printf("\nEntrer le nombre de sets: ");
	scanf("%hu", &temp_exercice.nb_set);
	printf("\nCombien de temps de recuperation entre chaque set (secondes): ");
	scanf("%hu", &temp_exercice.temps_recup);
	choixInterval(&temp_exercice); //Propose 2 choix d'Interval et enregistre la donnee
	printf("\nEntrer les poids a utiliser, 0 si aucun. ");
	scanf("%f", &temp_exercice.weight);


	print_exercice(&temp_exercice);
}

int main()
{
	char buffer[50];
	char current_time[50];

	welcome_screen(current_time);
	printf("%s", current_time);

	remplir_template();

	
	

	scanf("%79s", buffer);
	return 0;
}