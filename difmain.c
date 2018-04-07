

#include "difparser.h"

int main(){

	Node* res;
	
	printf("main 2.5\n");
	char* str = (char*) calloc (100,sizeof(char));
	printf("Enter your example \n you can use (+ - / * ^) \n  Please do not use spaces(it's illegal) \n");
	scanf("%s",str);
	Node* root = GetG(str);
	
	res = Differentiate(root);

	printf("main 3\n");
	Simplification(res);
	printf("\n");
	DotDump(root);
	AltSaveInfoInFile(stdout,res);
	printf("\n");
	
	//TexDump(res);
	
	DeleteTree(root);
	DeleteTree(res);
	
	return 0;
}