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

Node* GetE(){						// + -
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

Node* GetT(){							// /  and *
	Node* node = NULL;
	Node* r;
	Node* l = GetS();
	while(s[p] == '*' || s[p] == '/'){
		char oper = s[p];
		p++;
		r = GetS();
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


Node* GetS(){							// ^
	Node* node = NULL;
	Node* r;
	Node* l = GetP();
	while(s[p] == '^'){
		char oper = s[p];
		p++;
		r = GetP();
		if(!node){
			node = CreateNewNode(OPER,ELEV,l,r);
			continue;
		}
		else{
			l = node;	
			node = CreateNewNode(OPER,ELEV,l,r);
			continue;
		}
		
	}
	if(node)
		return node;
	return l;
}

Node* GetP(){												// braces  trygonometry and x
	
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
	if(s[p] == 's'){
		p++;
		if(s[p] == 'i'){
			p++;
			if(s[p] == 'n'){
				p++;
				Node* l = GetP();
				Node* val = CreateNewNode(FUNC,SIN,l,NULL);
				return val;
			}
			printf("Invalid function \n");
			assert(0);
		}
		if(s[p] == 'h'){
			p++;
			Node* l = GetP();
			Node* val = CreateNewNode(FUNC,SH,l,NULL);
			return val;
		}
		else{
			printf("Invalid function\n");
			assert(0);
		}
	}
	
	if(s[p] == 'c'){
		p++;
		if(s[p] == 'o'){
			p++;
			if(s[p] == 's'){
				p++;
				Node* l = GetP();
				Node* val = CreateNewNode(FUNC,COS,l,NULL);
				return val;
			}
			printf("Invalid function \n");
			
		}
		if(s[p] == 'h'){
			p++;
			Node* l = GetP();
			Node* val = CreateNewNode(FUNC,CH,l,NULL);
			return val;
		}
		else{
			printf("Invalid function\n");
			assert(0);
		}
	}	
	
	if(s[p] == 't'){
		p++;
		if(s[p] == 'a'){
			p++;
			if(s[p] == 'n'){
				p++;
				Node* l = GetP();
				Node* val = CreateNewNode(FUNC,TG,l,NULL);
				return val;
			}
			printf("Invalid function \n");
			assert(0);
		}
		else{
			printf("Invalid function\n");
			assert(0);
		}
	}
	if(s[p] == 'l'){
		p++;
		if(s[p] == 'n'){
			p++;

			Node* l = GetP();
			Node* val = CreateNewNode(FUNC,LN,l,NULL);
			return val;
			
			
		}
		else{
			printf("Invalid function\n");
			assert(0);
		}
	}
	
	
	else	
		return GetN();
}

Node* GetN(){						// numbers
	int val = 0;
	
	while('0' <= s[p] && s[p]<='9'){
		val = s[p] - '0' + 10*val;
		p++; printf("s[%d] = %c\n",p,s[p]);
	}	
	printf("ERR %c\n",s[p]);
	return CN(val,NUM);
}