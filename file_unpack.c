#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char int2ascii(int tmp){
	if (9>=tmp && tmp>=0)
	{
		return tmp + '0';
	}
	else{
		return tmp - 10 + 'A';
	}
}

int main(){

	//Open file
	FILE *fptr;
	// fptr = fopen("msg.txt", "r");
	fptr = fopen("IsoIn.txt", "rb");
	if (fptr == NULL)
	{
		printf("open_file_error");
		exit(1);
	}

	//File size
	int file_size;
    fseek(fptr, 0, SEEK_END);
	file_size = ftell(fptr);
	fseek(fptr,0,SEEK_SET);
	printf("File size = %d BYTE\n",file_size );

	// Read file
	// unsigned char copied[480] = {'\0'};
	unsigned char *copied = malloc( 2*file_size*sizeof(unsigned char));

	int count = 0;
	int n = 0;
	int s = 0;
	unsigned char ch={'\0'};

	while(fscanf(fptr,"%c",&ch)==1) {

		// (儲存位置,讀取單位大小,讀取單位數量,等待被讀取位置)

        if (ch=='\n')
        {
        	n++;
        }
        if (ch=='\0')
        {
        	s++;
        }

		printf("%2X ", ch);

        //1 ascii to 2 decimal
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


	int len=0;
	printf("\n-------------------------------------------------------\n");

	printf("count = %d number\n",count);
	printf("change line = %d\n",n);
	printf("space = %d\n",s);
	printf("\n-------------------------------------------------------\n");



	//開始切割，一個char等
	char buf[500] = {'\0'};
	char LEN[4];
	char TPDU[10];
	char MTI[4];
	char Bitmap[16];
	char element[500]={'\0'};

	int disp = 0;

	printf("[Data]\n\n");
	printf("%s\n", copied);
	printf("\n-------------------------------------------------------\n");
	printf("[Unpack]\n\n");

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
	disp+=16;

	printf("Bitmap = %s\n",Bitmap);

	// memset(buf, '\0', sizeof(buf));

	char f_state[128] = {'\0'};


	void div_Field(int n, int index){
		int k = 8;
		int disp = 0;
		while(n){
			if(n>=k){
				n = n-k;
				// printf("%d\n",index+count);
				f_state[index+disp] = '1';
			}
			k = k/2;
			disp++;
		}
	}

	//切bitmap
	for (int i = 0; i < 16; i++)
	{
		//field從1開始
		if (Bitmap[i]>='0' && Bitmap[i]<='9'){
			div_Field(Bitmap[i]-'0', 4*i+1);
		}
		else if(Bitmap[i]>='A' && Bitmap[i]<='F'){
			div_Field(Bitmap[i]-'A'+10, 4*i+1);
		}
		else{
			printf("ERROR\n");
		}
	}


	// printf("FIELD = %s\n",FIELD);
	printf("FIELD = ");
	for (int i = 0; i < sizeof(f_state); i++)
	{
		if (f_state[i] == '1')
		{
			printf("%d ", i);
		}
	}
	printf("\n-------------------------------------------------------\n");

	printf("\ndisp = %d\n", disp);
	printf("el_size = %d\n",2*file_size - disp);

	strncpy(buf,copied+disp,2*file_size - disp);
	strncpy(element,buf,sizeof(buf));
	printf("Element = %s\n",element);
	memset(buf, '\0', sizeof(buf));


    fclose(fptr);

}
