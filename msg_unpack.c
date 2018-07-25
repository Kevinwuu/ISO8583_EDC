#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Unpack.h"

int main(int argc, char const *argv[])
{
	unsigned char buf[1024] = {'\0'};
	printf("Enter:\n>>");
	gets(buf);
	unpack(buf);
	// unpack("12345678");
	return 0;
}
