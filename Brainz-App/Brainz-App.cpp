#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include "Brainz-Members.h"
#include "Brainz-Brains.h"
#include "Brainz-Menu.h"
#include "Brainz-Comment.h"


int main() 
{
	MEMBER_LIST* member_list;
	member_list = (MEMBER_LIST*)malloc(sizeof(*member_list));
	BRAIN_LIST* brain_list;
	brain_list = (BRAIN_LIST*)malloc(sizeof(*brain_list));
	MASTER_COMMENT* master_list;
	master_list = (MASTER_COMMENT*)malloc(sizeof(*master_list));

	fMenuDisplay(member_list, brain_list, master_list);
	return 0;
}