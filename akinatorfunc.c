#ifndef _AKINATOR_H_
#define _AKINATOR_H_ 
#include "akinator.h"
#endif


void IsThereAnyLine(const char* line){
	assert(line != NULL);	
}
void IsCorrectNumber(const int number){
	assert(number <= 5);
	
}
int IsProperAnswer(const char* answer){
	if(!strcmp(answer,"yes") || !strcmp(answer,"no"))
		return 1;
	else {
		printf("This is not a proper answer (I understand only yes or no) \n");
		return 0;
	}
}
void IsProperNode(const pNode node){
	assert((node->left && node->right) || (!node->left && !node->right));
	
	return;
}
int IsQuestion(const pNode node){
	
	IsProperNode(node);
	if(node->left && node->right){
		return 1;
	}
	else
		return 0;
	
}

int GetLine(FILE* file,char* line){
	char ch;
	int length = 0;
	while(ch != '\n' && ch != EOF){
		ch = getc(file);
		line[length] = ch;
		++length;
	}
	line[length] = '\0';
	return length;
}

void CreateBasicTree(pNode root){


	root->left = (pNode) malloc (sizeof(Node));
	root->right = (pNode) malloc (sizeof(Node));

	strcpy(root->value ,"Alive");
	strcpy(root->left->value , "Frog");
	strcpy(root->right->value , "Book");

}
void GetChildStr(char* str, char* l_str, char* r_str, int sym_count){
	if(str[sym_count] == '\0'){
		l_str[0] = '\0';
		r_str[0] = '\0';
		return;
	}
	int brace = 0;
	char sym = '#';
	int i=0;
	brace++;
	for(i =0; brace; i++){
		sym = str[sym_count];
		sym_count++;
		if(sym == '(')
			brace++;
		if(sym == ')')
			brace--;
			
		if(brace){
			l_str[i] = sym;
		}
	}
	l_str[i] = '\0';
			
	brace++;
	sym_count++;
	for(i = 0; brace; i++){
	sym = str[sym_count];	
	sym_count++;
		if(sym == '(')
			brace++;
		if(sym == ')')
			brace--;
			
		if(brace){
			r_str[i] = sym;
		}
	}
	r_str[i] = '\0';
}
void AltSaveInfoInFile(FILE* file, pNode root){
	fprintf(file,root->value);
	if(root->left && root->right){
		if(root->left == NULL){
			printf("ERR no left pointer in question\n");
			abort();
		}
		fprintf(file,"(");
		AltSaveInfoInFile(file,root->left);
		fprintf(file,")");
		
		if(root->right == NULL){
			printf("ERR no right pointer in question \n");
			abort();
		}
		
		fprintf(file,"(");
		AltSaveInfoInFile(file,root->right);
		fprintf(file,")");
	}
	
	
}


void CreateNewNode(pNode node,const char* name_of_new_element){
	printf("What is the difference between %s and %s ?\n",node->value, name_of_new_element);
	char new_question[_MAX_LINE_LENGTH_];
	char user_answer[_MAX_LINE_LENGTH_];
	scanf("%*c");
	scanf("%[a-z ]",&new_question);
	
	printf("Is %s %s \n",node->value,new_question);
	do{
			scanf("%s",user_answer);
			}while(IsProperAnswer(user_answer) == 0);
			
	node->left = (pNode) malloc (sizeof(Node));	
	node->right = (pNode) malloc (sizeof(Node));
	
	node->right->left = NULL;		
	node->right->right =NULL;		
	node->left->left = NULL;		
	node->left->right =NULL;		
			
			
	if (!strcmp(user_answer,"yes")){
		strcpy(node->left->value, node->value);
		strcpy(node->right->value , name_of_new_element);
		strcpy(node->value , new_question);
	}
	else{
		strcpy(node->right->value, node->value);
		strcpy(node->left->value, name_of_new_element);
		strcpy(node->value , new_question);
	}

}

void Guesing(pNode root){
	pNode cur;
	char user_answer[_MAX_LINE_LENGTH_] = {};
	char user_answer_n[_MAX_LINE_LENGTH_] = {};
	do{
		cur = root;
	
		while(IsQuestion(cur)){
			
			printf("Is it  %s ?\n",cur->value);
			
			do{
			scanf("%s",&user_answer);
			}while(!IsProperAnswer(user_answer));
			
		
			if(!strcmp(user_answer,"yes"))
				cur = cur->left;
			else
				cur = cur->right;
			
		}
		
		printf("The answer is %s \n",cur->value);
		do{
			scanf("%s",&user_answer);
			}while(!IsProperAnswer(user_answer));
			
			
		if(!strcmp(user_answer,"yes")){
			printf("I'm always right \n");
		}
		else{
			printf("What is it?\n");
			scanf("%*c");
			scanf("%[a-z ]",&user_answer_n);
			
			CreateNewNode(cur,user_answer_n);
			printf("Congrats you've won \n");
		}
		
		printf("Do you want to play again? \n");
		do{
			scanf("%s",user_answer);
		}while(!IsProperAnswer(user_answer));
		

	} while(!strcmp(user_answer,"yes"));
	
	
}


Node* AltReadInfoFromFile(char* str,pNode parent){
	Node* ret = (Node*) malloc(sizeof(Node));
	
	ret->left = NULL;
	ret->right = NULL;
	ret->parent = parent;
	
	int sym_count = 0;
	char tmp = str[sym_count];
	while(tmp != '(' && tmp!='\0'){
		ret->value[sym_count] = tmp;
		sym_count++;
		tmp = str[sym_count];
	}
	ret->value[sym_count] = '\0';
	sym_count++;
	
	
	char* l_str = (char*)calloc(strlen(str),sizeof(char));
	char* r_str = (char*)calloc(strlen(str),sizeof(char));
	GetChildStr(str,l_str,r_str,sym_count);
	if(l_str[0] != '\0'){
		ret->left = AltReadInfoFromFile(l_str,ret);
		ret->right = AltReadInfoFromFile(r_str,ret);
	}
	free(l_str);
	free(r_str);


	return ret;
}

