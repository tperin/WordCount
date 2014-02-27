#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "node.h"
#include "wordstat.h"

struct node *head;

int main(int argc, char ** argv) {

	FILE *file;
	int c;
	char *wordBuffer;
	int ch;

	if (argc != 2) {
		printf("Invalid usage. Use -h flag for help\n");
		return 0;	
	}
	if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"-help") == 0) {
		printf("Usage: wordstat [-h] <filename>\n");
		return 0;
	}

	head = NULL;
	file  = fopen(argv[1],"r");
	if (file == NULL) {
		printf("Error. File %s not found. Exiting\n",argv[1]);
		return 0;
	}
	wordBuffer = (char *)malloc(2000);

	c = 0; /* buffer counter */

	while ((ch = fgetc(file)) != EOF) {
		if (isalpha(ch)) { /* char is letter, add it */
			wordBuffer[c] = ch;
			c++;
		}
		else if (isdigit(ch) && c > 0) { /* char is number, and we have a partial word so we can add it */
			wordBuffer[c] = ch;
			c++;
		}
		else { /* char is non alphanumeric or it's a number at the beginning of a word, so we are done with current word */
			if (wordBuffer[0] != '\0') { /* make sure we have a word */
				processStr(wordBuffer);
			}
			memset(wordBuffer,'\0',sizeof(char)*strlen(wordBuffer)+1); /* empty buffer */
			c = 0; /* reset counter */
		}
	}
	if (wordBuffer[0] != '\0') {
		/* still have a word left in the buffer */
		head = insert(head,wordBuffer);
	}
	traverse(head);
	return 1;
}
void processStr(char* str) {
	head = insert(head,str);
}

void printResult() {
	traverse(head);
}

void traverse(struct node *n) {
	int i;
        if (n->left != NULL) {
                traverse(n->left);
        }

        for (i = 0; i < strlen(n->word); i++) {
                n->word[i] = tolower(n->word[i]);
        }
        printf("%s\t%d\t%d\n",n->word,n->count,n->count + n->similarCount);
        if (n->right != NULL) {
                traverse(n->right);
        }
}
 
