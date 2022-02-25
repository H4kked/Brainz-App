#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <Windows.h>
#include "Brainz-Brains.h"
#include "Brainz-Menu.h"
#include "Brainz-Members.h"


void fBrainStart(BRAIN_LIST* brain_list)
{
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
}

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
	//printf("\n\n");
	//fAddBrain(brain_list);
	//fDisplayBrainList(brain_list);
	//fDelBrain(brain_list);
	//fDisplayBrainList(brain_list);

	char* ch_name;
	ch_name = (char*)malloc(15);
	printf("Enter the name of the brain you want to borrow : ");
	fgets(ch_name, 15, stdin);
	ch_name[strlen(ch_name) - 1] = '\0';

	fSetAvailability(brain_list, ch_name);
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


	printf("+------+-----------------+------------------------------------------------------------------------------------------------------+---------------+--------+\n");
	printf("|  id  |      name       |                                              Description                                             |  AVAILABILITY | NOTE/5 |\n");
	printf("+------+-----------------+------------------------------------------------------------------------------------------------------+---------------+--------+\n");
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
		printf("| %04d | %15s | %100s | %s | %.2f/5 |\n", brain->id, brain->name, brain->desc, available, brain->note);
		
		brain = brain->next;
	}
	printf("+------+-----------------+------------------------------------------------------------------------------------------------------+---------------+--------+\n");
	printf("  number of brains : %04d\n", brain_list->size-1);

	system("PAUSE");
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

void fAddBrain(BRAIN_LIST* brain_list)
{
	int id = brain_list->last->id + 1;
	int is_available = 1;
	char* name;
	name = (char*)malloc(15);
	char* description;
	description = (char*)malloc(100);

	Sleep(50);
	getchar();

	printf("Enter the name of the brain (15 characters max) : ");
	fgets(name, 15, stdin);
	name[strlen(name) - 1] = '\0';
	printf("Enter the description of the brain (100 characters max) : ");
	fgets(description, 100, stdin);
	description[strlen(description) - 1] = '\0';

	fAddEnd(brain_list, id, name, description, is_available, NULL);
	fWriteBrain(brain_list);
}

void fWriteBrain(BRAIN_LIST* brain_list)
{
	FILE* brain_file;
	brain_file = (FILE*)malloc(sizeof(*brain_file));
	char path[] = "brain.txt";
	fopen_s(&brain_file, path, "w+");
	
	BRAIN* my_brain;
	my_brain = (BRAIN*)malloc(sizeof(*my_brain));
	my_brain = brain_list->first->next;

	// We want the brain to be written as : id/name/description/is_avilable/note
	while (my_brain != NULL)
	{
		fprintf(brain_file, "%04d/%s/%s/%d/%.2f\n", my_brain->id, my_brain->name, my_brain->desc, my_brain->is_available, my_brain->note);
		my_brain = my_brain->next;
	}
	fclose(brain_file);
	fBrainStart(brain_list);
}

void fDelBrain(BRAIN_LIST* brain_list)
{
	BRAIN* del_brain;
	del_brain = (BRAIN*)malloc(sizeof(*del_brain));
	del_brain = brain_list->first;

	char* del_name;
	del_name = (char*)malloc(15);
	printf("Enter the name of the brain you want to delete : ");
	fgets(del_name, 15, stdin);
	del_name[strlen(del_name) - 1] = '\0';

	while (strcmp(del_brain->name, del_name) != 0 && del_brain != NULL)
	{
		del_brain = del_brain->next;
		if (del_brain == NULL)
		{
			break;
		}
	}

	if (del_brain == NULL)
	{
		printf("There is no brain with this name...\n\n");
	}
	else
	{
		printf("\n");

		if (strcmp(del_brain->name, brain_list->last->name) == 0)
		{
			brain_list->last = del_brain->previous;
			del_brain->previous->next = NULL;
		}
		else
		{
			del_brain->previous->next = del_brain->next;
			del_brain->next->previous = del_brain->previous;
			del_brain = del_brain->next;
			while (del_brain != NULL)
			{
				del_brain->id -= 1;
				del_brain = del_brain->next;
			}
		}
		brain_list->size -= 1;
		fWriteBrain(brain_list);
	}
}

void fSetAvailability(BRAIN_LIST* brain_list, char* ch_name)
{
	BRAIN* ch_brain;
	ch_brain = (BRAIN*)malloc(sizeof(*ch_brain));
	ch_brain = brain_list->first->next->next;

	while (strcmp(ch_brain->name, ch_name) != 0)
	{
		ch_brain = ch_brain->next;
		if (ch_brain == NULL)
		{
			break;
		}
	}

	if (ch_brain == NULL)
	{
		printf("There is no brain with this name\n");
	}
	else
	{
		if (ch_brain->is_available == 0)
		{
			ch_brain->is_available = 1;
		}
		else
		{
			ch_brain->is_available = 0;
		}
		fWriteBrain(brain_list);
	}


}

void fBorrowBrain(MEMBER_LIST* member_list, BRAIN_LIST* brain_list, MEMBER* current_member)
{
	BRAIN* borrowed_brain;
	borrowed_brain = (BRAIN*)malloc(sizeof(*borrowed_brain));
	borrowed_brain = brain_list->first;

	// DISPLAY ALL THE BRAINS
	fDisplayBrainList(brain_list);

	// ASK WHAT BRAIN WILL BE BORROWED
	char* name;
	name = (char*)malloc(sizeof(*name));
	Sleep(1);
	getchar();
	printf("							Enter the name of the brain you want to borrow : ");
	fgets(name, 15, stdin);
	name[strlen(name) - 1] = '\0';

	// SEARCH THE BRAIN THROUGH THE LIST
	while (strcmp(borrowed_brain->name, name) != 0 && borrowed_brain != NULL)
	{
		printf("%s\n", name);
		printf("%s\n", borrowed_brain->name);
		borrowed_brain = borrowed_brain->next;
	}

	// THE BRAIN'S NAME HAS NOT BEEN RECOGNIZED IN THE LIST
	if (borrowed_brain == NULL)
	{
		printf("						There is no brain with this name.\n");
		fBorrowBrain(member_list, brain_list, current_member);
	}
	else
	{
		if (borrowed_brain->is_available == 0)
		{
			// THE BRAIN IS NOT AVAILABLE, RE-DO THE FUNCTION
			printf("		This brain has already been borrowed. Please select another brain.");
			fBorrowBrain(member_list, brain_list, current_member);
		}
		else
		{
			// INDICATES THE BRAIN AS NON AVAILABLE AND INDICATES IT ON THE USERS PROFILE
			borrowed_brain->is_available = 0;
			current_member->brain_id = borrowed_brain->id;

			// RE-BUILD THE TXT FILES AND LISTS
			fWriteBrain(brain_list);
			fWriteMember(member_list);

			// RETURNS ON THE USER'S SCREEN
			printf("				Brain borrowed. Thanks for using our app ! \n");
			system("PAUSE");
			fUserScreen(current_member, brain_list, member_list);
		}
	}
}

void fReturnBrain(MEMBER_LIST* member_list, BRAIN_LIST* brain_list, MEMBER* current_member)
{
	BRAIN* returned_brain;
	returned_brain = (BRAIN*)malloc(sizeof(returned_brain));
	returned_brain = brain_list->first;
	
	while (returned_brain->id != member_list->logged->brain_id && returned_brain != NULL)
	{
		returned_brain = returned_brain->next;
		if (returned_brain == NULL)
		{
			break;
		}
	}

	returned_brain->is_available = 1;
	member_list->logged->brain_id = 0;
	fWriteBrain(brain_list);
	fWriteMember(member_list);
	printf("									Brain returned. Thanks for using our app!");
	system("PAUSE");
}

void fBrainManagement(MEMBER_LIST* member_list, BRAIN_LIST* brain_list)
{
	clear_screen(' ');
	Sleep(50);
	fPrintLogo();

	printf("										1 - ADD A BRAIN\n");
	printf("										2 - DELETE A BRAIN\n");
	printf("										3 - SEE BRAIN LIST\n");
	printf("\n										9 - EXIT\n");
	printf("\n										Entry : ");

	int choice = 0;
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
		clear_screen(' ');
		fPrintLogo();
		fAddBrain(brain_list);
		break;
	case 2:
		clear_screen(' ');
		fPrintLogo();
		fDelBrain(brain_list);
		break;
	case 3:
		clear_screen(' ');
		fPrintLogo();
		fDisplayBrainList(brain_list);
		break;
	case 9:
		fAdminScreen(member_list->logged, brain_list, member_list);
		break;
	}
	fAdminScreen(member_list->logged, brain_list, member_list);
}
