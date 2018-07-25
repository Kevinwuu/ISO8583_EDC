#include <stdio.h>
#include <String.h>




int ascii2int(char ch_tmp)
{
	int dec_val = 0;
	if ((ch_tmp >= '0') && (ch_tmp <= '9'))
	{
		dec_val = ch_tmp - '0';
	}
	else if ((ch_tmp >= 'A') && (ch_tmp <= 'F'))
	{
		dec_val = ch_tmp - 'A' + 10;
	}
	else if((ch_tmp >= 'a') && (ch_tmp <= 'f'))
	{
		dec_val = ch_tmp - 'a' + 10;
	}
	else
	{
		printf("ERROR!\n");
	}
	// printf("%d ",dec_val);
	return dec_val;

}

int ParseInput(char tmp[500]){
	int length = strlen(tmp)/2;
	char hex_ch[250] = {};
	int H_bit = 0;
	int L_bit = 0;

	for (int i = 0; i < strlen(tmp); i=i+2)
	{
		H_bit = ascii2int(tmp[i]);
		L_bit = ascii2int(tmp[i+1]);
		printf("%d ",16*H_bit + L_bit );
		hex_ch[i/2] = 16*H_bit + L_bit;
		// printf("%d\n",hex_ch);
	}
}

int main(){
	char szBuf[500] = {'\0'};
	printf("Enter:\n>>");
	gets(szBuf);

	// printf("%s\n",szBuf );
	ParseInput(szBuf);

}
