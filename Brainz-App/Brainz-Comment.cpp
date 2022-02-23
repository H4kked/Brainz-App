#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
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

	fCommentStart(master_list);
	fDisplayCommentList(master_list);
	fDisplayComment(master_list, 0002);
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
	str = (char*)malloc(200);

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

}