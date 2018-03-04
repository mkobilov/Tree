#include "akinator.h"



int main (){
	
	pNode root = (pNode) calloc(1,sizeof(Node)) ;
	char* line = (char*) calloc (_MAX_RW_LINE_LENGTH_,sizeof(char));
	FILE* file_r = fopen("./akinatortestlogfile.txt","r");
	if(file_r){
		int length = GetLine(file_r,line);
		line =(char*) realloc((void*)line,length);
		root = AltReadInfoFromFile(line,NULL);
		free(line);	
	}
	else{
		CreateBasicTree(root);
	}
	Guesing(root);
	FILE* file = fopen("./akinatortestlogfile.txt","w+");

	AltSaveInfoInFile(file,root);
	fclose(file);
	return 0;
}

