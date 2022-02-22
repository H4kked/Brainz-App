#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include "Brainz-App.h"
#include "Brainz-Brains.h"



int main() 
{
	MEMBER_LIST* list;
	list = (MEMBER_LIST*)malloc(sizeof(MEMBER_LIST*));
	BRAIN_LIST* brains_list;
	brains_list = (BRAIN_LIST*)malloc(sizeof(*brains_list));
	fMenuDisplay(list);
	fMainSaves();
	return 0;
}