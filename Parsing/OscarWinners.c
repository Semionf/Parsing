#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable:4996)

int main4()
{
	FILE* f = fopen("oscar_age_female.txt","r");
	char str[100] = "0", * year = 0, * name, * movie;
	char* token = 0;
	fgets(str, sizeof(str), f);
	while (fgets(str, sizeof(str), f))
	{
		token = strtok(str, " ");
		year = strtok(NULL, ",");
		token = strtok(NULL, "\"");
		name = strtok(NULL, "\"");
		token = strtok(NULL, "\"");
		movie = strtok(NULL, "\"");
		token = strtok(str, " ");
		printf("The Oskar Goes to %s at %s Movie %s\n", name, year, movie);
	}
}