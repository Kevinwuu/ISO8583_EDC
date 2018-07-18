#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(){
	// 讀檔
	FILE *fptr;
	int size;
	// fptr = fopen("msg.txt", "r");
	fptr = fopen("IsoIn.txt", "rb");

	if ((fptr = fopen("IsoIn.txt", "rb")) == NULL)
	{
		printf("open_file_error");
		exit(1);
	}

    fseek(fptr, 0, SEEK_END);
	size = ftell(fptr);
	printf("File size = %d BYTE\n",size );

	// char ecb_info[474] = {'\0'};
	char int2ascii(int tmp){
		if (9>=tmp && tmp>=0)
		{
			return tmp + '0';
		}
		else{
			return tmp - 10 + 'A';
		}
	}

	// 開始讀檔,讀到檔尾結束
	unsigned char copied[480] = {'\0'};
	int count = 0;
	int n = 0;
	int s = 0;
	fseek(fptr,0,SEEK_SET);
	while(!feof(fptr)) {
		unsigned char ch={'\0'};

		// (儲存位置,讀取單位大小,讀取單位數量,等待被讀取位置)
        fread(&ch, sizeof(char), 1, fptr);
        if (ch=='\n')
        {
        	n++;
        }
        if (ch=='\0')
        {
        	s++;
        }

		printf("%d ", ch);

		if (ch>=16)
		{
			int H_bit = ch/16;
			int L_bit = ch%16;
			char H,L;
			H = int2ascii(H_bit);
			L = int2ascii(L_bit);
			copied[count] = H;
			count++;
			copied[count] = L;
		}else{
			copied[count] = '0';
			count++;
			char L;
			L = int2ascii(ch);
			copied[count] = L;
		}
		count++;
	}


	printf("\n");


	printf("count = %d number\n",count);
	printf("change line = %d\n",n);
	printf("space = %d\n\n",s);

	printf("%s\n", copied);


	//開始切割，一個char等
	char buf[80] = {'\0'};
	char LEN[4];
	char TPDU[10];
	char MTI[4];
	char Bitmap[16];
	int disp = 0;

	strncpy(buf,copied,4);
	strncpy(LEN,buf,sizeof(buf));
	memset(buf, '\0', sizeof(buf));
	disp+=4;

	printf("LEN = %s\n",LEN);

	strncpy(buf,copied+disp,10);
	strncpy(TPDU,buf,sizeof(buf));
	memset(buf, '\0', sizeof(buf));
	disp+=10;

	printf("TPDU = %s\n",TPDU);

	strncpy(buf,copied+disp,4);
	strncpy(MTI,buf,sizeof(buf));
	memset(buf, '\0', sizeof(buf));
	disp+=4;

	printf("MTI = %s\n",MTI);

	strncpy(buf,copied+disp,16);
	strncpy(Bitmap,buf,sizeof(buf));
	memset(buf, '\0', sizeof(buf));

	printf("Bitmap = %s\n",Bitmap);


	char FIELD[128] = {'\0'};

	void div_Field(int n, int index){
		int k = 8;
		int count = 0;
		while(n){
			if(n>=k){
				n = n-k;
				// printf("%d\n",index+count);
				FIELD[index+count] = '1';
			}
			k = k/2;
			count++;
		}
	}

	//切bitmap
	for (int i = 0; i < 16; i++)
	{
		//0~9
		if (Bitmap[i]>=48 && Bitmap[i]<=57){

			//field從1開始
			div_Field(Bitmap[i]-'0', 4*i+1);
		}
		//A~F
		else if(Bitmap[i]>=65 && Bitmap[i]<=70){
			div_Field(Bitmap[i]-'A'+10, 4*i+1);
		}
		else{
			printf("ERROR\n");
		}
	}
	// printf("FIELD = %s\n",FIELD);
	printf("FIELD = ");
	for (int i = 0; i < sizeof(FIELD); i++)
	{
		if (FIELD[i] == '1')
		{
			printf("%d ", i);
		}
	}
	// itoa(num,str,2);

	memset(buf, '\0', sizeof(buf));
	disp+=16;


    fclose(fptr);

}
