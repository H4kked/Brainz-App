#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "Brainz-Saves.h"

void fMainSaves()
{
	fGetBrains();
}

void fOpenFiles(char file_name[], FILE* file)
{
	fopen_s(&file, file_name, "r+");

	if (file == NULL)
	{
		printf("[ERROR] file does not exist\n");
		exit(0);
	}
}

void fGetBrains()
{
	FILE* brain_file;
	brain_file = (FILE*)malloc(sizeof(FILE*));
	char path[] = "brain.txt";
	fopen_s(&brain_file, path, "r+");
	char*  str;
	str = (char*)malloc(70);

	while (fgets(str, 70, brain_file) != NULL)
	{
		printf("%s\n", str);
		int id = 0;
		char* name;
		char* description;
		int is_available = 0;
		int note = 0;
		name = (char*)malloc(sizeof(20));
		description = (char*)malloc(sizeof(180));
	}
	fclose(brain_file);
}
