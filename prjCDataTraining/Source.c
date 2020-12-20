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
	//while (scanf())
}

int main()
{
	char buffer[50];
	char current_time[50];
	
	welcome_screen(current_time);

	printf("%s", current_time);
	

	scanf("%79s", buffer);
	return 0;
}