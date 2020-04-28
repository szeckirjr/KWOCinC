/* kwoc3.c
 * Eduardo Szeckir
 * V00921126
 * Assignment 3 - SENG265
 */

#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "listy.h"

#define MAX_WORD_LEN 40
#define MAX_LINE_LEN 100

// toLowercase TRANSFORMS A TEXT FROM A NODE TO LOWERCASE
void toLowercase(node_t *node, void *arg){
	for(int i=0; i<strlen(node->text); i++){
		node->text[i]=(char)tolower((int)node->text[i]);
	}		
}

// lowerIt TRANSFORMS A STRING INTO LOWERCASE
char *lowerIt(char line[]){
	for(int i=0; i<strlen(line); i++){
		line[i]=(char)tolower((int)line[i]);
	}
	return line;
}

// upperIt TRANSFORMS A STRING INTO UPPERCASE
char *upperIt(char line[]){
	for(int i=0; i<strlen(line); i++){
		line[i]=(char)toupper((int)line[i]);
	}
	return line;
}

// readInputLines READS EVERY LINE FROM A FILE AND STORES EACH ONE IN A NODE IN A LINKED LIST
node_t *readInputLines(node_t *head, char* fileName){
	// OPEN FILE
	FILE *fp = fopen(fileName,"r");
	if(fp==NULL){
		printf("Unable to open file %s\n", fileName);
		exit(1);
	}
	
	// STORE EACH LINE IN A NEW NODE AND ADD THAT NODE TO THE END OF A LINKED LIST
	char currLine[MAX_LINE_LEN]="";
	node_t *temp_node=NULL;
	while(fgets(currLine, MAX_LINE_LEN,fp)){
		if(currLine!=NULL && strcmp(currLine,"")!=0 && strcmp(currLine,"\0")!=0){
			currLine[strlen(currLine)-1]='\0';
			temp_node = new_node(currLine);
			head = add_end(head, temp_node);
		}
	}
	fclose(fp);
	return head;
}

// readUniqueWords READS EVERY WORD FROM EVERY NODE OF A LINKED LIST AND ADDS TO THE END OF IT ALL THE UNIQUE WORDS
node_t *readUniqueWords(node_t *destination, node_t *source){

	// WHILE THERE IS A NODE TO READ
	while(source!=NULL){

		// COPY THE LINE INTO A CURRLINE STRING AND LOWER IT, SO WE CAN SEARCH THE LOWERCASE WORDS
		node_t *temp_node=NULL;
		char *currLine=(char *)emalloc(sizeof(char)*MAX_LINE_LEN);
		strncpy(currLine,source->text,MAX_LINE_LEN);
		currLine=lowerIt(currLine);

		// LOOK AT EVERY SINGLE WORD IN THE LINE
		char *currWord = strtok(currLine," ");
		while(currWord!=NULL){

			// COMPARE EACH WORD TO ALL THE WORDS BEFORE
			node_t *p = destination;
			int insert = 1;
			while(p!=NULL){
				if(strcmp(p->text,currWord)==0){
					insert=0;
					break;
				}
				p = p->next;	
			}

			// IF WORD IS DIFFERENT THAN ALL WORDS BEFORE IT, THEN INSERT INTO DESTINATION LIST
			if(insert==1){
				if(strcmp(currWord,"\n")!=0){
					temp_node = new_node(currWord);
					destination = add_end(destination, temp_node);
				}
			}
			currWord = strtok(NULL, " ");
		}
		source = source->next;
		free(currLine);
	}
	return destination;
}


// removeExceptionWords REMOVES ALL WORDS FROM A LINKED LIST OF WORDS THAT ARE IN ANOTHER LINKED LIST OF WORDS
node_t *removeExceptionWords(node_t *words, node_t *exception){
	
	// CREATES NEW LINKED LIST TO STORE ALL FINAL WORDS
	node_t *new = NULL;

	// WHILE THERE IS ANOTHER WORD TO CHECK
	while(words!=NULL){

		// COMPARE THAT WORD TO ALL WORDS TO BE REMOVED
		node_t *p = exception;
		int insert=1;
		while(p!=NULL){
			if(strcmp(p->text,words->text)==0){
				insert=0;
				break;
			}
			p=p->next;
		}

		// IF WORD IS NOT THE SAME AS ALL OF THE REMOVE WORDS, THEN ADD THE WORD TO A NODE AND ADD THE NODE TO THE FINAL WORDS LIST
		if(insert==1){
			node_t *temp = new_node(words->text);
			new = add_end(new,temp);
		}
		words=words->next;
	}
	return new;
}

// sortAlphabetically SORTS A LINKED LIST OF WORDS IN ALPHABETICAL ORDER
node_t *sortAlphabetically(node_t *head){

	// WHILE THERE IS ANOTHER WORD TO CHECK
	node_t *p = head;
	while(p!=NULL){

		// COMPARE IT TO ALL THE NEXT WORDS AND SWAP NODE TEXTS IF NECESSARY
		node_t *t = p->next;
		while(t!=NULL){
			if(strcmp(p->text,t->text)>0){
				char temp[MAX_WORD_LEN];
				strncpy(temp,p->text,MAX_WORD_LEN);
				strncpy(p->text,t->text,MAX_WORD_LEN);
				strncpy(t->text,temp,MAX_WORD_LEN);
			}
			t = t->next;
		}
		p = p->next;
	}
	return head;	
}

// findMaxLength FINDS THE MAX WORD LENGTH IN A LINKED LIST OF WORDS
int findMaxLength(node_t *head){

	// WHILE THERE IS ANOTHER WORD TO CHECK
	int max=0;
	node_t *p=head;
	while(p!=NULL){

		// IF THE LENGTH OF THE CURRENT WORD IS MORE THAN THE MAX LENGTH FOUND SO FAR, THEN UPDATE MAX
		if(strlen(p->text)>max){
			max = strlen(p->text);
		}
		p=p->next;
	}
	return max;
}


// printOutput PRINTS THE OUTPUT AS REQUESTED IN ASSIGNMENT
void printOutput(node_t *words, node_t *lines, int maxLength){

	// WHILE THERE IS ANOTHER WORD TO CHECK
	node_t *currWord= words;
	while(currWord!=NULL){

		// CHECK WORD IN EVERY LINE IN THE FILE
		node_t *currLine = lines;
		int linecount = 1;
		while(currLine!=NULL){

			// COPY THE LINE INTO A TEMP STRING, SO IT CAN BE A LOWERCASE AND YOU CAN SEARCH THE WORD
			char *tempLine=(char *)emalloc(sizeof(char)*MAX_LINE_LEN);
			strncpy(tempLine,currLine->text,MAX_LINE_LEN);
			tempLine = lowerIt(tempLine);	
			char *newLine = strstr(tempLine, currWord->text);
	
			// IF WORD WAS FOUND WITHIN THE LINE, SPLIT THE LINE IN WORDS AND COMPARE EVERY WORD
			if(newLine!=NULL){
				char buffer[MAX_LINE_LEN];
				strncpy(buffer, tempLine,MAX_LINE_LEN);
				char *t = strtok(buffer," ");
				int freq = 0;

				// CHECK EVERY WORD AND IF IT IS EQUAL, THEN ADD TO THE FREQUENCY
				while(t!=NULL){
					if(strcmp(t,currWord->text)==0){
						freq++;
					}
					t=strtok(NULL," ");
				}

				// 
				if(freq!=0){
					int spaces = maxLength-(int)strlen(currWord->text)+2;
					char *newWord=(char *)emalloc(sizeof(char)*MAX_WORD_LEN);
					strncpy(newWord, currWord->text,MAX_WORD_LEN);
					newWord = upperIt(newWord);
					printf("%s", newWord);
					free(newWord);
					for(int i=0; i<spaces; i++){
						printf(" ");
					}
					printf("%s ", currLine->text);
					if(freq>1){
						printf("(%d*)\n",linecount);
					} else {
						printf("(%d)\n",linecount);
					}
				}
			}
			currLine=currLine->next;
			linecount++;
			free(tempLine);
		}
		currWord = currWord->next;
	}
}

int main(int argc, char *argv[]){

	// SET EXCEPTION FILE/INPUT FILE NAMES
	char *exception_file = NULL;
	char *input_file = NULL;
	if(argc<2){
		printf("You ned to set an input file.\n");
	} else if (argc==2){
		input_file = argv[1];
	} else if (strcmp(argv[1],"-e")==0){
		input_file = argv[3];
		exception_file = argv[2];
	} else if (strcmp(argv[2],"-e")==0){
		input_file = argv[1];
		exception_file = argv[3];
	}

	// CREATE LINES ARRAY BY STORING ALL INPUT LINES INTO NODES BY READING FROM THE FILE
	// NODE LINESHEAD IS THE BEGINNING OF THE LINKED LIST
	node_t *linesHead = NULL;
	linesHead = readInputLines(linesHead,input_file);

	// CREATE WORDS ARRAY BY STORING ALL INPUT WORDS INTO NODES BY READING FROM EVERY LINE FROM LINES LIST
	// NODE WORDSHEAD IS THE BEGINNING OF THE LINKED LIST
	node_t *wordsHead = NULL;
	wordsHead = readUniqueWords(wordsHead, linesHead);

	// IF EXCEPTION FILE IS NOT NULL (I.E. A FILE WAS GIVEN), THEN:
	// 1. READ EVERY WORD OF THE EXCEPTION FILE AND STORE IT INTO AN EXCEPTION LINKED LIST
	// 2. REMOVING EACH EXCEPTION WORD FROM THE LINKED LIST AND SETTING THE WORDS HEAD TO BE THE NEW LINKED LIST
	if(exception_file!=NULL){
		node_t *exceptionHead = NULL;
		exceptionHead = readInputLines(exceptionHead,exception_file);
		wordsHead = removeExceptionWords(wordsHead,exceptionHead);
	}

	// SORT WORDS ARRAY ALPHABETICALLY
	wordsHead = sortAlphabetically(wordsHead);
		
	// FIND MAX LENGTH OF ALL WORDS
	int maxLength = findMaxLength(wordsHead);

	// PRINTS OUTPUT BY SENDING WORDS, LINES AND MAX WORD LENGTH
	printOutput(wordsHead, linesHead, maxLength);
	
	// EXIT WITH 0 IF SUCCESSFUL
	exit(0);
}
