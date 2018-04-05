#include "difparser.h"

int p = 0;
char* s;

Node* GetG( char* str){
	s = str;
	p = 0;
	Node* node = new (Node);
	node = GetE();
	assert(s[p] == '\0');
	
	return node;
}

Node* GetE(){
	Node* node = NULL;
	Node* r;
	Node* l = GetT();
	while(s[p] == '+' || s[p] == '-'){
		char oper = s[p];
		p++; printf("s[%d] = %c\n",p,s[p]);
		r = GetT();
		if(!node){
			if(oper == '+')		
				node = CreateNewNode(OPER,PLUS,l,r);
			if(oper == '-')
				node = CreateNewNode(OPER,MINUS,l,r);
			continue;
		}
		else{
			l = node;
			if(oper == '+')		
				node = CreateNewNode(OPER,PLUS,l,r);
			if(oper == '-')
				node = CreateNewNode(OPER,MINUS,l,r);
			continue;
		}
	}
	if(node)
		return node;
	return l;
}

Node* GetT(){
	Node* node = NULL;
	Node* r;
	Node* l = GetP();
	while(s[p] == '*' || s[p] == '/'){
		char oper = s[p];
		p++;
		r = GetP();
		if(!node){
			if(oper == '*')		
				node = CreateNewNode(OPER,MULT,l,r);
			if(oper == '/')
				node = CreateNewNode(OPER,DIV,l,r);
			continue;
		}
		else{
			l = node;
			if(oper == '*')		
				node = CreateNewNode(OPER,MULT,l,r);
			if(oper == '/')
				node = CreateNewNode(OPER,DIV,l,r);
			continue;
		}
		
	}
	if(node)
		return node;
	return l;
}

Node* GetP(){
	
	if(s[p] == '('){
		p++; printf("s[%d] = %c\n",p,s[p]);
		Node* val = GetE();
		assert(s[p] == ')');
		p++; printf("s[%d] = %c\n",p,s[p]);
		printf ("meow");
		return val;
	}
	if(s[p] == 'x'){
		p++;
		return CN(x,VAR);
	}	
	else	
		return GetN();
}

Node* GetN(){
	int val = 0;
	
	while('0' <= s[p] && s[p]<='9'){
		val = s[p] - '0' + 10*val;
		p++; printf("s[%d] = %c\n",p,s[p]);
	}	
	printf("ERR %c\n",s[p]);
	return CN(val,NUM);
}