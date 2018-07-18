#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct MTI
{
	char mean[10];
	char usage[100];
}MTI;

MTI m[]={
	{'\0','\0'}
};


void split(char tmp[150], int num){
	const char s[2] = "\t";
    char *token;
    token = strtok(tmp,s);
    for (int i = 1; i <= 3; i++)
    {
		printf("%s\n", token);
	    token = strtok(NULL,s);
    	// if (i==2)
    	// {
    	// 	strcpy(f[num].type,token);
    	// }
    	// if (i==3)
    	// {
    	// 	strcpy(f[num].content,token);
    	// }
    }

}

int main(int argc, char const *argv[])
{
	FILE *fptr;
	fptr = fopen("MTI_info.txt","r");
	if ((fptr = fopen("MTI_info.txt", "r")) == NULL)
	{
		printf("open_file_error");
		// exit(1);
	}

	unsigned char ch = {'\0'};


	char buf[150]={'\0'};
	int line = 1;
	while((fgets(buf,sizeof(buf),fptr)) != NULL){
		printf("%s", buf);
		split(buf,line);
		memset(buf,'\0',sizeof(buf));
		line+=1;
	}
	printf("\n");
	// printf("type = %s\n",f[5].type);
	// printf("content = %s\n",f[5].content);

	fclose(fptr);
	return 0;
}
