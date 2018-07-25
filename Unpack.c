


char int2ascii(int tmp){
	if (9>=tmp && tmp>=0)
	{
		return tmp + '0';
	}
	else{
		return tmp - 10 + 'A';
	}
}

int test(){
	printf("Hello\n");
}

char unpack(FILE fptr){

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
}
