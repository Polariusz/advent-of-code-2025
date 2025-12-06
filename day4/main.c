#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef char* u_char_ptr;

struct Node {
	u_char_ptr char_p;
	struct Node *next;
};

struct LL {
	struct Node *root;
	unsigned int size;
};

struct LL LLNew(void)
{
	return (struct LL) {NULL, 0};
}

void llPush(struct LL *ll, char *buf)
{
	int c_buf = strlen(buf);

	struct Node *n = malloc(sizeof(struct Node));
	if(!n) {
		printf("Download more RAM\n");
		return;
	}

	u_char_ptr char_p = malloc((1 + c_buf) * sizeof(char));
	if(!char_p) {
		printf("Download more RAM\n");
		free(n);
		return;
	}

	for(int i = 0; i < c_buf; i++) {
		char_p[i] = buf[i];
	}
	char_p[c_buf] = '\0';

	n->char_p = char_p;
	n->next = ll->root;
	ll->root = n;
	ll->size += 1;

	return;
}

u_char_ptr llPop(struct LL *ll)
{
	if(!ll->root)
		return NULL;

	struct Node *toFree = ll->root;
	ll->root = ll->root->next;
	ll->size -= 1;

	u_char_ptr char_p = toFree->char_p;
	toFree->next = NULL;
	toFree->char_p = NULL;

	free(toFree);

	return char_p;
}

char* llGet(struct LL *ll, unsigned int i)
{
	if(i > ll->size) {
		printf("oob\n");
		return NULL;
	}

	struct Node *n = ll->root;
	while(i > 0) {
		n = n->next;
		--i;
	}

	return n->char_p;
}

void llDump_r(struct Node *n) {
	if(!n)
		return;
	llDump_r(n->next);

	printf("%s\n", n->char_p);
}

void llDump(struct LL *ll)
{
	llDump_r(ll->root);
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

	struct LL ll = LLNew();

	char buf[255] = {0};
	while(fscanf(fp, "%s\n", &buf) != EOF) {
		llPush(&ll, buf);
	}

	int certified_forklifting_happened = 1;
	unsigned int certified_forklifting = 0;
	while(certified_forklifting_happened) {
		certified_forklifting_happened = 0;
		for(int rowI = 0; rowI < ll.size; ++rowI) {
			char *row = llGet(&ll, rowI);
			int c_row = strlen(row);
			for(int columnI = 0; columnI < c_row; ++columnI) {
				int neighbours = 0;
				if(row[columnI] != '@') {
					continue;
				} else {
					int u = 0;
					int d = 0;
					int l = 0;
					int r = 0;
					if(rowI > 0) {
						u = 1;
					}
					if(rowI < ll.size - 1) {
						d = 1;
					}
					if(columnI > 0) {
						l = 1;
					}
					if(columnI < c_row) {
						r = 1;
					}
					if(u) {
						char *upRow = llGet(&ll, rowI-1);
						if(upRow[columnI] == '@') {
							++neighbours;
						}
					}
					if(d) {
						char *downRow = llGet(&ll, rowI+1);
						if(downRow[columnI] == '@') {
							++neighbours;
						}
					}
					if(l) {
						if(row[columnI - 1] == '@') {
							++neighbours;
						}
					}
					if(r) {
						if(row[columnI + 1] == '@') {
							++neighbours;
						}
					}
					if(u && l) {
						char *upRow = llGet(&ll, rowI-1);
						if(upRow[columnI - 1] == '@') {
							++neighbours;
						}
					}
					if(u && r) {
						char *upRow = llGet(&ll, rowI-1);
						if(upRow[columnI + 1] == '@') {
							++neighbours;
						}
					}
					if(d && l) {
						char *downRow = llGet(&ll, rowI+1);
						if(downRow[columnI - 1] == '@') {
							++neighbours;
						}
					}
					if(d && r) {
						char *downRow = llGet(&ll, rowI+1);
						if(downRow[columnI + 1] == '@') {
							++neighbours;
						}
					}
				}
				if(neighbours < 4) {
					// Comment these two lines down to get part one of the day 4.
					certified_forklifting_happened = 1;
					row[columnI] = 'x';
					++certified_forklifting;
				}
			}
		}

		llDump(&ll);
		// usleep(1000 * 200);

		if(!certified_forklifting_happened) {
			break;
		}
	}

	printf("certified forklifting: %d\n", certified_forklifting);
	while(ll.root != NULL) {
		u_char_ptr row = llPop(&ll);
		free(row);
	}

	fclose(fp);
	return printf("Just Monika\n");
}
