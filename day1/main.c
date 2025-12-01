#include <stdio.h>
#include <stdlib.h>

void rotate(char direction, int distance, int *currentRotation, int *cntZeroesPartOne, int *cntZeroesPartTwo)
{
	printf("Curr: %d next: %c-%d\n", *currentRotation, direction, distance);
	int addedPartTwo = 0;
	while(distance > 100) {
		distance -= 100;
		++(*cntZeroesPartTwo);
		++addedPartTwo;
	}

	if(direction == 'L') {
		if(*currentRotation - distance < 0) {
			if(*currentRotation != 0) {
				++(*cntZeroesPartTwo);
				++addedPartTwo;
			}
			*currentRotation += 100;
		}
		*currentRotation -= distance;
	} else if(direction == 'R') {
		if(*currentRotation + distance > 99) {
			if(*currentRotation != 0 && *currentRotation + distance != 100) {
				++(*cntZeroesPartTwo);
				++addedPartTwo;
			}
			*currentRotation -= 100;
		}
		*currentRotation += distance;
	} else {
		printf("Unknown direction detected, it's '%c'\n", direction);
	}
	if(*currentRotation == 0) {
		++(*cntZeroesPartOne);
	}

	printf("\taddedPartTwo: %d\n", addedPartTwo);
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
		rotate(direction, distance, &currentRotation, &cntZeroesPartOne, &cntZeroesPartTwo);
	}
	fclose(fp);
	printf("Password for ONLY part 1: %d\n", cntZeroesPartOne);
	printf("Password for ONLY part 2: %d\n", cntZeroesPartTwo);
	printf("Password for part 2     : %d\n", cntZeroesPartOne + cntZeroesPartTwo);

	printf("Just Monika\n");
	return 0;
}

