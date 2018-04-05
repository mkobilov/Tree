#ifndef __DIFPARSER_H__
#define __DIFPARSER_H__
#include "diff.h"

extern char* s ;
extern int p ;
extern int change ;



Node* GetG(char* str);
Node* GetE();
Node* GetT();
Node* GetP();
Node* GetN();
#endif