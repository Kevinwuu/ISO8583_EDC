#include <stdio.h>
#include <String.h>




int ascii2int(char ch)
{
	int dec_val = 0;
	if ((ch >= '0') && (ch <= '9'))
	{
		dec_val = ch - '0';
	}
	else if ((ch >= 'A') && (ch <= 'F'))
	{
		dec_val = ch - 'A' + 10;
	}
	else if((ch >= 'a') && (ch <= 'f'))
	{
		dec_val = ch - 'a' + 10;
	}
	else
	{
		printf("ERROR!\n");
	}
	// printf("%d ",dec_val);
	return dec_val;

}


char int2ascii(int ch){
	if (9>=ch && ch>=0)
	{
		return ch + '0';
	}
	else{
		return ch - 10 + 'A';
	}
}

int parseInput(unsigned char tmp[500]){
	int length = strlen(tmp)/2;
	char hex_ch[300] = {};
	int H_bit = 0;
	int L_bit = 0;

	for (int i = 0; i < strlen(tmp); i=i+2)
	{
		H_bit = ascii2int(tmp[i]);
		L_bit = ascii2int(tmp[i+1]);
		// printf("%d ",16*H_bit + L_bit );
		hex_ch[i/2] = 16*H_bit + L_bit;
	}
	strcpy(tmp,hex_ch);
}

int parseOutput(unsigned char tmp[250]){
	unsigned char output[500] = {'\0'};
	int H_bit = 0;
	int L_bit = 0;
	int count = 0;
	for (int i = 0; i < strlen(tmp); i++)
	{
		if (tmp[i]>=16)
		{
			int H_bit = tmp[i]/16;
			int L_bit = tmp[i]%16;
			char H,L;
			H = int2ascii(H_bit);
			L = int2ascii(L_bit);
			output[count] = H;
			count++;
			output[count] = L;
		}
		else if(tmp[i]>=0 && tmp[i]<=16){
			output[count] = '0';
			count++;
			char L;
			L = int2ascii(tmp[i]);
			output[count] = L;
		}
		else{
			printf("-1\n");
			printf("%d\n",tmp[i]);
		}
		// printf("%d ",16*H_bit + L_bit );
		// hex_ch[i/2] = 16*H_bit + L_bit;
		count++;
	}
	printf("%s\n", output);
}

