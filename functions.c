#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

void get( FILE* fp, char** str )
{
	char* tmp = malloc(10*sizeof(char));
	int c=0;
	while( tmp[c]=getc(fp) )	
	{
		if( tmp[c] < 48 || tmp[c] > 57 )
		{
			tmp[c] = '\0';
			break;
		}
		c++;
	}
	*str = malloc(c);
	strncpy( *str, tmp, c );
	free(tmp);
}

int get_brightness(char* f)
{
	FILE* b = fopen(f, "r");	
	char* brightness;

	if( b == NULL )
	{
		fprintf(stdout, "Error opening file");
		exit(1);
	}

	get( b, &brightness );
	int ret = atoi(brightness);
	fclose(b);
	free(b);
	free(brightness);
	return ret;
}

void set_path(char* dir, char* file, char** path)
{
	char* static_path = "/sys/class/backlight/";
	size_t path_size = strlen(static_path)+strlen(dir)+strlen(file) + 1;
	*path = malloc(path_size);
	snprintf( *path, path_size, "%s%s%s", static_path, dir, file );
}
