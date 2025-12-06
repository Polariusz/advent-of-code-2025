#include <stdio.h>
#include <string.h>

long findMaxJoltage(char *buf)
{
	int len = strlen(buf);
	if(strlen(buf) < 2) {
		return 0;
	}

	long l = (long) (*buf - '0');
	long r = (long) (*(buf + 1) - '0');
	++buf;
	++buf;
	while(*buf != '\0') {
		int digit = (*buf - '0'); 
		if(r <= l) {
			if(r < digit) {
				r = digit;
			}
		} else {
			l = r;
			r = digit;
		}
		++buf;
	}

	printf("%d%d\n", l, r);

	return l*10+r;
}

long findMaxJoltagePartTwo(char *buf, unsigned int len)
{
	char res[len+1];
	for(int i = 0; i < len+1; ++i) {
		res[i] = '\0';
	}

	unsigned int c_res = 0;

	for(unsigned int i = 0; i < strlen(buf); ++i) {
		if(c_res < len) {
			res[c_res] = buf[i];
			++c_res;
		} else {
			// len reached
		}
	}

	printf("res: %s\n", res);
	return 0;
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

	/*
	long sum = 0;
	char buf[128] = {0};
	while(fscanf(fp, "%s\n", buf) != EOF) {
		printf("buf: %s\n", buf);
		sum += findMaxJoltage(buf);
	}

	printf("sum: %ld\n", sum);
	*/

	printf("in: 123321, 3; expected: 321 "); findMaxJoltagePartTwo("123321", 3);
	printf("in: 123321, 2; expected: 33 "); findMaxJoltagePartTwo("123321", 2);
	printf("in: 321123, 4; expected: 3223 "); findMaxJoltagePartTwo("321123", 4);
	printf("in: 321123, 5; expected: 32123 "); findMaxJoltagePartTwo("321123", 5);

	return printf("Just Monika\n");
}

