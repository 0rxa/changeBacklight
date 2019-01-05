#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void get( FILE* fp, char* str )
{
	int c=0;
	while( str[c]=getc(fp) )	
	{
		if( str[c] < 48 || str[c] > 57 )
		{
			str[c] = '\0';
			break;
		}
		c++;
	}
	
}

int main(int argc, char* argv[])
{
	setuid(0);
	if(argc != 2)
	{
		printf("%s max\n", argv[0]);
		printf("%s min\n", argv[0]);
		printf("%s ++\n", argv[0]);
		printf("%s --\n", argv[0]);
		printf("%s s\n", argv[0]);
		exit(1);
	}

	if(getuid() != 0)
	{
		printf("This program must be executed as root\n");
		exit(1);
	}

	FILE* brightness = fopen("/sys/class/backlight/acpi_video0/brightness", "r+");
	//string operand, arg;
	char* operand = malloc( 3*sizeof(char) );
	char* arg = malloc( strlen(argv[1])*sizeof(char) );
	int val, max=11;
	strcpy(arg, argv[1]);

	//Get actual Brightness
	if(brightness != NULL)
	{
		get( brightness, operand );
	}
	val=atoi(operand);

	//Make the changes
	if(strcmp(arg, "max") == 0)
	{
		val = max;
	}

	else if(strcmp(arg, "min")==0)
	{
		val = 0;
	}

	else if(strcmp(arg, "++")==0)
	{
		val++;
	}

	else if(strcmp(arg, "--")==0)
	{
		val--;
	}
	else if(strcmp(arg, "s")==0)
	{
	}
	else
	{
		fprintf(stderr, "Invalid argument\n");
		exit(1);
	}

	fprintf( brightness, "%d", val );
	fprintf( stdout, "%d\n", val );

	return 0;
}
