#include "Brainz-Saves.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

void fMainSaves()
{
	printf("main");
}

void fOpenFile(char* file_name, FILE* file)
{
	fopen_s(&file, file_name, "r+");

	if (file == NULL)
	{
		printf("[ERROR] file does not exist\n");
		exit(0);
	}
}
