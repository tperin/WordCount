#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "node.h"


int main(int argc, char ** argv) {
	printf("test");
	struct node *head;
	printf("test2");
	FILE *file = fopen("test1.txt","r");
	if (file == NULL) {
		printf("Error opening file\n");
		return 1;
	}
	printf("test3");
	char ch;
	char *wordBuffer = (char *)malloc(2000);
	printf("test4");
	int c = 0; /* buffer counter */

	while ((ch = fgetc(file)) != EOF) {
		printf("%s\n",ch);
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
	print(head);
	return 1;
}
