#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "Brainz-Brains.h"
#include "Brainz-App.h"

void fMainSaves()
{
	BRAIN_LIST* brain_list;
	brain_list = (BRAIN_LIST*)malloc(sizeof(*brain_list));
	BRAIN* first_brain;
	first_brain = (BRAIN*)malloc(sizeof(*brain_list));
	first_brain->desc = (char*)"The first brain ever";
	first_brain->id = -1;
	first_brain->is_available = 0;
	first_brain->list = NULL;
	first_brain->name = (char*)"First Brain";
	first_brain->next = NULL;
	first_brain->note = 0;
	first_brain->previous = NULL;

	brain_list->first = first_brain;
	brain_list->last = first_brain;
	brain_list->size = 0;
	fGetBrains(brain_list);
	fDisplayBrainList(brain_list);
}


void fGetBrains(BRAIN_LIST* brain_list)
{
	
	FILE* brain_file;
	brain_file = (FILE*)malloc(sizeof(FILE*));
	char path[] = "brain.txt";
	fopen_s(&brain_file, path, "r+");
	char*  str;
	str = (char*)malloc(200);

	while (fgets(str, 200, brain_file) != NULL)
	{
		//printf("%s\n", str);
		int id = 0;
		char* name;
		char* description;
		int is_available = 0;
		float note = 0;
		name = (char*)malloc(20);
		description = (char*)malloc(180);
		fSplitBrain(&id, name, description, &is_available, &note, str);
		fAddEnd(brain_list, id, name, description, is_available, note);

		//printf("last : %s\nbefore_last : \nsecond : %s\nfirst : \n\n", brain_list->last->name, brain_list->last->previous->name, brain_list->first->next->name, brain_list->first->name);
	}
	fclose(brain_file);
}

void fSplitBrain(int* id, char* name, char* description, int* is_available, float* note, char* str)
{
	int pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
	char splitter = '/';
	char* ret;
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
	*note = atof(temp);
}


void fDisplayBrainList(BRAIN_LIST* brain_list)
{
	/*
	* We want the information to be displayed as the example below :
	+------+-----------------+----------------------------------------------------+---------------+--------+
	|  id  |      name       |                   Description                      |  AVAILABILITY | NOTE/5 |
	+------+-----------------+----------------------------------------------------+---------------+--------+
	| 0003 |             GOD |			                  The Almighty GOD's Bain |	NOT_AVAILABLE |	  5/5  |
	|      |                 |													  |				  |		   |
	+------+-----------------+----------------------------------------------------+---------------+--------+
	*/


	BRAIN* brain;
	brain = (BRAIN*)malloc(sizeof(*brain));
	brain = brain_list->first;                      // Recover the first brain in an object of the type BRAIN
	brain = brain->next->next;						// The third brain on the list is the first that we want to display
	char* available;
	available = (char*)malloc(sizeof(*available));

	printf("+------+-----------------+----------------------------------------------------+---------------+--------+\n");
	printf("|  id  |      name       |                   Description                      |  AVAILABILITY | NOTE/5 |\n");
	printf("+------+-----------------+----------------------------------------------------+---------------+--------+\n");
	while (brain != NULL)
	{
		// We want to know if the brain is available or not
		if (brain->is_available == 1) // if brain->is_available == 0 then brain is NOT_AVAILABLE, else the brain is AVAILABLE
		{
			available = (char*)"    AVAILABLE\0";
		}
		else
		{
			available = (char*)"NOT_AVAILABLE\0";
		}
		printf("| %04d | %15s | %50s | %s | %.2f/5 |\n", brain->id, brain->name, brain->desc, available, brain->note);
		
		brain = brain->next;
	}
	printf("+------+-----------------+----------------------------------------------------+---------------+--------+\n");
	printf("  number of brains : %04d\n", brain_list->size-1);
}

void fAddEnd(BRAIN_LIST* brain_list, int id, char* name, char* description, int is_available, float note)
{
	BRAIN* my_brain;
	my_brain = (BRAIN*)malloc(sizeof(*my_brain));

	// Set the value of the different objects of the brain
	my_brain->id = id;
	my_brain->desc = description;
	my_brain->name = name;
	my_brain->is_available = is_available;
	my_brain->note = note;

	// Link the new brain in the list
	my_brain->previous = brain_list->last;
	my_brain->next = NULL;
	brain_list->last->next = my_brain;
	brain_list->last = my_brain;

	// Add one to the size of the list
	brain_list->size += 1;
}