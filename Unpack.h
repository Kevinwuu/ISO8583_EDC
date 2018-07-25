


char int2ascii(int tmp){
	if (9>=tmp && tmp>=0)
	{
		return tmp + '0';
	}
	else if (tmp>='A' && tmp<='F')
	{
		return tmp + 'A' - 10;
	}
	else{
		printf("ERROR!\n");
	}
}

int test(){
	printf("Hello\n");
}
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




void unpack(unsigned char msg[1024]){
	int size = strlen(msg);
	unsigned char *copied = malloc( 2*size*sizeof(unsigned char));

	// while(sscanf(msg,"%4s",ch)) {
	printf("size = %d\n",size);
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		printf("%d \n", msg[i]);
		if (msg[i]>=16)
		{
			int H_bit = msg[i]/16;
			int L_bit = msg[i]%16;
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
			L = int2ascii(msg[i]);
			copied[count] = L;
		}
		count++;

	}
	//開始切割，一個char等
	char buf[500] = {'\0'};
	char LEN[4];
	char TPDU[10];
	char MTI[4];
	char Bitmap[16];
	char element[500]={'\0'};

	int disp = 0;

	printf("\n-------------------------------------------------------\n");
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

	// char f_state[128] = {'\0'};

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

	printf("FIELD = ");
	for (int i = 0; i < sizeof(f_state); i++)
	{
		if (f_state[i] == '1')
		{
			printf("%d ", i);
		}
	}

	printf("\n-------------------------------------------------------\n");


}
