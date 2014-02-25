#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

struct node *insert(struct node *n, char *text) {
	struct node *insNode = (struct node *)malloc(sizeof(struct node));
	insNode->word = (char *)malloc(sizeof(char)*strlen(text)+1);
	insNode->count = 1;
	insNode->similarCount = 0;

	strcpy(text,insNode->word);

	if (n == NULL) {
		/* new tree */
		return insNode;
	}

	struct node *head = n;
	
	struct node *ptr = n;
	struct node *prevPtr;
	
	int cmp = 0; /* init compare int out here so we can access it later */
	while (ptr != NULL) {
		cmp = strcasecmp(insNode->word,ptr->word);
		if (cmp == 0) { /* words equal */
			int sim = strcmp(insNode->word,ptr->word);
			if (sim == 0) { /* same word same case */
				
				ptr->count++;
				return head;
			}
			else { /* same word dif case */
				
				ptr->similarCount++;
				struct node *simPtr = ptr->similar;
				while (simPtr != NULL) {
					simPtr = simPtr->similar;
				}
				simPtr = insNode;
				return head;

			}
		}
		else if (cmp < 0) {
			
			prevPtr->left = insNode;
			return head;
		}
		else {
			
			prevPtr->right = insNode;
			return head;
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

void print(struct node *head) {
	if (head->left != NULL) {
		print(head->left);
	}
	printf("%s\t%d\t%d\n",head->word,head->count,head->similarCount);
	if (head->right != NULL) {
		print(head->right);
	}
}
