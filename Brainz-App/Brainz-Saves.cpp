#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "Brainz-Saves.h"
#include "Brainz-App.h"

void fMainSaves()
{
	fGetBrains();
}


void fGetBrains()
{
	BRAIN_LIST* brain_list;
	brain_list = (BRAIN_LIST*)malloc(sizeof(BRAIN_LIST*));
	BRAIN* brain;
	brain = (BRAIN*)malloc(sizeof(brain));
	MEMBER* member;
	member = (MEMBER*)malloc(sizeof(member));
	FILE* brain_file;
	brain_file = (FILE*)malloc(sizeof(FILE*));
	char path[] = "brain.txt";
	fopen_s(&brain_file, path, "r+");
	char*  str;
	str = (char*)malloc(200);

	while (fgets(str, 200, brain_file) != NULL)
	{
		printf("%s\n", str);
		int id = 0;
		char* name;
		char* description;
		int is_available = 0;
		int note = 0;
		name = (char*)malloc(sizeof(20));
		description = (char*)malloc(sizeof(180));
		fSplitBrain(&id, name, description, &is_available, &note, str);
		
		brain->id;
	}
	fclose(brain_file);
}

void fSplitBrain(int* id, char* name, char* description, int* is_available, int* note, char* str)
{
	int pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
	char splitter = '/';
	int length = strlen(str);

	for (int i = 0; i < length; i++)
	{
		if (str[i] == splitter)
		{
			if (pos1 == 0)
			{
				pos1 = i+1;
			}
			else if (pos2 == 0)
			{
				pos2 = i+1;
			}
			else if (pos3 == 0)
			{
				pos3 = i+1;
			}
			else if (pos4 == 0)
			{
				pos4 = i+1;
			}
		}
	}
	printf("%s\n", str);
	printf("pos1 = %d\npos2 = %d\npos3 = %d\npos4 = %d\n", pos1, pos2, pos3, pos4);

	char* temp;
	temp = (char*)malloc(100);

	// Recover the id of the brain
	for (int i = 0; i < pos1; i++)
	{
		temp[i] = str[i];
	}
	temp[pos1-1] = '\0';
	*id = atoi(temp);
	printf("%04d\n", *id);

	// Recover the name of the brain
	for (int i = pos1; i < pos2; i++)
	{
		name[i - pos1] = str[i];
	}
	name[pos2 - pos1 - 1] = '\0';
	printf("%s\n", name);

	// Recover the description of the brain
	for (int i = pos2; i < pos3; i++)
	{
		description[i - pos2] = str[i];
	}
	description[pos3 - pos2 - 1] = '\0';
	printf("%s\n", description);

	// Recover the availability of the brain
	for (int i = pos3; i < pos4; i++)
	{
		temp[i - pos3] = str[i];
	}
	temp[pos4 - pos3 - 1] = '\0';
	*is_available = atoi(temp);
	printf("%d\n", *is_available);

	// Recover the note of the brain
	for (int i = pos4; i < length; i++)
	{
		temp[i - pos4] = str[i];
	}
	temp[length - pos4 - 1]='\0';
	*note = atoi(temp);
	printf("%d\n", *note);


}
