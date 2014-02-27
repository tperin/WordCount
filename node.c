#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "node.h"

struct node *newNode(char *text) {
	struct node *n = (struct node *)malloc(sizeof(struct node));
	n->word = (char *)malloc(sizeof(char)*strlen(text)+1);
	n->count = 1;
	n->similarCount = 0;
	return n;
}

struct node *insert(struct node *n, char *text) {
	struct node *head;
	struct node *ptr;
	struct node *prevPtr;
	int cmp;
	int sim;
	struct node *simPtr;

	struct node *insNode = (struct node *)malloc(sizeof(struct node));
	insNode->word = (char *)malloc(sizeof(char)*strlen(text)+1);
	insNode->count = 1;
	insNode->similarCount = 0;

	strcpy(insNode->word, text);

	head = n;

		if (head == NULL) {
		/* new tree */
		return insNode;
	}
	
	ptr = n;
	prevPtr = ptr;
	
	cmp = 0; /* init compare int out here so we can access it later */
	while (ptr != NULL) {
		cmp = strcasecmp(insNode->word,ptr->word);
		if (cmp == 0) { 
			/* words equal */
			sim = strcmp(insNode->word,ptr->word);
			if (sim == 0) { 
				/* same word same case */
				ptr->count++;
				return head;
			}
			else { 
				/* same word dif case */
				ptr->similarCount++;
				
				simPtr = ptr->similar;
				while (simPtr != NULL) {
					simPtr = simPtr->similar;
				}
				simPtr = insNode;
				
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

