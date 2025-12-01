#include <stdio.h>
#include <stdlib.h>

void addDirection(char direction, int distance, int *currentRotation, int *cntZeroesPartOne, int *cntZeroesPartTwo)
{
	if(direction == 'L') {
		*currentRotation -= distance;
		while(*currentRotation < 0) {
			*currentRotation += 100;
			++(*cntZeroesPartTwo);
		}
	} else if(direction == 'R') {
		*currentRotation += distance;
		while(*currentRotation > 99) {
			*currentRotation -= 100;
			++(*cntZeroesPartTwo);
		}
	} else {
		printf("Unknown direction detected, it's '%c'\n", direction);
	}
	if(*currentRotation == 0) {
		++(*cntZeroesPartOne);
	}
}

int main(int carg, char **varg)
{
	if(carg < 2) {
		printf("please provide path to the input file as argument.\n");
		return 1;
	}
	FILE *fp = fopen(varg[1], "r");
	if(fp == NULL)
	{
		printf("file '%s' does not exist.\n", varg[1]);
		return 69;
	}

	int cntZeroesPartOne = 0;
	int cntZeroesPartTwo = 0;
	int currentRotation = 50;
	char direction = '\0';
	int distance = 0;
	while(fscanf(fp, "%c%d\n", &direction, &distance) != EOF) {
		addDirection(direction, distance, &currentRotation, &cntZeroesPartOne, &cntZeroesPartTwo);
	}
	fclose(fp);
	printf("Password for part 1: %d\n", cntZeroesPartOne);
	printf("Password for part 2: %d\n", cntZeroesPartTwo);
	printf("Just Monika\n");
	return 0;
}

