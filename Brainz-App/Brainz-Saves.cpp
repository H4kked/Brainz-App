#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "Brainz-Saves.h"

void fMainSaves()
{
	printf("main");
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
	brain_file = (FILE*)malloc(sizeof(brain_file));
	fOpenFiles((char*)"brain.txt", brain_file);
	char  str[222];


	while (fgets(str, 222, brain_file) != NULL)
	{
		printf(str);
		int id = 0;
		char* name;
		char* description;
		int is_available = 0;
		int note = 0;
		name = (char*)malloc(sizeof(20));
		description = (char*)malloc(sizeof(180));
	}
}
