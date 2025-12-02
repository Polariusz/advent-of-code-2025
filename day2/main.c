#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct Longs {
	long left;
	long right;
};

struct CharArray {
	char *chars;
	unsigned int c_chars;
	unsigned int max;
};

struct CharArray charArrayNew(unsigned int max)
{
	char *chars = malloc(max * sizeof(char));
	return (struct CharArray) {chars, 0, max};
}

void charArrayAdd(struct CharArray *ca, char c)
{
	if(ca->c_chars == ca->max) {
		char *new_chars = malloc(2 * ca->max * sizeof(char));
		for(int i = 0; i < ca->c_chars; i++) {
			new_chars[i] = ca->chars[i];
		}
		free(ca->chars);
		ca->chars = new_chars;
		ca->max *= 2;
	}
	ca->chars[ca->c_chars] = c;
	++ca->c_chars;
}

char* charArrayToCString(struct CharArray *ca)
{
	char *trimmed_chars = malloc((1 + ca->c_chars) * sizeof(char));
	for(int i = 0; i < ca->c_chars; i++) {
		trimmed_chars[i] = ca->chars[i];
	}
	trimmed_chars[ca->c_chars] = '\0';

	free(ca->chars);
	ca->chars = NULL;
	ca->c_chars = 0;
	ca->max = 0;

	return trimmed_chars;
}

struct Longs strRangeToLongs(char *from)
{
	char *minus = strchr(from, '-');
	if(minus == NULL) {
		printf("f\n");
		return (struct Longs) {0L, 0L};
	}

	++minus;

	struct CharArray leftCA = charArrayNew(16);
	while(*from >= '0' && *from <= '9') {
		charArrayAdd(&leftCA, *from);
		++from;
	}
	char *leftCS = charArrayToCString(&leftCA);

	struct CharArray rightCA = charArrayNew(16);
	while(*minus >= '0' && *minus <= '9') {
		charArrayAdd(&rightCA, *minus);
		++minus;
	}
	char *rightCS = charArrayToCString(&rightCA);

	long left = strtol(leftCS, NULL, 10);
	free(leftCS);

	long right = strtol(rightCS, NULL, 10);
	free(rightCS);

	return (struct Longs) {left, right};
}

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

long iterateThroughLongsToFindInvalidsPartOne(struct Longs longs) {
	long toReturn = 0;

	for(long i = longs.left; i <= longs.right; i++) {
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
}

long iterateThroughLongsToFindInvalidsPartTwo(struct Longs longs) {
	long toReturn = 0;

	for(long i = longs.left; i <= longs.right; i++) {
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

	struct CharArray ca = charArrayNew(16);
	char c = '\0';
	while((c = fgetc(fp)) && c != EOF && c != '\n') {
		charArrayAdd(&ca, c);
	}
	fclose(fp);

	char *text = charArrayToCString(&ca);
	printf("text: %s\n", text);

	long invalidSum = 0;
	char *prevAddr = text;
	char *commaAddr = text;
	while((commaAddr = strchr(commaAddr, ',')) != NULL) {
		struct Longs longs = strRangeToLongs(prevAddr);
		invalidSum += iterateThroughLongsToFindInvalidsPartOne(longs);

		prevAddr = commaAddr + 1;
		commaAddr += 1;
	}
	struct Longs longs = strRangeToLongs(prevAddr);
	invalidSum += iterateThroughLongsToFindInvalidsPartOne(longs);

	printf("Result: %ld\n", invalidSum);

	free(text);
	text = NULL;

	/* Debugging
	printf(">Y %ld\n", findInvalidPartTwo(99));
	printf(">N %ld\n", findInvalidPartTwo(999));
	printf(">Y %ld\n", findInvalidPartTwo(9999));
	printf(">Y %ld\n", findInvalidPartTwo(1010));
	printf(">Y %ld\n", findInvalidPartTwo(102102));
	printf(">N %ld\n", findInvalidPartTwo(22222));
	printf(">Y %ld\n", findInvalidPartTwo(223344223344));
	*/

	return printf("Just Monika\n");
}
