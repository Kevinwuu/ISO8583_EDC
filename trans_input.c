#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(){
	int size;

	// 讀檔
	FILE *fptr;
	FILE *sptr;
	// fptr = fopen("msg.txt", "r");
	fptr = fopen("IsoIn.txt", "rb");
	sptr = fopen("output.txt", "wb");

	if ((fptr = fopen("msg.txt", "r")) == NULL)
	{
		printf("open_file_error");
		exit(1);
	}
	if ((sptr = fopen("output.txt", "wb")) == NULL)
	{
		printf("open_file_error");
		exit(1);
	}


	int ascii_to_hex(char ch_tmp)
	{
		// char ch_tmp;
		int hex_val = -1;
		// ch_tmp = tolower(ch);
		if ((ch_tmp >= '0') && (ch_tmp <= '9'))
		{
			// 輸入的ascii碼是'0' ~ '9'
			hex_val = ch_tmp - '0'-30;
			// hex_val = ch_tmp -18;
		}
		else if ((ch_tmp >= 'A') && (ch_tmp <= 'F'))
		{
			// 輸入的ascii碼是'A' ~ 'F'
			hex_val = ch_tmp - 'A' -55;
			// hex_val = ch_tmp - 24;
		}

		return hex_val;

	}


	char buf;
	int count = 0;
	while(!feof(fptr)) {
		// (儲存位置,讀取單位大小,讀取單位數量,等待被讀取位置)
		int hex2dec = 0;

		//一次讀兩個字元, 02 34 60 06
        fread(&buf, sizeof(char),1 , fptr);
		// buf = ascii_to_hex(buf);
		printf("%c", buf);

		// fwrite(&buf, sizeof(int), 1, sptr);


		count++;
	}

    fclose(fptr);
    fclose(sptr);




}
