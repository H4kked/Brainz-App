#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "Brainz-App.h"

struct MEMBER
{
	char* username;
	char* password;
	char* desc;
	int is_admin;
	BRAIN* current_brain;
	MEMBER* previous;
	MEMBER* next;
};
struct MEMBER_LIST
{
	int size;
	MEMBER* first;
	MEMBER* last;
};
struct COMMENT
{
	MEMBER* member;
	char* comment;
	int note;
	char* date;
	COMMENT* previous;
	COMMENT* next;
};
struct COMMENT_LIST
{
	int name;
	int size;
	COMMENT* first;
	COMMENT* last;
};
struct BRAIN
{
	int id;
	char* name;
	char* desc;
	int is_available;
	COMMENT_LIST* list;
	int note;
	BRAIN* previous;
	BRAIN* next;
};
struct BRAIN_LIST
{
	int size;
	BRAIN* first;
	BRAIN* last;
};

void fMenuDisplay()
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
	fPrintLogo();
	fPrintLoading();
	Sleep(1000);

	clear_screen(' ');

	int choice;
	printf("\n\n											Log in (1) - Sign Up (2) - Exit (9)");
	do {
		scanf_s("%d", &choice);
	} while (choice > 2 && choice < 9 || choice > 9);
	switch (choice)
	{
		case 1:
			fLogIn();
			break;
		case 2:
			fSignUp();
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
void fSignUp()
{
	MEMBER* new_member;
	MEMBER_LIST* list;
	new_member = (MEMBER*)malloc(sizeof(*new_member));
	list = (MEMBER_LIST*)malloc(sizeof(*list));


	//CREATES MEMBER PARAMETERS
	char* username;
	char* password;
	char* desc;
	printf("											Username: ");
	username = (char*)malloc(sizeof(*username));
	printf("											Password: ");
	password = (char*)malloc(sizeof(*password));
	printf("											Description: ");
	desc = (char*)malloc(sizeof(*desc));
	new_member->next = NULL;

	//ASSIGN PARAMETERS TO NEW MEMBER
	fgets(new_member->username, 20, stdin);
	new_member->username[strlen(username) - 1] = '\0';
	fgets(new_member->password, 20, stdin);
	new_member->password[strlen(password) - 1] = '\0';
	fgets(new_member->desc, 100, stdin);
	new_member->desc[strlen(desc) - 1] = '\0';

	//PLACES NEW MEMBER IN MEMBER LIST
	list->last->next = new_member;
	new_member->previous = list->last;
	new_member = list->last;

	printf("\n\n										Account created. Welcome, %s !\n", username);
	Sleep(3000);
	clear_screen(' ');
	fLogIn();
}
void fLogIn()
{
	//INITIALIZE LIST TO GO THROUGH
	MEMBER* current;
	MEMBER* pending;
	MEMBER_LIST* list;
	current = (MEMBER*)malloc(sizeof(*current));
	pending = (MEMBER*)malloc(sizeof(*pending));
	list = (MEMBER_LIST*)malloc(sizeof(*list));
	current = list->first;

	//USER PARAMETERS
	char* username;
	char* password;
	printf("\n											Username: ");
	username = (char*)malloc(sizeof(*username));
	printf("\n											Password: ");
	password = (char*)malloc(sizeof(*password));
	printf("\n									Press 9 to exit. Press any key to continue.\n");
	int n;
	scanf_s("%d", &n);

	//USER CHECK
	do
	{
		if (n == 9)
		{
			clear_screen(' ');
			fMenuDisplay();
		}
		if (strcmp(username, current->username) == 0)
		{
			if (strcmp(password, current->password) == 0)
			{
				printf("											Connected ! Welcome, %s.\n", username);
				Sleep(2000);
				fLoggedMenu();
			}
		}
	} while (current->next != NULL);

	//THE USER HAS NOT BEEN RECOGNIZED
	printf("									Incorrect username or password. Please try again.");
	Sleep(3000);
	fLogIn();
}
void fLoggedMenu()
{

}