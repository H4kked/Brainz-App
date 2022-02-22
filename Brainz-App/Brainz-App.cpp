#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include "Brainz-Members.h"
#include "Brainz-Brains.h"
#include "Brainz-Menu.h"
#include "Brainz-Comment.h"


int main() 
{
	MEMBER_LIST* member_list;
	member_list = (MEMBER_LIST*)malloc(sizeof(*member_list));
	BRAIN_LIST* brains_list;
	brains_list = (BRAIN_LIST*)malloc(sizeof(*brains_list));
	fTestComment();
	//fMenuDisplay(member_list, brains_list);
	return 0;
}