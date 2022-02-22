#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "Brainz-Members.h"

void fSignUp(MEMBER_LIST* list)
{
	MEMBER* new_member;
	new_member = (MEMBER*)malloc(sizeof(*new_member));


	//CREATES MEMBER PARAMETERS
	char* username;
	char* password;
	char* desc;
	username = (char*)malloc(sizeof(*username));
	password = (char*)malloc(sizeof(*password));
	desc = (char*)malloc(sizeof(*desc));
	new_member->next = NULL;

	//ASSIGN PARAMETERS TO NEW MEMBER
	getchar();
	printf("											Username: ");
	fgets(new_member->username, 20, stdin);
	new_member->username[strlen(username) - 1] = '\0';
	printf("											Password: ");
	fgets(new_member->password, 20, stdin);
	new_member->password[strlen(password) - 1] = '\0';
	printf("											Description: ");
	fgets(new_member->desc, 100, stdin);
	new_member->desc[strlen(desc) - 1] = '\0';

	//PLACES NEW MEMBER IN MEMBER LIST
	list->last->next = new_member;
	new_member->previous = list->last;
	new_member = list->last;

	printf("\n\n										Account created. Welcome, %s !\n", username);
	Sleep(3000);
	clear_screen(' ');
	fLogIn(list);
}
void fLogIn(MEMBER_LIST* list)
{
	//INITIALIZE LIST TO GO THROUGH
	MEMBER* current;
	MEMBER* pending;
	current = (MEMBER*)malloc(sizeof(*current));
	pending = (MEMBER*)malloc(sizeof(*pending));
	current = list->first;

	//USER PARAMETERS
	char* username;
	char* password;
	getchar();
	printf("\n												Username: ");
	username = (char*)malloc(sizeof(*username));
	fgets(username, 15, stdin);
	username[strlen(username) - 1] = '\0';
	printf("\n												Password: ");
	password = (char*)malloc(sizeof(*password));
	fgets(password, 15, stdin);
	password[strlen(password) - 1] = '\0';
	printf("\n									Press 9 to exit. Press any key to continue.\n");
	int n;
	scanf_s("%d", &n);

	//USER CHECK
	do
	{
		if (n == 9)
		{
			clear_screen(' ');
			fMenuDisplay(list);
		}
		if (strcmp(username, current->username) == 0)
		{
			if (strcmp(password, current->password) == 0)
			{
				//THE USER HAS BEEN RECOGNIZED
				printf("											Connected ! Welcome, %s.\n", username);
				Sleep(2000);

				fLoggedMenu(list, current);
			}
		}
	} while (current->next != NULL);

	//THE USER HAS NOT BEEN RECOGNIZED
	printf("									Incorrect username or password. Please try again.");
	Sleep(3000);
	fLogIn(list);
}
void fLoggedMenu(MEMBER_LIST* list, MEMBER* current)
{
	
}