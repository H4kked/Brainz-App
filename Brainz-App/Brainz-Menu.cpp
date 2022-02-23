#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <Windows.h>
#include <time.h>
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
void fUserScreen(MEMBER* current_member, BRAIN_LIST* brain_list, MEMBER_LIST* member_list)
{
	clear_screen(' ');
	Sleep(50);
	fPrintLogo();

	printf("										1 - BORROW A BRAIN\n");
	printf("										2 - RETURN A BRAIN\n");
	printf("										3 - MY ACCOUNT\n");
	printf("\n										9 - EXIT\n");
	printf("\n										Entry : ");

	int choice = 0;
	scanf_s("%d", &choice);

	switch (choice)
	{
		case 1:
			clear_screen(' ');
			fPrintLogo();
			fBorrowBrain(member_list, brain_list, current_member);
			break;
		case 2:
			fReturnBrain(member_list, brain_list, current_member);
		case 3:
			printf("my account");
			break;
		case 9:
			printf("exit");
			break;
	}
}

void fGetDate(char* date)
{
	int day, month, year;
	
	time_t current_time = time(NULL);

	//printf("Time : %d\n", current_time);

	struct tm* local;
	local = (tm*)malloc(sizeof(*local));

	localtime_s(local, &current_time);

	day = local->tm_mday;                // Get the day of today (an int between 1 and 31)
	month = local->tm_mon + 1;			 // Get the monthe of today (an int between 0 and 11)
	year = local->tm_year + 1900;		 // Get the number of year since 1900


	//printf("Today is : %02d-%02d-%4d\n", day, month, year);
	sprintf_s(date, 15, "%02d-%02d-%4d", day, month, year);  // Convert the integers to a date under the format DD-MM-YYYY
	//printf("Today (but different) is : %s", date);


}