#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct RangeNode {
	unsigned long from;
	unsigned long to;
	struct RangeNode *next;
};

struct RangeNode *push(struct RangeNode *root, unsigned long from, unsigned long to)
{
	struct RangeNode *rn = malloc(sizeof(struct RangeNode));
	rn->from = from;
	rn->to = to;
	rn->next = root;

	return rn;
}

struct RangeNode *pop(struct RangeNode *root, unsigned long *from, unsigned long *to)
{
	if(!root)
		return root;

	struct RangeNode *toFree = root;
	root = root->next;

	if(from)
		*from = toFree->from;
	if(to)
		*to = toFree->to;

	toFree->from = 0L;
	toFree->to = 0L;
	toFree->next = NULL;

	free(toFree);

	return root;
}

int isWithinRange(struct RangeNode *root, unsigned long l)
{
	struct RangeNode *node = root;
	while(node) {
		if(node->from <= l && l <= node->to) {
			printf("%lu-%lu, %lu\n", node->from, node->to, l);
			return 1;
		}
		node = node->next;
	}

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

	struct RangeNode *rn = NULL;
	unsigned long from = 0L;
	unsigned long to = 0L;
	while(fscanf(fp, "%lu-%lu\n", &from, &to) != EOF) {
		if(to == 0L) {
			break;
		}

		rn = push(rn, from, to);
		to = 0L;
	}

	unsigned long c_fresh = 0;

	unsigned long num = from;
	do {
		if(isWithinRange(rn, num)) {
			++c_fresh;
		}
	} while(fscanf(fp, "%lu\n", &num) != EOF);

	printf("Part one: %lu\n", c_fresh);

	while(rn != NULL) {
		rn = pop(rn, NULL, NULL);
	}

	fclose(fp);
	printf("Just Monika\n");
	return 0;
}
