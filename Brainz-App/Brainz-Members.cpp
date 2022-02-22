#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <Windows.h>
#include "Brainz-Members.h"

void fMenuDisplay(MEMBER_LIST* list)
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
	printf("\n\n\n\n\n");
	fPrintLogo();
	fPrintLoading();
	Sleep(1000);

	int choice;
	printf("\n\n\n\n   										     Log in (1) - Sign Up (2) - Exit (9)\n   												Entry: ");
	do {
		scanf_s("%d", &choice);
	} while ((choice > 2 && choice < 9) || (choice > 9) || isdigit(choice) == 1);
	switch (choice)
	{
		case 1:
			fLogIn(list);
			break;
		case 2:
			fSignUp(list);
			break;
		default:
			exit(0);
	}

	clear_screen(' ');
}

void clear_screen(char fill) {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}
void fPrintLogo()
{
	//PRINT THE LOGO WHAT DO YOU WANT ME TO SAY
	printf("\n\
											      _---~~(~~-_.\n\
											    _{        )   )\n\
											  ,   ) -~~- ( ,-' )_\n\
											 (  `-,_..`., )-- '_,)\n\
											( ` _)  (  -~( -_ `,  }\n\
											(_-  _  ~_-~~~~`,  ,' )\n\
											  `~ -^(    __;-,((()))\n\
										     	        ~~~~ {_ -_(())\n\
							 				  _            `\\  }       \n\
											 | |             { }               +++\n\
											 | |__  _ __ __ _ _ _ __ _____   ++\n\
											 | '_ \\| '__/ _` | | '_ \\ _   /\n\
											 | |_) | | | (_| | | | | | / /_ _    \n\
											 |_.__/|_| \\____ |_|_| |_|/____|_|   \n\
											  =============================inc.\n\n");
	printf("										Welcome to BRAINZ ! The place where skills become yours.\n\n\n\n\n");
}
void fPrintLoading()
{
	//MAKES US LOOK LIKE BOSSES
	Sleep(3000);
	printf("											Loading");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
	Sleep(2000);
	printf("	Initialized !");
}
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