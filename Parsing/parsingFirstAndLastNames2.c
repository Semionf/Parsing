#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable:4996)

int main3()
{
	char str[100];
	printf("Please enter your last and first name: ");
	gets(str);
	char* token = strtok(str, " ");
	while (token)
	{
		printf("%s\n", token);
		token = strtok(NULL, "");
	}
}