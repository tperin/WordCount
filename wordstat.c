#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "node.h"


int main(int argc, char ** argv) {

	if (argc != 2) {
		printf("Invalid usage. Use -h flag for help\n");
		return 0;	
	}
	if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"-help") == 0) {
		printf("Usage: wordstat [-h] <filename>\n");
		return 0;
	}

	struct node *head = NULL;
	FILE *file = fopen(argv[1],"r");
	if (file == NULL) {
		printf("Error. File %s not found. Exiting\n",argv[1]);
		return 0;
	}
	char ch;
	char *wordBuffer = (char *)malloc(2000);
	int c = 0; /* buffer counter */

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
				head = insert(head,wordBuffer);
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
