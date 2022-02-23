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
	comment->member = NULL;
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
	master_list->size = 1;
}

void fTestComment()
{
	fFullScreen();
	MASTER_COMMENT* master_list;
	master_list = (MASTER_COMMENT*)malloc(sizeof(*master_list));

	fCommentStart(master_list);
	fDisplayCommentList(master_list);

}

void fDisplayCommentList(MASTER_COMMENT* master_list)
{
	COMMENT_LIST* comment_list;
	comment_list = (COMMENT_LIST*)malloc(sizeof(*comment_list));
	comment_list = master_list->first;

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

