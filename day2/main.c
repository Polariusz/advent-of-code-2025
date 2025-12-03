#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

long findInvalidPartOne(long id) {
	char buf[16] = {0};
	sprintf(buf, "%ld", id);
	if(strlen(buf) % 2 != 0) {
		// String length is unequal, so it cannot have two same sequences.
		return 0;
	}

	for(int i = 0; i < strlen(buf) / 2; i++) {
		if(buf[i] != buf[strlen(buf)/2 + i]) {
			return 0;
		}
	}

	return id;
}

long iterateThroughLongsToFindInvalidsPartOne(long left, long right) {
	long toReturn = 0;

	for(long i = left; i <= right; i++) {
		long res = findInvalidPartOne(i);
		if(res != 0) {
			toReturn += res;
		}
	}

	return toReturn;
}

long findInvalidPartTwo(long id) {
	char buf[16] = {0};
	sprintf(buf, "%ld", id);

	int middle = strlen(buf) / 2;

	return 0;
}

long iterateThroughLongsToFindInvalidsPartTwo(long left, long right) {
	long toReturn = 0;

	for(long i = left; i <= right; i++) {
		long res = findInvalidPartTwo(i);
		if(res != 0) {
			toReturn += res;
		}
	}

	return toReturn;
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

	long sumPartOne = 0;
	long left = 0;
	long right = 0;
	while(fscanf(fp, "%ld-%ld,", &left, &right) != EOF) {
		printf("left: %ld\n", left);
		printf("right: %ld\n", right);
		sumPartOne += iterateThroughLongsToFindInvalidsPartOne(left, right);
	}

	printf("sumPartOne: %ld\n", sumPartOne);
	fclose(fp);

	return printf("Just Monika\n");
}
