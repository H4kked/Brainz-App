#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include "Brainz-App.h"
#include "Brainz-Saves.h"



int main() 
{
	MEMBER_LIST* list;
	list = (MEMBER_LIST*)malloc(sizeof(MEMBER_LIST*));

	//fMenuDisplay(list);
	fMainSaves();
	return 0;
}