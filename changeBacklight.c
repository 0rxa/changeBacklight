#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "functions.h" 

int main(int argc, char* argv[])
{

	int opt;
	int inc_perc = 5, max_brightness, min_brightness = 0, brightness, div = 1, inc = 1;
	bool mode = false, invalid = false; // default to hard
	char* operation = "-";
	char* path;
	char* soft_dir = "intel_backlight/";
	char* hard_dir = "acpi_video0/";
	char* max_brightness_file = "max_brightness";
	char* brightness_file = "brightness";

	while( ( opt = getopt( argc, argv, "m:o:p:h") ) != -1 )
	{
		switch(opt)
		{
			case 'm':
				if( !strcmp(optarg, "s") )
				{
					mode = true;
				}
				else if( strcmp(optarg, "h" ) )
				{
					invalid = true;
				}
				break;
			case 'o':
				operation = optarg;
				break;
			case 'p':
				inc_perc=atoi(optarg);
				break;
			case 'h':
				invalid = true;
				break;
			case ':':
				printf("Option requires a value\n");
				break;

		}
	}

	if( invalid )
	{
		printf("This program must be executed as root\n");
		printf("Usage: %s [moph]\n", argv[0]);
		printf("\t-m: set mode hard(h) or soft(s), will default to hard mode");
		printf("\t-o: set operation\n\t ++, --, max, min, - (shows current brightness)\n");
		printf("\t-p: set percentage, will be ignored on hard mode\n");
		printf("\t-h: display this help message\n");
		return 0;
	}

	setuid(0);
	if( strcmp(operation, "-") && getuid() != 0 )
	{
		printf("This program must be executed as root\n");
		return 1;
	}

	if( !mode )
	{
		set_path( hard_dir, max_brightness_file, &path);
		max_brightness = get_brightness(path);
		free(path);

		set_path( hard_dir, brightness_file, &path);
		brightness = get_brightness(path);
	}
	else
	{
		set_path( soft_dir, max_brightness_file, &path);
		max_brightness = get_brightness(path);
		free(path);

		set_path( soft_dir, brightness_file, &path);
		brightness = get_brightness(path);
		min_brightness = max_brightness/100;
		inc = (max_brightness/100)*inc_perc;
	}

	FILE* f = fopen(path, "r+");
	if( !strcmp( operation, "max" ) )
	{
		brightness = max_brightness;
	}
	else if( !strcmp( operation, "min" ) )
	{
		brightness = min_brightness;
	}
	else if( !strcmp( operation, "++" ) )
	{
		brightness += inc;
	}
	else if( !strcmp( operation, "--" ) )
	{
		brightness -= inc;
	}
	else if( operation[0] == '-' )
	{
		printf("Current Brightness: %d\n", brightness);
		return 0;
	}

	fprintf(f, "%d", brightness);
	fclose(f);
	return 0;
}
