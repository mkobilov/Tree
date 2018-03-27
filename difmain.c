#include "diff.h"

int main(){
	FILE* file_d = fopen("test.txt","w");
	
	Node* root = CreateExample();
	Node* res;

	printf("main 1\n");
	res = Differentiate(root);
	printf("main 2\n");
	AltSaveInfoInFile(stdout,root);
		printf("\n");
	AltSaveInfoInFile(stdout,res);
	printf("\n");
	
	
	
	printf("main 3\n");
	Simplification(res);
	printf("\n");
	//DotDump(res);
	AltSaveInfoInFile(stdout,res);
	printf("\n");
	
	TexDump(res);
	
	DeleteTree(root);
	DeleteTree(res);
	fclose(file_d);
	
	return 0;
}