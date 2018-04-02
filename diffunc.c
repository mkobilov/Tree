#include "diff.h"

Node* CN(int v,int t){
	Node* dst = new (Node);
	dst->value = v;
	dst->type = t;
	dst->left  = NULL;
	dst->right = NULL;
	
	
	return dst;
}

Node _no_alloc_CN(int v,int t){
	Node dst;
	
	dst.value = v;
	dst.type = t;
	dst.left  = NULL;
	dst.right = NULL;
	
	
	return dst;
}

Node* CreateExample(){
	
	

	Node* root = CN(PLUS,OPER);
	root->left = CN(DIV,OPER);
	root->left->right = CN(COS,FUNC);
	root->left->right->left = CN(PLUS,OPER);
	root->left->right->left->left = CN(ELEV,OPER);
	root->left->right->left->left->left = CN(SIN,FUNC);
	root->left->right->left->left->left->left = CN(x,VAR);
	root->left->right->left->left->right = CN(2,NUM);
	root->left->right->left->right = CN(MULT,OPER);
	root->left->right->left->right->left = CN(4,NUM);
	root->left->right->left->right->right = CN(x,VAR);
	root->left->left = CN(ELEV,OPER);
	root->left->left->right = CN(PLUS,OPER);
	root->left->left->right->left = CN(SIN,FUNC);
	root->left->left->right->left->left = CN(x,VAR);
	root->left->left->right->right = CN(LN,FUNC);
	root->left->left->right->right->left = CN(MINUS,OPER);
	root->left->left->right->right->left->left = CN(ELEV,OPER);
	root->left->left->right->right->left->left->left = CN(x,VAR);
	root->left->left->right->right->left->left->right = CN(2,NUM);
	root->left->left->right->right->left->right = CN(4,NUM);
	root->left->left->left = CN(x,VAR);
	
	
	root->right = CN(3,NUM);
	
	
	return root;
}

void AltSaveInfoInFile(FILE* file, Node* root){
	if(!root){
		return;
	}
	if(root->left && root->right && (root->type == OPER)){
		
		
		if(root->left->type == OPER )
			fprintf(file,"(");
		AltSaveInfoInFile(file,root->left);
		if(root->left->type == OPER )
			fprintf(file,")");
			
		PrintValue(file,root);
		
		
		
		if(root->right->type == OPER )
			fprintf(file,"(");
		AltSaveInfoInFile(file,root->right);
		if(root->right->type == OPER )
			fprintf(file,")");
	}
	if(root->type == FUNC){
		PrintValue(file,root);
		fprintf(file,"(");
		AltSaveInfoInFile(file,root->left);
		fprintf(file,")");
	}
	
	if(root->type == VAR || root->type == NUM){
		if(root->value < 0){
			fprintf(file,"(");
			PrintValue(file,root);
			fprintf(file,")");
		}
		
		PrintValue(file,root);
	}
}

Node* Differentiate(const Node* src){

	Node* dst ;
	
	
	
	if(src == NULL){
		printf("nothing to diffirintiate\n");
		return NULL;
	}

	switch(src->type){
		case VAR : {
			dst = CreateNewNode(NUM,1,NULL,NULL);
			break;
		}
		case NUM : {
			dst = ZERO;
			break;
		}
		case OPER:{
			if(src->value == PLUS){

				dst = PLUS(Differentiate(src->left),Differentiate(src->right));
			
			
			}
			
			if(src->value == MINUS){

				dst = MINUS(Differentiate(src->left),Differentiate(src->right));
			}
			if(src->value == MULT){



				dst = PLUS(CreateNewNode(OPER,MULT,Differentiate(src->left),Copy(src->right)),CreateNewNode(OPER,MULT,Copy(src->left),Differentiate(src->right)));
			}
			if(src->value == DIV){
				Node* L = CreateNewNode(OPER,MINUS,CreateNewNode(OPER,MULT,Differentiate(src->left),Copy(src->right)),CreateNewNode(OPER,MULT,Copy(src->left),Differentiate(src->right)));
				Node* R = CreateNewNode(OPER,MULT,Copy(src->right),Copy(src->right));
				dst = DIV(L,R);
			}
			if(src->value == ELEV){

				
				
				Node* tmp = (Node*) calloc (1,sizeof(Node));
				tmp->value = LN;
				tmp->type = FUNC;
				tmp->left = Copy(src->left);
				tmp->right = NULL;
				
				Node* L = Copy(src);
				
				Node* R = CreateNewNode(OPER,PLUS,CreateNewNode(OPER,MULT,Differentiate(src->right),tmp),CreateNewNode(OPER,MULT,Copy(src->right),Differentiate(tmp)));
				dst = MULT(L,R);
			}
			break;
		}
		case FUNC:{
			if(src->value == LN){
				
				Node* tmp ;
				
				tmp = CreateNewNode(NUM,1,NULL,NULL);
				dst = MULT(CreateNewNode(OPER,DIV,tmp,Copy(src->left)),Differentiate(src->left));
			}
			
			if(src->value == SIN){
				dst = MULT(CreateNewNode(FUNC,COS,Copy(src->left),NULL),Differentiate(src->left));

			}
			
			if(src->value == COS){
				
				Node* L = CreateNewNode(OPER,MULT,CreateNewNode(FUNC,SIN,Copy(src->left),NULL),Differentiate(src->left));
				Node* R = CreateNewNode(NUM,-1,NULL,NULL);
				dst = MULT(L,R);
			}	
			if(src->value == SH){
				dst = MULT(CreateNewNode(FUNC,CH,Copy(src->left),NULL),Differentiate(src->left));

			}
			if(src->value == CH){
				dst = MULT(CreateNewNode(FUNC,SH,Copy(src->left),NULL),Differentiate(src->left));

			}	
			if(src->value == TG){
				dst = CreateNewNode(OPER,MULT,CreateNewNode(OPER,DIV,ONE,CreateNewNode(OPER,ELEV,CreateNewNode(FUNC,COS,Copy(src->left),NULL),CreateNewNode(NUM,2,NULL,NULL))),Differentiate(src->left));
			}
			
			break;
		}	
	}
	return dst;
}

Node* CreateNewNode(const int type,const int value, Node* L, Node* R){
	


	Node* dst = new (Node);
	dst->value = value;
	dst->type = type;
	dst->left = L;
	dst->right = R;
	
	return dst;
}

void DeleteTree(Node* root){
	if(root == NULL)
		return;
	if(root->left)
		DeleteTree(root->left);
	root->left = NULL;
	if(root->right)
		DeleteTree(root->right);
	root->right = NULL;
	delete(root);
	
}


Node* Copy(const Node* node){
	if(node){	

		Node* cpy = new (Node);
		if(node->left)
			cpy->left = Copy(node->left);
		else cpy->left = NULL;
		if(node->right)
			cpy->right = Copy(node->right);
		else	
			cpy->right = NULL;
		cpy->value = node->value;
		cpy->type = node->type;
		return cpy;
	}
	return NULL;
}

void PrintValue(FILE* file, Node* node){
	if(node->type == VAR){
		fprintf(file,"x");
		return;
	}
	
	if(node->type == NUM){
		fprintf(file,"%d",node->value);
		return;
	}
	
	if(node->type == OPER){
		switch(node->value){
			case(PLUS):{
				 fprintf(file,"+");
				 return;
			}
			case(MINUS):{
				 fprintf(file,"-");
				 return;
			}
			case(MULT):{
				 fprintf(file,"\\cdot ");
				 return;
			}
			case(DIV):{
				 fprintf(file,"/");
				 return;
			}
			case(ELEV):{
				 fprintf(file,"^");
				 return;
			}
		}
	}
	if(node->type == FUNC){
		if(node->value == LN){
			 fprintf(file,"ln");
			 return;
		}
		if(node->value == SIN){
			fprintf(file,"sin");
			return;
		}
		if(node->value == COS){
			fprintf(file,"cos");
			return;
		}
		if(node->value == SH){
			fprintf(file,"sh");
			return;
		}
		if(node->value == CH){
			fprintf(file,"ch");
			return;
		}
		if(node->value == TG){
			fprintf(file,"tg");
			return;
		}
	
	}
	
}



int AreNums(const Node* r,const Node* l){
	return ((r->type == NUM) && (l->type == NUM));
}




void DotDump(Node* n)
{
	FILE* output = fopen("dump.gv", "w");
	fprintf(output, "digraph dump {\n node [shape = record];\n");
	_DotDump(n, output);
	fprintf(output, "}");
	fclose(output);
	system ("dump.gv");
}

void _DotDump(Node* n, FILE* output){
	

	fprintf(output, "%d [shape = record, label = \"{pointer: %p|type: %d|value: ",n, n , n->type);
	PrintValue(output,n);
	
	
	fprintf(output, " |left: %p|right: %p}\"];",
	 n->left, n->right);
	
	
	if(n -> left != NULL){
		fprintf(output, "%d -> %d\n", (long int)n, (long int)n->left);
		_DotDump(n -> left, output);
	}
	if(n -> right != NULL){
		fprintf(output, "%d -> %d\n", (long int)n, (long int)n->right);
		_DotDump(n -> right, output);
	}

}


void SimplifyZero(Node* root){
	switch (root->type){
		case(FUNC): {
			SimplifyZero(root->left);
			break;
		}
		case(NUM): return ;
		case(VAR): return ;
		case(OPER):{
			if(root->value == MULT && root->left->type == NUM && root->left->value == 0){
				root->value = 0;
				root->type = NUM;
				DeleteTree(root->left);
				DeleteTree(root->right);
				root->left=NULL;
				root->right=NULL;
				change++;
			}
			if(root->value == MULT && root->right->type == NUM && root->right->value == 0){
				root->value = 0;
				root->type = NUM;
				DeleteTree(root->left);
				DeleteTree(root->right);
				root->left=NULL;
				root->right=NULL;
				change++;
			}	
			
			
			if(root->value == PLUS && root->left->type == NUM && root->left->value == 0){
				Node* tmp;
				delete(root->left);
				root->left = root->right->left;
				root->value = root->right->value;
				root->type = root->right->type;
				tmp = root->right->right;
				root->right->right = NULL;
				root->right->left = NULL;
				
				delete(root->right);
				root->right = tmp;
				change++;
				
			}
			if(root->value == PLUS && root->right->type == NUM && root->right->value == 0){
				Node* tmp;
				delete(root->right);
				root->right = root->left->right;
				root->value = root->left->value;
				root->type = root->left->type;
				tmp = root->left->left;
				
				root->left->right = NULL;
				root->left->left = NULL;
				
				delete(root->left);
				root->left = tmp;
				change++;
			}
			if(root->value == MINUS && root->right->type == NUM && root->right->value == 0){
				Node* tmp;
				delete(root->right);
				root->right = root->left->right;
				root->value = root->left->value;
				root->type = root->left->type;
				tmp = root->left->left;
				
				root->left->right = NULL;
				root->left->left = NULL;
				
				delete(root->left);
				root->left = tmp;
				change++;
			}
			if(root->left)
				SimplifyZero(root->left);
			if(root->right)
				SimplifyZero(root->right);
		}

	}
}
void SimplifyONE(Node* root){
	switch (root->type){
		case(FUNC): {
			SimplifyONE(root->left);
			break;
		}
		case(NUM): return ;
		case(VAR): return ;
		case(OPER):{
			if(root->value == MULT && root->type == OPER && root->left->value == 1 && root->left->type == NUM){
				Node* tmp;
				DeleteTree(root->left);
				root->left = root->right->left;
				root->value = root->right->value;
				root->type = root->right->type;
				tmp = root->right->right;

				root->right->right = NULL;
				root->right->left = NULL;
				
				DeleteTree(root->right);
				root->right = tmp;
				change++;
			}
			if(root->value == MULT && root->type == OPER && root->right->value == 1 && root->right->type == NUM){
				Node* tmp;
				delete(root->right);
				root->right = root->left->right;
				root->value = root->left->value;
				root->type = root->left->type;
				tmp = root->left->left;
				
				root->left->right = NULL;
				root->left->left = NULL;
				
				DeleteTree(root->left);
				root->left = tmp;
				change++;
			}
			if(root->left)
				SimplifyONE(root->left);
			if(root->right)	
				SimplifyONE(root->right);
			break;
		}
	}
}

Node SimplifyConstants(Node* root){
	Node res = _no_alloc_CN(0,0);
	
	Node lres = _no_alloc_CN(0,0);
	Node rres = _no_alloc_CN(0,0);
	switch(root->type){
		case(OPER):{
			if(!AreNums(root->left,root->right)){
				rres = SimplifyConstants(root->right);
				lres = SimplifyConstants(root->left);
				if(((lres.type == FAIL) || (rres.type == FAIL))){
					res.type = FAIL;

					return res;
				}
				
			}
			if(AreNums(root->left,root->right)){
				switch(root->value){
					case(PLUS):{
						change++;
						root->value = root->left->value + root->right->value;
						DeleteTree(root->left);
						DeleteTree(root->right);
						root->left = NULL;
						root->right = NULL;
						root->type = NUM;
						break;
					}
					case(MULT):{
						change++;
						root->value = root->left->value * root->right->value;
						DeleteTree(root->left);
						DeleteTree(root->right);
						root->left = NULL;
						root->right = NULL;
						root->type = NUM;
						break;
					}
					case(MINUS):{
						change++;
						root->value = root->left->value - root->right->value;
						DeleteTree(root->left);
						DeleteTree(root->right);
						root->left = NULL;
						root->right = NULL;
						root->type = NUM;
						break;
					}
					case(DIV):{
						change++;
						root->value = root->left->value / root->right->value;
						DeleteTree(root->left);
						DeleteTree(root->right);
						root->left = NULL;
						root->right = NULL;
						root->type = NUM;
						break;
					}
					
				}	
			}
			break;
		}
		case(VAR): {
			res.type = FAIL;
		
			break;
		}
		case(FUNC):  {
			res.type = FAIL;
		
			break;
		}	
		case(NUM):{
			break;
		}
	}

	return res;
}

void ezSimplify(Node* root){			//Simplify 0 and 1
	
	#ifndef _RELEASE_ 
	if(!root){
		printf("ERR no root found");
		abort;
	}
	#endif	
	
	SimplifyONE(root);
	SimplifyZero(root);
	
	
}		

void Simplification(Node* root){
	change = 1;
	while(change != 0){
		change = 0;
		ezSimplify(root);
		SimplifyConstants(root);
	}
}

void TexDump(Node* root){
	FILE* file = fopen("tdump.tex","w");
	fprintf(file,"\\documentclass[10pt,a2paper]{article}\n \\usepackage[utf8]{inputenc} \n \\title{diftest} \n \\begin{document}\n $$ ");
	_TexDump(file,root);
	fprintf(file," $$ \n  \\end{document}\n");
	fclose(file);
	
	system ("latex tdump.tex");
	system("tdump.DVI");
	
}


void _TexDump(FILE* file,Node* root){
	
	if(!root){
		return;
	}

	if((root->type == OPER) && (root->value == DIV)){
		fprintf(file,"\\frac{");
		_TexDump(file,root->left);
		fprintf(file,"}");
		fprintf(file,"{");
		_TexDump(file,root->right);
		fprintf(file,"}");
		return;
	}
	
	else{
		if(root->left && root->right && (root->type == OPER)){
			
			
			if(root->left->type == OPER )

				fprintf(file,"\\left(");
			_TexDump(file,root->left);
			

			if(root->left->type == OPER )
				fprintf(file,"\\right)");
			
				
			PrintValue(file,root);
			
			
			
			if(root->type == OPER && root->value == ELEV)
					fprintf(file,"{");
			if(root->right->type == OPER )
				fprintf(file,"\\left(");
			_TexDump(file,root->right);
			if(root->right->type == OPER )
				fprintf(file,"\\right)");
			if(root->type == OPER && root->value == ELEV)
					fprintf(file,"}");
		}
		if(root->type == FUNC){
			PrintValue(file,root);
			fprintf(file,"(");
			_TexDump(file,root->left);
			fprintf(file,")");
		}
		
		if(root->type == VAR || root->type == NUM){
			if(root->value < 0){
				fprintf(file,"(");
				PrintValue(file,root);
				fprintf(file,")");
			}
			
			PrintValue(file,root);
		}
		return;
	}

	
}

