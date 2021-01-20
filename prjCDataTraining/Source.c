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
	//TODO: Fix infinite loop on entering string
}

void fprint_exercice(exercice_template *temp_exercice, FILE *ptrTemplate)
{

	if (temp_exercice->measure == REPETITION)
	{
		fprintf(ptrTemplate, "%hu,1,%s,%hu,%hu,%hu,%.2f\n",		temp_exercice->id,
																temp_exercice->nom_exercice,
																temp_exercice->nb_set,
																temp_exercice->temps_recup,
																temp_exercice->quantity.nb_repetition,
																temp_exercice->weight);
	}
	else if (temp_exercice->measure == DUREE)
	{
		fprintf(ptrTemplate, "%hu,2,%s,%hu,%hu,%hu,%.2f\n",		temp_exercice->id,
																temp_exercice->nom_exercice,
																temp_exercice->nb_set,
																temp_exercice->temps_recup,
																temp_exercice->quantity.duree,
																temp_exercice->weight);
	}	
}

//Propose 2 choix d'Interval et enregistre la donnee
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

exercice_template remplir_template()
{
	exercice_template temp_exercice;
	exercice_template_default(&temp_exercice);


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

	return temp_exercice;
}

//Returns answer of the question, Y=true
int askquestion(char *question)
{
	char whitespace[5] = "";
	char answer = "";

	printf("\n%s O/N: ",question);
	scanf(" %c", &answer); //TODO: Test modifier scanf pour fgets et retirer fgets 
	fgets(whitespace, 5, stdin);
	
	if (answer == 'O' || answer == 'o')
	{
		return 1;
	}
	else { return 0; }

}

short nextExerciceID(exercice_template *exercices)
{
	int i = 0;

	while (exercices[i].nom_exercice[0] != NULL)
	{
		i++;
	}

	return (exercices[i - 1].id + 1);
}

void createtemplate_loop(exercice_template *exercices)
{
	FILE *ptrTemplate = fopen("Templates_Exercice.csv", "a");
	exercice_template temp_template;
	char answer[1];
	char *question = "Voulez-vous ajouter un exercice?";

	while (askquestion(question))
	{
		temp_template = remplir_template();
		temp_template.id = nextExerciceID(exercices);
		fprint_exercice(&temp_template, ptrTemplate);
	} 
	fclose(ptrTemplate);
}

//Returns I which will finally be amount of exercises created
void read_exercises(exercice_template *exercices)
{
	FILE *ptrTemplate = fopen("Templates_Exercice.csv", "r");
	short measure_type = 0;

	if (ptrTemplate == NULL)
	{
		puts("Template file does not exist. Add exercises before training");
	}

	int i = 0;
	while (fscanf(ptrTemplate, "%hu,%hu,%[^,],%hu,%hu,%hu,%5f", &exercices[i].id,&measure_type, exercices[i].nom_exercice, &exercices[i].nb_set, &exercices[i].temps_recup, &exercices[i].quantity.duree, &exercices[i].weight) == 7)
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
}

void printtemplatelist(exercice_template *templates)
{
	int i = 0;
	while (templates[i].nom_exercice[0] != NULL)
	{
		//Print exercises
		printf("%i- %s\n", i + 1, templates[i].nom_exercice);
		i++;
	}
}

void menu_training(exercice_template *exercices)
{
	char *question = "\nVoulez vous debuter l'entrainement?";
	if (askquestion(question))
	{
		printtemplatelist(exercices);//TODO: StartTraining()
	}
	else { puts("\nI don't want to train!"); }
}

void printExercise(exercice_template *exercise)
{
	//Imprimer les infos de exercise
	printf("\n\n\tDetails for exercise: %s", exercise->nom_exercice);
	printf("\n\tAmount of sets: %hu", exercise->nb_set);
	printf("\n\tTime between sets (seconds): %hu", exercise->temps_recup);
	if (exercise->measure == REPETITION)
	{
		printf("\n\tNumber of repetitions: %hu", exercise->quantity.nb_repetition);
	}
	else if (exercise->measure == DUREE)
	{
		printf("\n\tDuration of exercise (seconds): %hu", exercise->quantity.duree);
	}
	printf("\n\tWeight (Pounds): %3.2f", exercise->weight);

}

void rewrite_Exercise(exercice_template *exercices)
{
	FILE *ptrTemplate = fopen("Templates_Exercice.csv", "w");
	int i = 0;
	
	while (exercices[i].nom_exercice[0] != NULL)
	{
		fprint_exercice((exercices + i), ptrTemplate);
		i++;
	}
}

void modifyExercise(exercice_template *exercices)
{
	exercice_template temp_template;
	char whitespace[5];

	int exercise_nb = 0;
	puts("\nEnter the exercise number to modify: ");
	while (exercise_nb < 1 || exercise_nb > MAXEXERCICE)
	{
		scanf("%i", &exercise_nb);
		fgets(whitespace, 5, stdin);
		if (exercise_nb == 0) { return; }
	}

	exercise_nb--;
	printExercise(exercices + exercise_nb);
	temp_template = remplir_template();
	temp_template.id = exercices[exercise_nb].id;
	printExercise(&temp_template);
	if (askquestion("Are you certain to replace these values?"))
	{
		exercices[exercise_nb] = temp_template;
	}

	rewrite_Exercise(exercices);
	

}

void menu_exercises(exercice_template *exercices)
{
	int menu_option = NULL;

	do {
		puts("\n\nVeuillez choisir une option.");
		puts(	"\t1- Ajouter Exercice\n"
				"\t2- Modifier Exercice\n"
				"\t0- Quitter\n\n");
		scanf("%i", &menu_option);
	} while (menu_option < 0 || menu_option > 2);

	switch (menu_option)
	{
	case 1:
		createtemplate_loop(exercices);
		break;
	case 2:
		printtemplatelist(exercices);
		modifyExercise(exercices);
		break;;
	default:
		break;
	}

}

void menu_trainingday()
{
	int menu_option = NULL;

	do {
		puts("\n\nVeuillez choisir une option.");
		puts("\t1- Ajouter Journee Entrainement\n"
			"\t2- Modifier Journee Entrainement\n"
			"\t0- Quitter\n\n");
		scanf("%i", &menu_option);
	} while (menu_option < 0 || menu_option > 2);

	switch (menu_option)
	{
	case 1:
		puts("Ajout de journee");
		break;
	case 2:
		puts("Modification de journee");
		break;
	default:
		break;
	}
}

void setup(exercice_template *exercices)
{
	//Initialize all exercice_template to initial value (to be removed after Code5)
	for (int i = 0; i < MAXEXERCICE; i++)
	{
		exercice_template_default(exercices + i);
	}

	//Read all exercice_templates into memory
	read_exercises(exercices);
}

int main()
{
	exercice_template exercices[MAXEXERCICE];
	char current_time[50];
	
	setup(&exercices);

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
				menu_exercises(exercices);
				break;
			case 3:
				menu_trainingday();
				break;
			case 0:
				puts("Fermeture application!");
				break;
			default:
				puts("Option invalide\n");
		}
	} while (menu_option != 0);


	puts("Fin Programme");
	return 0;
}