#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include "Brainz-Brains.h"
#include "Brainz-Menu.h"
#include "Brainz-Members.h"
#include "Brainz-Comment.h"

void fCommentStart(MASTER_COMMENT* master_list)
{
	COMMENT_LIST* comment_list;
	COMMENT* comment;
	comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));
	comment = (COMMENT*)malloc(sizeof(*comment));

	char* date;
	date = (char*)malloc(20);
	fGetDate(date);

	// Initialize the first comment
	comment->member_name = (char*)"main_seh";
	comment->comment = (char*)"The first comment of the first list";
	comment->note = 0;
	comment->date = date;
	comment->brain_id = 0000;
	comment->next = NULL;
	comment->previous = NULL;

	// Initialize the first list
	comment_list->brain_id = 0000;
	comment_list->first = comment;
	comment_list->last = comment;
	comment_list->size = 1;
	comment_list->next = NULL;
	comment_list->previous = NULL;

	// set the first element of the master list
	master_list->first = comment_list;
	master_list->last = comment_list;
	master_list->size = 0;
	fGetComment(master_list);
}

void fTestComment()
{
	fFullScreen();
	MASTER_COMMENT* master_list;
	master_list = (MASTER_COMMENT*)malloc(sizeof(*master_list));
	MEMBER_LIST* member_list;
	member_list = (MEMBER_LIST*)malloc(sizeof(*member_list));
	MEMBER* current_mem;
	current_mem = (MEMBER*)malloc(sizeof(*current_mem));
	current_mem->username = (char*)"pierre";
	member_list->logged = current_mem;


	fMemberStart(member_list);
	fCommentStart(master_list);
	fDisplayCommentList(master_list);
	int brain_id;
	printf("Enter an id : ");
	scanf_s("%d", &brain_id);
	fDisplayFirstComm(master_list, brain_id);
	/*fDisplayComment(master_list, brain_id);
	fDelComment(master_list, brain_id);
	fDisplayComment(master_list, brain_id);
	
	fDisplayComment(master_list, 0002);
	Sleep(2000);
	clear_screen(' ');
	fPostComment(master_list, member_list, 0006);
	fDisplayComment(master_list, 0006);
	Sleep(5000);
	clear_screen(' ');
	getchar();
	fPostComment(master_list, member_list, 0002);
	fDisplayComment(master_list, 0002);
	*/
}

void fDisplayCommentList(MASTER_COMMENT* master_list)
{
	COMMENT_LIST* comment_list;
	comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));
	comment_list = master_list->first->next;

	printf("+----------+-------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("| Brain ID | Number of comment |                                                                           Last Comment                                                                           |\n");
	printf("+----------+-------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	while (comment_list != NULL)
	{
		printf("|     %04d |   %4d Comment(s) | %160s |\n", comment_list->brain_id, comment_list->size, comment_list->last->comment);
		comment_list = comment_list->next;
	}
	printf("+----------+-------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("	Number of brains with comments : %4d\n", master_list->size);
}

void fGetComment(MASTER_COMMENT* master_list)
{
	FILE* comment_file;
	comment_file = (FILE*)malloc(sizeof(*comment_file));
	char path[] = "comment.txt";
	fopen_s(&comment_file, path, "r+");
	char* str;
	str = (char*)malloc(250);

	while (fgets(str, 200, comment_file) != NULL)
	{
		int brain_id = 0;
		char* member_name;
		member_name = (char*)malloc(15);
		char* date;
		date = (char*)malloc(15);
		float note = 0.00;
		char* description;
		description = (char*)malloc(161);

		fSplitComment(&brain_id, date, description, &note, member_name, str);

		COMMENT_LIST* comment_list;
		comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));
		comment_list = master_list->first;

		while (comment_list->brain_id != brain_id)
		{
			comment_list = comment_list->next;
			if (comment_list == NULL)
			{
				break;
			}
		}

		if (comment_list == NULL)
		{
			fAddCommentList(master_list, brain_id, date, description, note, member_name);
		}
		else
		{
			fAddComment(master_list, brain_id, date, description, note, member_name);
		}
	}
	fclose(comment_file);
}

void fSplitComment(int* brain_id, char* date, char* description, float* note, char* member_name, char* str)
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
				pos1 = i + 1;
			}
			else if (pos2 == 0)
			{
				pos2 = i + 1;
			}
			else if (pos3 == 0)
			{
				pos3 = i + 1;
			}
			else if (pos4 == 0)
			{
				pos4 = i + 1;
			}
		}
	}

	char* temp;
	temp = (char*)malloc(165);

	// Recover the id of the linked brain
	for (int i = 0; i < pos1; i++)
	{
		temp[i] = str[i];
	}
	temp[pos1 - 1] = '\0';
	*brain_id = atoi(temp);

	// Recover the name of the member 
	for (int i = pos1; i < pos2; i++)
	{
		member_name[i - pos1] = str[i];
	}
	member_name[pos2 - pos1 - 1] = '\0';	
	
	// Recover the date of the comment
	for (int i = pos2; i < pos3; i++)
	{
		date[i - pos2] = str[i];
	}
	date[pos3 - pos2 - 1] = '\0';

	// Recover the note of the comment
	for (int i = pos3; i < pos4; i++)
	{
		temp[i - pos3] = str[i];
	}
	temp[pos4 - pos3 - 1] = '\0';
	*note = atof(temp);

	// Recover the note of the brain
	for (int i = pos4; i < length; i++)
	{
		description[i - pos4] = str[i];
	}
	description[length - pos4 - 1] = '\0';
}

void fAddCommentList(MASTER_COMMENT* master_list, int brain_id, char* date, char* description, float note, char* member_name)
{
	COMMENT_LIST* comment_list;
	comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));
	COMMENT* comment;
	comment = (COMMENT*)malloc(sizeof(*comment));

	// Initialize the first comment
	comment->brain_id = brain_id;
	comment->comment = description;
	comment->date = date;
	comment->member_name = member_name;
	comment->note = note;
	comment->next = NULL;
	comment->previous = NULL;

	// Initialize the comment_list
	comment_list->brain_id = brain_id;
	comment_list->first = comment;
	comment_list->last = comment;
	comment_list->size = 1;
	
	// Link the comment list in the master list
	master_list->last->next = comment_list;
	comment_list->previous = master_list->last;
	comment_list->next = NULL;
	master_list->last = comment_list;
	master_list->size += 1;
}

void fAddComment(MASTER_COMMENT* master_list, int brain_id, char* date, char* description, float note, char* member_name)
{
	COMMENT_LIST* comment_list;
	comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));
	COMMENT* comment;
	comment = (COMMENT*)malloc(sizeof(*comment));

	comment_list = master_list->first;
	while (comment_list->brain_id != brain_id)
	{
		comment_list = comment_list->next;
		if (comment_list == NULL)
		{
			break;
		}
	}

	// Initialize the new comment
	comment->brain_id = brain_id;
	comment->comment = description;
	comment->date = date;
	comment->member_name = member_name;
	comment->note = note;
	comment->next = NULL;

	// Link the comment in the list 
	comment_list->last->next = comment;
	comment->previous = comment_list->last;
	comment_list->last = comment;

	
}

void fDisplayComment(MASTER_COMMENT* master_list, int brain_id)
{
	COMMENT_LIST* comment_list;
	comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));
	COMMENT* comment;
	comment = (COMMENT*)malloc(sizeof(*comment));

	comment_list = master_list->first;
	while (comment_list->brain_id != brain_id)
	{
		comment_list = comment_list->next;
		if (comment_list == NULL)
		{
			break;
		}
	}

	if (comment_list == NULL)
	{
		printf("No comment on this particular brain...\n");
	}
	else
	{
		comment = comment_list->first;
		while (comment != NULL)
		{
			printf("+------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
			printf("|      Username : %15s                                                                                             Publication Date : %12s      |\n", comment->member_name, comment->date);
			printf("|                                                                                                                                                                  |\n");
			printf("| %160s |\n", comment->comment);
			printf("|                                                                                                                                                                  |\n");
			printf("+------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

			comment = comment->next;
		}
	}


}

void fPostComment(MASTER_COMMENT* master_list, MEMBER_LIST* member_list, int brain_id)
{
	COMMENT_LIST* comment_list;
	comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));
	comment_list = master_list->first;

	char* description;
	char* date;
	char* member_name;
	float note;
	description = (char*)malloc(160);
	date = (char*)malloc(15);
	member_name = (char*)malloc(15);
	fGetDate(date);
	printf("Enter your comment (160 characters max) : ");
	fgets(description, 160, stdin);
	Sleep(250);
	printf("Enter the note of this brain : ");
	scanf_s("%f", &note);
	description[strlen(description) - 1] = '\0';
	member_name = member_list->logged->username;

	while (comment_list->brain_id != brain_id)
	{
		comment_list = comment_list->next;
		if (comment_list == NULL)
		{
			break;
		}
	}

	if (comment_list == NULL)
	{
		fAddCommentList(master_list, brain_id, date, description, note, member_name);
	}
	else
	{
		fAddComment(master_list, brain_id, date, description, note, member_name);
	}	
	fWriteComment(master_list);
}

void fWriteComment(MASTER_COMMENT* master_list)
{
	FILE* comment_file;
	comment_file = (FILE*)malloc(sizeof(*comment_file));
	char path[] = "comment.txt";
	fopen_s(&comment_file, path, "w+");

	COMMENT_LIST* my_comment_list;
	my_comment_list = (COMMENT_LIST*)malloc(sizeof(*my_comment_list));
	my_comment_list = master_list->first->next;

	COMMENT* my_comment;
	my_comment = (COMMENT*)malloc(sizeof(*my_comment));

	// We want the brain to be written as : brain_id/member_name/date/note/description
	while (my_comment_list != NULL)
	{
		my_comment = my_comment_list->first;
		while (my_comment != NULL)
		{
			fprintf(comment_file, "%04d/%s/%s/%.2f/%s\n", my_comment->brain_id, my_comment->member_name, my_comment->date, my_comment->note, my_comment->comment);
			my_comment = my_comment->next;
		}
		my_comment_list = my_comment_list->next;
	}
	fclose(comment_file);
}

void fDelComment(MASTER_COMMENT* master_list, int brain_id)
{
	COMMENT_LIST* comment_list;
	comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));

	COMMENT* comment;
	comment = (COMMENT*)malloc(sizeof(*comment));

	comment_list = master_list->first;

	while (comment_list->brain_id != brain_id)
	{
		comment_list = comment_list->next;
		if (comment_list == NULL)
		{
			break;
		}
	}

	if (comment_list != NULL)
	{
		char* description;
		description = (char*)malloc(165);
		getchar();
		printf("Copy-Paste the description of the comment you want to delete : \n");
		fgets(description, 160, stdin);
		description[strlen(description) - 1] = '\0';

		comment = comment_list->first;

		while (strcmp(description, comment->comment) != 0)
		{
			printf("%s / %s\n", description, comment->comment);
			comment = comment->next;
			if (comment == NULL)
			{
				break;
			}
		}

		if (comment != NULL)
		{
			if (comment->next != NULL)
			{
				comment->next->previous = comment->previous;
				comment->previous->next = comment->next;
			}
			else
			{
				comment->previous->next = NULL;
				comment_list->last = comment->previous;
			}
			printf("Succeed in deleting the comment\n");
			free(comment);
		}
		else
		{
			printf("There is no comment that correspond to this description\n");
			fDelComment(master_list, brain_id);
		}
		fWriteComment(master_list);
	}
}

void fDisplayFirstComm(MASTER_COMMENT* master_list, int brain_id)
{
	COMMENT_LIST* comment_list;
	comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));
	COMMENT* comment;
	comment = (COMMENT*)malloc(sizeof(*comment));

	comment_list = master_list->first;
	while (comment_list->brain_id != brain_id)
	{
		comment_list = comment_list->next;
		if (comment_list == NULL)
		{
			break;
		}
	}

	if (comment_list == NULL)
	{
		printf("No comment on this particular brain...\n");
	}
	else
	{
		comment = comment_list->first;
		for (int i = 0; i<3; i++)
		{
			if (comment != NULL)
			{
				printf("+------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
				printf("|      Username : %15s                                                                                             Publication Date : %12s      |\n", comment->member_name, comment->date);
				printf("|                                                                                                                                                                  |\n");
				printf("| %160s |\n", comment->comment);
				printf("|                                                                                                                                                                  |\n");
				printf("+------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

				comment = comment->next;
			}
			else
			{
				break;
			}
		}
	}
}