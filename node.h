#ifndef NODE_H
#define NODE_H

typedef struct node {
	char *word;
	int count;
	int similarCount;
	struct node *left;
	struct node *right;
	struct node *similar;
} node;

struct node *insert(struct node *, char *);

void print(struct node *);

#endif
