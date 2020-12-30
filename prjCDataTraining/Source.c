#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Header.h"
#define MAXEXERCICE 20

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

int menu_main()
{
	int menu_option = NULL;

	do {
		puts("\n\nVeuillez choisir une option.");
		puts(	"\t1- Debuter entrainement!\n"
				"\t2- Ajouter/Modifier Exercices\n"
				"\t3- Ajouter/Modifier Journées Entrainement\n"
				"\t0- Quitter\n\n");
		scanf("%i", &menu_option);
	} while (menu_option <0 || menu_option > 3);

	return menu_option;

}

void print_exercice(exercice_template *temp_exercice)
{
	FILE *ptrTemplate = fopen("Templates_Exercice.csv", "a");


	if (temp_exercice->measure == REPETITION)
	{
		fprintf(ptrTemplate, "1,'%s',%hu,%hu,%hu,%.2f\n",		temp_exercice->nom_exercice,
																temp_exercice->nb_set,
																temp_exercice->temps_recup,
																temp_exercice->quantity.nb_repetition,
																temp_exercice->weight);
	}
	else if (temp_exercice->measure == DUREE)
	{
		fprintf(ptrTemplate, "2,'%s',%hu,%hu,%hu,%.2f\n",		temp_exercice->nom_exercice,
																temp_exercice->nb_set,
																temp_exercice->temps_recup,
																temp_exercice->quantity.duree,
																temp_exercice->weight);
	}
	fclose(ptrTemplate);
	
}

void choixInterval(exercice_template *temp_exercice)
{
	int choix = 0;

	while ((choix < 1) || (choix > 2))
	{
		printf("\nVeuillez choisir l'unite de mesure de l'activite: \t1- Repetition\t2-Duree\n");
		scanf("%i", &choix);
	}

	switch (choix)
	{
	case 1:
		temp_exercice->measure = REPETITION;
		printf("\nEntrer le nombre de repetition: ");
		scanf("%hu", &temp_exercice->quantity.nb_repetition);
		break;
	case 2:
		temp_exercice->measure = DUREE;
		printf("\nEntrer la duree: ");
		scanf("%hu", &temp_exercice->quantity.duree);
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

	//TODO: Retirer scanf non necessaire, modifier vers fgets ou autre
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
//Returns answer of the question, Y=true
int askquestion(char *question)
{
	char whitespace[5] = "";
	char answer = "";

	printf("\n%s O/N: ",question);
	scanf(" %c", &answer);
	fgets(whitespace, 5, stdin);
	
	if (answer == 'O' || answer == 'o')
	{
		return 1;
	}
	else { return 0; }

}

void createtemplate_loop()
{
	
	char answer[1];
	char *question = "Voulez-vous ajouter un exercice?";

	while (askquestion(question))
	{
		remplir_template();
	} 
}

//Returns I which will finally be amount of exercises created
int read_exercises(exercice_template *exercices)
{
	FILE *ptrTemplate = fopen("Templates_Exercice.csv", "r");
	short measure_type = 0;

	if (ptrTemplate == NULL)
	{
		puts("Template file does not exist. Add exercises before training");
		return 0;
	}

	int i = 0;
	while (fscanf(ptrTemplate, "%hu,%[^,],%hu,%hu,%hu,%5f", &measure_type, exercices[i].nom_exercice, &exercices[i].nb_set, &exercices[i].temps_recup, &exercices[i].quantity.duree, &exercices[i].weight) == 6)
	{
		if (measure_type == 1)
		{
			exercices[i].measure == REPETITION;
		}
		else if (measure_type == 2)
		{
			exercices[i].measure == DUREE;
		}
		

		i++;
	}
	
	return i++;
}

void printtemplatelist(exercice_template *templates, int nb_exercises)
{
	for (int i = 0; i < nb_exercises; i++)
	{
		//Print exercises
		printf("%i- %s\n", i+1, templates[i].nom_exercice);
	}
}

void menu_training(exercice_template *exercices)
{
	char *question = "Voulez vous debuter l'entrainement?";
	if (askquestion(question))
	{
		printtemplatelist(exercices, read_exercises(exercices));
	}
	else { puts("I don't want to train!"); }
}

void menu_exercises()
{
	createtemplate_loop();
}

void menu_trainingday()
{
	puts("Entered menu_trainingday()");
}

int main()
{
	exercice_template exercices[MAXEXERCICE];
	char current_time[50];
	
	//Main Menu
	int menu_option;
	do
	{
		switch (menu_option = menu_main())
		{
			case 1:
				menu_training(exercices);
				break;
			case 2:
				menu_exercises();
				break;
			case 3:
				menu_trainingday();
				break;
			case 0:
				puts("Fermeture application!");
				break;
		}
	} while (menu_option != 0);


	puts("Fin Programme");
	return 0;
}