#ifndef _DIFFERENTIATOR_H_
#define _DIFFERENTIATOR_H_
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int change = 0;

enum node_type{
	NUM = 1,
	VAR = 2,
	OPER = 3,
	FUNC = 4,
	FAIL = 5
};

enum functions_and_vars{
	PLUS = 1,
	MINUS = 2,
	MULT = 3,
	DIV = 4,
	ELEV = 5,
	LN = 6,
	x = 7,
	SIN = 8,
	COS = 9,
	SH = 10,
	TG = 11,
	CH = 12,
	
};

typedef struct Node{
	
	int value;
	int type;
	struct Node * left;
	struct Node * right;
	
	
	
}Node; 

#define	ZERO CreateNewNode(NUM,0,NULL,NULL)
#define ONE CreateNewNode(NUM,1,NULL,NULL)
#define PLUS(L,R) CreateNewNode(OPER,PLUS,L,R)
#define MINUS(L,R) CreateNewNode(OPER,MINUS,L,R)
#define MULT(L,R) CreateNewNode(OPER,MULT,L,R)
#define DIV(L,R) CreateNewNode(OPER,DIV,L,R)
#define ELEV(L,R) CreateNewNode(OPER,ELEV,L,R)


void SimplifyONE(Node* root);
void SimplifyZero(Node* root);
void ezSimplify(Node* root);
void Simplification(Node* root);
void DotDump(FILE* file,Node* root);
int AreNums(const Node* r,const Node* l);
int AreSimplified(Node* l, Node* r);
void TreeMemAlloc (int levels,Node* root);
void PrintValue(FILE* file, Node* node);
void DeleteTree(Node* root);
Node* CreateExample();
void AltSaveInfoInFile(FILE* file, Node* root);
Node* Differentiate(const Node* src);
Node* CreateNewNode(const int type,const int value, Node* L, Node* R);
Node* Copy(const Node* node);
Node SimplifyConstants(Node* root);
void DotDump(Node* n);
void _DotDump(Node* n, FILE* output);
Node* CN(int v,int t);
void Texdump(Node* root);
void _TexDump(FILE* file,Node* root);
#include "diffunc.c"
#endif