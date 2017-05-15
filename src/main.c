#include"driver.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int err;

	err = shellMenu();
	
	if(err != 0)
	{
		return 1;
	}

	return 0;
}
