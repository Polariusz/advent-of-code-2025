#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

long findInvalidPartOne(long id)
{
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

long iterateThroughLongsToFindInvalidsPartOne(long left, long right)
{
	long toReturn = 0;

	for(long i = left; i <= right; i++) {
		long res = findInvalidPartOne(i);
		if(res != 0) {
			toReturn += res;
		}
	}

	return toReturn;
}

int isThereAPattern(char *str, unsigned int len)
{
	if(strlen(str) < 2) {
		// printf("Too short!\n");
		return 0;
	}
	int cnt = strlen(str) / len;
	if(cnt * len != strlen(str)) {
		// printf("Pattern is impossible.\n");
		return 0;
	}

	for(int i = 0; i < len; i++) {
		for(int j = i; j < strlen(str); j+=len) {
			// printf("   str[i:%d]:%c != str[j:%d]:%c   ", i, str[i], j, str[j]);
			if(str[i] != str[j]) {
				// printf("bad\n");
				return 0;
			}
		}
	}

	// printf("ya\n");
	return 1;
}

long findInvalidPartTwo(long id)
{
	char buf[16] = {0};
	sprintf(buf, "%ld", id);

	int middle = strlen(buf) / 2;
	for(int i = 1; i <= middle; i++) {
		if(isThereAPattern(buf, i) == 1) {
			return id;
		}
	}

	return 0;
}

long iterateThroughLongsToFindInvalidsPartTwo(long left, long right)
{
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
	long sumPartTwo = 0;
	long left = 0;
	long right = 0;
	while(fscanf(fp, "%ld-%ld,", &left, &right) != EOF) {
		printf("left: %ld\n", left);
		printf("right: %ld\n", right);
		sumPartOne += iterateThroughLongsToFindInvalidsPartOne(left, right);
		sumPartTwo += iterateThroughLongsToFindInvalidsPartTwo(left, right);
	}

	printf("sumPartOne: %ld\n", sumPartOne);
	printf("sumPartTwo: %ld\n", sumPartTwo);
	fclose(fp);

	/*
	printf("N(1): "); isThereAPattern("1", 1);
	printf("N(1): "); isThereAPattern("12", 1);
	printf("Y(1): "); isThereAPattern("11", 1);
	printf("Y(1): "); isThereAPattern("111", 1);
	printf("Y(1): "); isThereAPattern("1111", 1);
	printf("Y(1): "); isThereAPattern("11111", 1);
	printf("Y(1): "); isThereAPattern("111111", 1);
	printf("N(2): "); isThereAPattern("111", 2);
	printf("Y(2): "); isThereAPattern("1212", 2);
	printf("Y(2): "); isThereAPattern("121212", 2);
	printf("Y(3): "); isThereAPattern("123123", 3);
	printf("N(3): "); isThereAPattern("696969", 3);
	*/

	return printf("Just Monika\n");
}
