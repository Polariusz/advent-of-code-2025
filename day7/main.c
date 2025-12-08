#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CharPtrNode {
	char *item;
	struct CharPtrNode *next;
};

struct CharPtrNodeLL {
	struct CharPtrNode *root;
	unsigned int size;
};

struct CharPtrNodeLL charPtrNodeLLNew(void)
{
	return (struct CharPtrNodeLL) {NULL, 0};
}

void charPtrNodeLLAdd(struct CharPtrNodeLL *ll, char *item)
{
	struct CharPtrNode *cpn = malloc(sizeof(*cpn));

	int c_item = strlen(item);
	cpn->item = malloc((c_item + 1) * sizeof(char));
	for(unsigned int i = 0; i < c_item; ++i) {
		cpn->item[i] = item[i];
	}
	cpn->item[c_item] = '\0';
	cpn->next = NULL;

	++ll->size;
	if(ll->root == NULL) {
		ll->root = cpn;
		return;
	}

	struct CharPtrNode *iter = ll->root;
	while(iter->next != NULL) {
		iter = iter->next;
	}
	iter->next = cpn;

	return;
}

char *charPtrNodeLLGet(struct CharPtrNodeLL *ll, unsigned int i)
{
	if(i > ll->size) {
		printf("oob\n");
		return NULL;
	}

	struct CharPtrNode *iter = ll->root;
	while(i) {
		iter = iter->next;
		--i;
	}

	return iter->item;
}

void charPtrNodeLLDestroy_r(struct CharPtrNode *n)
{
	if(!n)
		return;

	charPtrNodeLLDestroy_r(n->next);
	free(n->item);
	n->item = NULL;
	n->next = NULL;
	free(n);

	return;
}

void charPtrNodeLLDestroy(struct CharPtrNodeLL *ll)
{
	charPtrNodeLLDestroy_r(ll->root);
	ll->size = 0;

	return;
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

	struct CharPtrNodeLL ll = charPtrNodeLLNew();
	char buf[256] = {0};
	while(fscanf(fp, "%s\n", buf) != EOF) {
		charPtrNodeLLAdd(&ll, buf);
	}

	unsigned int splits = 0;
	for(int i = 1; i < ll.size; ++i)
	{
		char *prev = charPtrNodeLLGet(&ll, i-1);
		char *next = charPtrNodeLLGet(&ll, i);
		int c_row = strlen(next);
		for(int r = 0; r < c_row; ++r) {
			if(prev[r] == 'S' || prev[r] == '|') {
				if(next[r] == '.') {
					next[r] = '|';
				} else if(next[r] == '^') {
					++splits;
					if(r > 0) {
						next[r-1] = '|';
					}
					if(r < c_row) {
						next[r+1] = '|';
					}
				}
			}
		}
	}

	printf("splits 1: %u\n", splits);

	for(int i = 0; i < ll.size; ++i) {
		char *row = charPtrNodeLLGet(&ll, i);
		printf("i: %3d | %s\n", i, row);
	}

	charPtrNodeLLDestroy(&ll);
	fclose(fp);

	printf("Just Monika\n");
	return 0;
}
