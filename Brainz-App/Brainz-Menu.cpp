#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <Windows.h>
#include "Brainz-Menu.h"
#include "Brainz-Members.h"
#include "Brainz-Brains.h"

void fMenuDisplay(MEMBER_LIST* member_list, BRAIN_LIST* brain_list)
{
	fFullScreen();
	printf("\n\n\n\n\n");
	fPrintLogo();
	fPrintLoading(member_list, brain_list);
	Sleep(1000);

	int choice;
	printf("\n\n\n\n   										     Log in (1) - Sign Up (2) - Exit (9)\n   												Entry: ");
	do {
		scanf_s("%d", &choice);
	} while ((choice > 2 && choice < 9) || (choice > 9) || isdigit(choice) == 1);
	switch (choice)
	{
	case 1:
		fLogIn(member_list, brain_list);
		break;
	case 2:
		fSignUp(member_list, brain_list);
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
void fPrintLoading(MEMBER_LIST* member_list, BRAIN_LIST* brain_list)
{
	//MAKES US LOOK LIKE BOSSES
	Sleep(3000);
	printf("											Loading");
	Sleep(1000);
	printf(".");
	fMemberStart(member_list);
	Sleep(1000);
	printf(".");
	fBrainStart(brain_list);
	Sleep(1000);
	printf(".");
	Sleep(2000);
	printf("	Initialized !");
}
void fFullScreen()
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
}