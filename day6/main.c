#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct OperatorResult {
	char op;
	unsigned long res;
};

struct ORList {
	struct OperatorResult *arr;
	unsigned int cnt;
	unsigned int cap;
};

void orListDump(struct ORList *orl)
{
	printf("cnt: %u\ncap: %u\narr: ", orl->cnt, orl->cap);
	for(unsigned int i = 0; i < orl->cnt; ++i) {
		printf("|op: %c, res: %lu| ", orl->arr[i].op, orl->arr[i].res);
	}
	printf("\n");

	return;
}

struct ORList orListNew(void)
{
#define ORLIST_DEFAULT_SIZE 16

	struct ORList orl;
	orl.arr = malloc(ORLIST_DEFAULT_SIZE * sizeof(struct OperatorResult));
	orl.cnt = 0;
	orl.cap = ORLIST_DEFAULT_SIZE;

	return orl;
}

void orListAdd(struct ORList *orl, char op)
{
	if(orl->cnt == orl->cap) {
		orl->cap *= 2;
		struct OperatorResult *newArr = malloc(orl->cap * sizeof(struct OperatorResult));
		for(unsigned int i = 0; i < orl->cnt; ++i) {
			newArr[i] = orl->arr[i];
		}
		free(orl->arr);
		orl->arr = newArr;
	}
	
	orl->arr[orl->cnt].op = op;
	orl->arr[orl->cnt].res = op == '*' ? 1 : 0;
	++orl->cnt;

	return;
}

void doIt(struct OperatorResult *or, unsigned long l)
{
	if(or->op == '*') {
		or->res *= l;
	} else {
		or->res += l;
	}

	return;
}

unsigned long sumTheseORs(struct ORList *l)
{
	unsigned long res = 0;
	for(unsigned int i = 0; i < l->cnt; ++i) {
		res += l->arr[i].res;
	}

	return res;
}

int isNumber(char *buf)
{
	for(;*buf != '\0'; ++buf)
	{
		if(!(*buf >= '0' && *buf <= '9')) {
			return 0;
		}
	}

	return 1;
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

	struct ORList l = orListNew();

	char buf[16] = {0};
	while(fscanf(fp, "%s", buf) != EOF) {
		if(*buf == '*' || *buf == '+') {
			orListAdd(&l, *buf);
		}
	}

	rewind(fp);

	unsigned int index = 0;
	while(fscanf(fp, "%s", buf) != EOF) {
		if(index >= l.cnt) {
			index = 0;
		}

		if(!isNumber(buf)) {
			break;
		}

		unsigned long num = strtoul(buf, NULL, 10);
		doIt(&l.arr[index], num);
		++index;
	}

	unsigned long res = sumTheseORs(&l);
	printf("res: %lu\n", res);

	free(l.arr);
	l.arr = NULL;
	l.cnt = 0;
	l.cap = 0;
	fclose(fp);
	return printf("Just Monika\n");
}

