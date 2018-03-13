#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum var_type{
	NUM = 1,
	VAR = 2,
	OPER = 3,
	FUNC = 4
	
};

typedef struct Node{
	
	char value[5];
	int type;
	struct Node * left;
	struct Node * right;
	
} Node, *pNode ; 

#define	ZERO CreateNewNode(dst,NUM,"0",NULL,NULL)
#define ONE CreateNewNode(dst,NUM,"1",NULL,NULL)
#define PLUS(L,R) CreateNewNode(dst,OPER,"+",L,R)
#define MINUS(L,R) CreateNewNode(dst,OPER,"-",L,R)
#define MULT(L,R) CreateNewNode(dst,OPER,"*",L,R)
#define DIV(L,R) CreateNewNode(dst,OPER,"/",L,R)
#define ELEV(L,R) CreateNewNode(dst,OPER,"^",L,R)

void DeleteTree(pNode root);
void CreateExample(pNode root);
void AltSaveInfoInFile(FILE* file, pNode root);
pNode Differentiate(const pNode src);
pNode CreateNewNode(pNode dst,const int type,const char* value,const pNode L,const pNode R);
pNode Copy(pNode node);
int main(){
	pNode root = (pNode) calloc (1,sizeof(Node));
	root->left = (pNode) calloc (1,sizeof(Node));
	root->left->left = (pNode) calloc (1,sizeof(Node));
	root->left->right = (pNode) calloc (1,sizeof(Node));
	root->right = (pNode) calloc (1,sizeof(Node));
	root->right->right = (pNode) calloc (1,sizeof(Node));
	root->right->left = (pNode) calloc (1,sizeof(Node));
	pNode res  = NULL;
	
	printf("main 0\n");
	CreateExample(root);
	printf("main 1\n");
	res = Differentiate(root);
	printf("main 2\n");
	AltSaveInfoInFile(stdout,res);
	printf("\n");
	AltSaveInfoInFile(stdout,root);
		printf("\n");
	
	DeleteTree(root);
	DeleteTree(res);
	printf("main 3\n");
	
	

	return 0;
}


void CreateExample(pNode root){
	

	strcpy(root -> value,"^");
	strcpy(root->left->value,"ln");
	strcpy(root->left->left->value,"x");
	strcpy(root ->right->value,"x");
	
	root->right->right = NULL;
	root->right->left = NULL;
	root->left->right = NULL;
	root->left->left->right = NULL;
	root->left->left->left = NULL;

	
	root->type = OPER;
	root->left->type = FUNC;
	root->left->left->type = VAR;
	root->right->type = VAR;

	
	
}

void AltSaveInfoInFile(FILE* file, pNode root){
	
	
	if(root->left && root->right && (root->type != FUNC)){
		if(root->left == NULL){
			printf("ERR no left pointer in question\n");
			abort();
		}
		
		if(root->left->type == OPER )
			fprintf(file,"(");
		AltSaveInfoInFile(file,root->left);
		if(root->left->type == OPER )
			fprintf(file,")");
			
		fprintf(file,root->value);
		
		if(root->right == NULL){
			printf("ERR no right pointer in question \n");
			abort();
		}
		
		if(root->right->type == OPER )
			fprintf(file,"(");
		AltSaveInfoInFile(file,root->right);
		if(root->right->type == OPER )
			fprintf(file,")");
	}
	if(root->type == FUNC){
		fprintf(file,root->value);
		fprintf(file,"(");
		AltSaveInfoInFile(file,root->left);
		fprintf(file,")");
	}
	
	if(root->type == VAR || root->type == NUM)
		fprintf(file,root->value);
}

pNode Differentiate(const pNode src){
	

	
	if(!src)
		return NULL;
	pNode dst = (pNode) calloc (1,sizeof(Node));

	switch(src->type){
		case VAR : {
			ONE;
			break;
		}
		case NUM : {
			ZERO;
			break;
		}
		case OPER:{
			if(!strcmp(src->value,"+")){
				dst->right = (pNode) calloc (1,sizeof(Node));
				dst->left = (pNode) calloc (1,sizeof(Node));
				PLUS(Differentiate(src->left),Differentiate(src->right));
			
			
			}
			
			if(!strcmp(src->value,"-")){
				dst->right = (pNode) calloc (1,sizeof(Node));
				dst->left = (pNode) calloc (1,sizeof(Node));
				MINUS(Differentiate(src->left),Differentiate(src->right));
			}
			if(!strcmp(src->value,"*")){

				dst->left = (pNode) calloc (1,sizeof(Node));
				dst->left->left = (pNode) calloc (1,sizeof(Node));
				dst->left->right = (pNode) calloc (1,sizeof(Node));
				dst->right = (pNode) calloc (1,sizeof(Node));
				dst->right->right = (pNode) calloc (1,sizeof(Node));
				dst->right->left = (pNode) calloc (1,sizeof(Node));

				PLUS(CreateNewNode(dst->left,OPER,"*",Differentiate(src->left),Copy(src->right)),CreateNewNode(dst->right,OPER,"*",Copy(src->left),Differentiate(src->right)));
			}
			if(!strcmp(src->value,"/")){
				
				dst->left = (pNode) calloc (1,sizeof(Node));
				dst->left->left = (pNode) calloc (1,sizeof(Node));
				dst->left->right = (pNode) calloc (1,sizeof(Node));
				dst->right = (pNode) calloc (1,sizeof(Node));
				dst->right->right = (pNode) calloc (1,sizeof(Node));
				dst->right->left = (pNode) calloc (1,sizeof(Node));
				
				
				
				pNode L = CreateNewNode(dst->left,OPER,"-",CreateNewNode(dst->left->left,OPER,"*",Differentiate(src->left),Copy(src->right)),CreateNewNode(dst->left->right,OPER,"*",Copy(src->left),Differentiate(src->right)));
				pNode R = CreateNewNode(dst->right,OPER,"*",Copy(src->left),Copy(src->left));
				DIV(L,R);
			}
			if(!strcmp(src->value,"^")){
				dst->left = (pNode) calloc (1,sizeof(Node));
				dst->left->left = (pNode) calloc (1,sizeof(Node));
				dst->left->right = (pNode) calloc (1,sizeof(Node));
				dst->right = (pNode) calloc (1,sizeof(Node));
				dst->right->right = (pNode) calloc (1,sizeof(Node));
				dst->right->left = (pNode) calloc (1,sizeof(Node));
				
				
				pNode tmp = (pNode) calloc (1,sizeof(Node));
				strcpy(tmp->value , "ln");
				tmp->type = FUNC;
				tmp->left = Copy(src->left);
				tmp->right = NULL;
				
				pNode L = Copy(src);
				pNode R = CreateNewNode(dst->right,OPER,"+",CreateNewNode(dst->right->left,OPER,"*",Differentiate(src->right),tmp),CreateNewNode(dst->right->right,OPER,"*",Copy(src->right),Differentiate(tmp)));
				MULT(L,R);
			}
		}
		case FUNC:{
			if(!strcmp(src->value,"ln")){
				dst->left = (pNode) calloc (1,sizeof(Node));
				
				
				pNode tmp = (pNode) calloc (1,sizeof(Node));
				strcpy(tmp->value,"1");
				tmp->left =NULL;
				tmp->right = NULL;
				tmp->type = NUM;
				
				MULT(CreateNewNode(dst->left,OPER,"/",tmp,Copy(src->left)),Differentiate(src->left));
			}
			
				
			
		}	
	}
	return dst;
}

pNode CreateNewNode(pNode dst,const int type,const char* value,const pNode L,const pNode R){
	
	strcpy(dst->value, value);
	dst->type = type;
	dst->left = L;
	dst->right = R;
	
	return dst;
}

void DeleteTree(pNode root){
	if(root == NULL)
		return;
	DeleteTree(root->left);
	DeleteTree(root->right);
	free(root);
	
}


pNode Copy(pNode node){
	if(node){	
		pNode cpy = (pNode) calloc (1,sizeof(Node));
		cpy->left = Copy(node->left);
		cpy->right = Copy(node->right);
		strcpy(cpy->value,node->value);
		cpy->type = node->type;
		return cpy;
	}
	return NULL;
}
