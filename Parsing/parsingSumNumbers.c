#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable:4996)

int main1()
{
	int sum = 0, num = 0;
	char str[100] = "123,456,789,1,2,3,4,5,6,7,2000";
		char* token = strtok(str, ",");
		while (token)
		{
			num = atoi(token);
			sum += num;
			token = strtok(NULL, ",");
		}
		printf("The sum is: %d", sum);
}