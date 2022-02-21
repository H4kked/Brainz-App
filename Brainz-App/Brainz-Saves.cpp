#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "Brainz-Saves.h"
#include "Brainz-App.h"

void fMainSaves()
{
	BRAIN_LIST* brain_list;
	brain_list = (BRAIN_LIST*)malloc(sizeof(*brain_list));
	brain_list->size = 0;
	fGetBrains(brain_list);
}


void fGetBrains(BRAIN_LIST* brain_list)
{
	BRAIN* brain;
	brain = (BRAIN*)malloc(sizeof(*brain));
	MEMBER* member;
	member = (MEMBER*)malloc(sizeof(*member));
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
		name = (char*)malloc(20);
		description = (char*)malloc(180);
		fSplitBrain(&id, name, description, &is_available, &note, str);
		
		if (brain_list->size == 0)
		{
			brain_list->first = brain;
			brain_list->last = brain;
			brain->next = NULL;
			brain->previous = NULL;
		}
		else {
			brain_list->last->next = brain;
			brain->next = NULL;
			brain->previous = brain_list->last;
			brain_list->last = brain;
		}
		
		brain->id = id;
		brain->name = name;
		brain->desc = description;
		brain->is_available = is_available;
		brain->note = note;
		brain->list = NULL;
		brain_list->last = brain;
		brain_list->size += 1;
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

	char* temp;
	temp = (char*)malloc(100);

	// Recover the id of the brain
	for (int i = 0; i < pos1; i++)
	{
		temp[i] = str[i];
	}
	temp[pos1-1] = '\0';
	*id = atoi(temp);

	// Recover the name of the brain
	for (int i = pos1; i < pos2; i++)
	{
		name[i - pos1] = str[i];
	}
	name[pos2 - pos1 - 1] = '\0';

	// Recover the description of the brain
	for (int i = pos2; i < pos3; i++)
	{
		description[i - pos2] = str[i];
	}
	description[pos3 - pos2 - 1] = '\0';

	// Recover the availability of the brain
	for (int i = pos3; i < pos4; i++)
	{
		temp[i - pos3] = str[i];
	}
	temp[pos4 - pos3 - 1] = '\0';
	*is_available = atoi(temp);

	// Recover the note of the brain
	for (int i = pos4; i < length; i++)
	{
		temp[i - pos4] = str[i];
	}
	temp[length - pos4 - 1]='\0';
	*note = atoi(temp);
}


void fDisplayBrainList(BRAIN_LIST* brain_list)
{
	printf("Nope");
}
