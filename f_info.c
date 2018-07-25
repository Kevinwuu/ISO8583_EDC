#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>




typedef struct FIELD
{
	char type[10];
	char len[10];
	char content[100];
}FIELD;

typedef struct MTI
{
	char code[4];
	char mean[50];
	char usage[100];
}MTI;

FIELD f[]={
	{'\0','\0','\0'}
};

MTI m[]={
	{'\0','\0','\0'}
};

// struct msgData{
// 	FIELD *f;
// 	MTI *m;
// }Data;

// void split(FILE* fp,FIELD set[]){
// 	char buf[100]={'\0'};
// 	int line = 1;
// 	while((fgets(buf,sizeof(buf),fp)) != NULL){
// 		printf("%s", buf);
// 		sscanf(buf,"%*d %s %s %*s",set[line].type,set[line].len);
// 		memset(buf,'\0',sizeof(buf));
// 		line+=1;
// 	}
// }

int main(int argc, char const *argv[])
{
	FILE *fptr,*mptr;
	fptr = fopen("FIELD_info.txt","r");
	mptr = fopen("MTI_info.txt","r");

	if ((fptr ==NULL) ||(mptr == NULL))
	{
		printf("open_file_error");
		// exit(1);
	}

	unsigned char ch = {'\0'};
	char buf[150]={'\0'};
	int line = 1;
	printf("\n----------------------------------------------------------------\n");

	while((fgets(buf,sizeof(buf),fptr)) != NULL){
		printf("%s", buf);
		sscanf(buf,"%*d %s %s %*s",f[line].type,f[line].len);


		// fgets(f[line].content,300,buf);
		memset(buf,'\0',sizeof(buf));
		line+=1;
	}
	printf("\n----------------------------------------------------------------\n");

	printf("\n%d",line);
	line = 0;
	printf("\n");
	printf("f[120] type = %s\n",f[120].type);
	printf("f[120] len = %s\n",f[120].len);
	printf("----------------------------------------------------------------\n");

	while((fgets(buf,sizeof(buf),mptr)) != NULL){
		// printf("line = %d\n", line);
		printf("%s", buf);
		// strncpy(m[line].code,buf,4);
		sscanf(buf,"%4s",m[line].code);

		printf("code = %s\n",m[line].code );
		// sscanf(buf+6,"%s%[*\t] ",m[line].mean);

		// printf("\nmean = %s\n\n",m[line].mean );

		memset(buf,'\0',sizeof(buf));
		line+=1;
	}
	printf("\n----------------------------------------------------------------\n");
	printf("m[1] code = %s\n",m[1].code);
	printf("m[1] mean = %s\n",m[1].mean);




	fclose(fptr);
	fclose(mptr);
	return 0;
}
