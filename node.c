#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

struct node *newNode(char *text) {
	struct node *n = (struct node *)malloc(sizeof(struct node));
	n->word = (char *)malloc(sizeof(char)*strlen(text)+1);
	n->count = 1;
	n->similarCount = 0;
	return n;
}

struct node *insert(struct node *n, char *text) {
	struct node *insNode = (struct node *)malloc(sizeof(struct node));
	insNode->word = (char *)malloc(sizeof(char)*strlen(text)+1);
	insNode->count = 1;
	insNode->similarCount = 0;

	strcpy(insNode->word, text);

	struct node *head = n;

		if (head == NULL) {
		/* new tree */
		return insNode;
	}
	
	struct node *ptr = n;
	struct node *prevPtr = ptr;
	
	int cmp = 0; /* init compare int out here so we can access it later */
	while (ptr != NULL) {
		cmp = strcasecmp(insNode->word,ptr->word);
		if (cmp == 0) { 
			/* words equal */
			int sim = strcmp(insNode->word,ptr->word);
			if (sim == 0) { 
				/* same word same case */
				ptr->count++;
				return head;
			}
			else { 
				/* same word dif case */
				ptr->similarCount++;
				/* we dont really need this
				struct node *simPtr = ptr->similar;
				while (simPtr != NULL) {
					simPtr = simPtr->similar;
				}
				simPtr = insNode;
				*/
				return head;

			}
		}
		else if (cmp < 0) {
			prevPtr = ptr;
			ptr = ptr->left;
		}
		else {
			prevPtr = ptr;
			ptr = ptr->right;
		}
	}
	
	/* reached end of tree, this is a new word */
	if (cmp < 0) {
		/* previous pointer was to the right */
		prevPtr->left = insNode;
	}
	else {
		/* previous pointer was to the left */
		prevPtr->right = insNode;
	}
	return head;
}

void traverse(struct node *head) {
	if (head->left != NULL) {
		traverse(head->left);
	}
	int i;
	for (i = 0; i < strlen(head->word); i++) {
		head->word[i] = tolower(head->word[i]);
	}
	printf("%s\t%d\t%d\n",head->word,head->count,head->count + head->similarCount);
	if (head->right != NULL) {
		traverse(head->right);
	}
}
