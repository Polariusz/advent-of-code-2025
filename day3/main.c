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

long findMaxJoltagePartTwo(char *buf) 
{
	// TODO: impl this.
	// 
	// max: 3; buf: "543211218123"
	// for i=0;i<max;i++:
		// Find the biggest that is located from 0 to strlen(buf) - max + i + 1
		// found one needs to be added to array
		// Cut from 0 to found
	// 543211218123
	// add(8)
	// 123
	// add(2)
	// add(3)
	// 
	//
	// max: 4; buf: 33224422921118211173
	// add(9)
	// 21118211173
	// add(8)
	// 211173
	// add(7)
	// add(3)
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

	long sum = 0;
	char buf[128] = {0};
	while(fscanf(fp, "%s\n", buf) != EOF) {
		printf("buf: %s\n", buf);
		sum += findMaxJoltage(buf);
	}

	printf("sum: %ld\n", sum);

	return printf("Just Monika\n");
}

