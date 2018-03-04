#ifndef _AKINATOR_H_
#define _AKINATOR_H_ 

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


#define _MAX_LINE_LENGTH_ 20
#define _MAX_ID_LENGTH_ 5
#define _MAX_RW_LINE_LENGTH_ 1000

typedef struct Node{
	
	char value[_MAX_LINE_LENGTH_];
	char id[_MAX_ID_LENGTH_];
	struct Node * left;
	struct Node * right;
	struct Node * parent;
} Node, *pNode;

void CreateBasicTree(pNode root);
void IsThereAnyLine(const char* line);
void IsCorrectNumber(const int number);
int IsProperAnswer(const char* answer);
void IsProperNode(const pNode node);
int IsQuestion(const pNode node);
int GetLine(FILE* file,char* line);
void GetChildStr(char* str, char* l_str, char* r_str, int sym_count);
void AltSaveInfoInFile(FILE* file, pNode root);
Node* AltReadInfoFromFile(char* str,pNode parent);
void CreateNewNode(pNode node,const char* name_of_new_element);
void Guesing(pNode root);

#include "akinatorfunc.c"
#endif
