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
void color_screen()
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int txt_col = 0;
	int bgd_color = 0;
	int col = 0;

	printf("\nChoose the text and background color (ex : 0 15) : \n");
	printf("0 - Black		8 - Gray\n");
	printf("1 - Blue		9 - Light Blue\n");
	printf("2 - Green		10 - Light Green\n");
	printf("3 - Aqua		11 - Light Aqua\n");
	printf("4 - Red			12 - Light Red\n");
	printf("5 - Purple		13 - Light Purple\n");
	printf("6 - Yellow		14 - Light Yellow\n");
	printf("7 - White		15 - Bright White\n\n");
	scanf_s("%d %d", &txt_col, &bgd_color);

	col = txt_col + 16 * bgd_color;

	// color your text in Windows console mode
	// colors are 0=black 1=blue 2=green and so on to 15=white  
	// colorattribute = foreground + background * 16
	// to get red text on yellow use 4 + 14*16 = 228
	// light red on yellow would be 12 + 14*16 = 236

	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, col);
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
	printf("%s\n", member_list->logged->username);

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
			break;
		case 3:
			if (member_list->logged->is_admin == 0)
			{
				fMemberAccountScreen(member_list, brain_list);
			}
			else
			{
				fAdminAccountScreen(member_list, brain_list);
			}
			break;
		case 9:
			fMenuDisplay(member_list, brain_list);
			break;
	}
	fMenuDisplay(member_list, brain_list);
}
void fAdminScreen(MEMBER* current_member, BRAIN_LIST* brain_list, MEMBER_LIST* member_list)
{
	clear_screen(' ');
	Sleep(50);
	fPrintLogo();

	printf("										1 - BORROW A BRAIN\n");
	printf("										2 - RETURN A BRAIN\n");
	printf("										3 - MY ACCOUNT\n");
	printf("										4 - MANAGE BRAINS\n");
	printf("										5 - MANAGE MEMBERS\n");
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
		break;
	case 3:
		if (member_list->logged->is_admin == 0)
		{
			fMemberAccountScreen(member_list, brain_list);
		}
		else
		{
			fAdminAccountScreen(member_list, brain_list);
		}
		break;
	case 4:
		fBrainManagement(member_list, brain_list);
		break;
	case 5:
		fMemberManagement(member_list, brain_list);
	case 9:
		fMenuDisplay(member_list, brain_list);
		break;
	}
	fMenuDisplay(member_list, brain_list);
}
void fMemberAccountScreen(MEMBER_LIST* member_list, BRAIN_LIST* brain_list)
{
	clear_screen(' ');

	// PRINT THE LOGO
	fPrintLogo();

	// PRINT USER NAME
	printf("\n\n												+-----------------+\n");
	printf("												| %15s |\n", member_list->logged->username);
	printf("												+-----------------+\n");

	// PRINT USER DESCRIPTION
	printf("									Description : %s\n", member_list->logged->desc);

	// CHECK IF USER HAS BORROWED A BRAIN
	if (member_list->logged->brain_id != 0)
	{
		BRAIN* brain;
		brain = (BRAIN*)malloc(sizeof(*brain));
		brain = brain_list->first;

		while (brain->id != member_list->logged->brain_id && brain != NULL)
		{
			brain = brain->next;
			if (brain == NULL)
			{
				break;
			}
		}

		// IF USER HAS BORROWED A BRAIN, PRINT BRAIN INFORMATION
		printf("\n\n								Current brain : \n\n");
		printf("											Name : %s\n", brain->name);
		printf("											Description : %s\n\n\n", brain->desc);
	}
	else
	{
		// ELSE PRINT NONE
		printf("\n\n								Current brain : NONE\n\n\n");
	}

	printf("								+------+");
	printf("								|-MENU-|");
	printf("								+------+");

	printf("						1 - Edit description");
	printf("						2 - Return brain");
	printf("						3 - Delete account");
	printf("						9 - Return to main menu");

	int choice = 0;
	switch (choice)
	{
		case 1:
			char* new_desc;
			new_desc = (char*)malloc(sizeof(*new_desc));
			fgets(new_desc, 100, stdin);

			member_list->logged->desc = new_desc;
			fWriteMember(member_list);
			break;
		case 2:
			fReturnBrain(member_list, brain_list, member_list->logged);
			break;
		case 3:
			fDelMember(member_list, brain_list);
			break;
		case 9:
			fUserScreen(member_list->logged, brain_list, member_list);
			break;
	}
	fUserScreen(member_list->logged, brain_list, member_list);
}
void fAdminAccountScreen(MEMBER_LIST* member_list, BRAIN_LIST* brain_list)
{
	clear_screen(' ');

	// PRINT THE LOGO
	fPrintLogo();

	// PRINT USER NAME
	printf("\n\n												+-------------------+\n");
	printf("												| ★%15s★ |\n", member_list->logged->username);
	printf("												+-------------------+\n");

	// PRINT USER DESCRIPTION
	printf("									Description : %s\n", member_list->logged->desc);

	// CHECK IF USER HAS BORROWED A BRAIN
	if (member_list->logged->brain_id != 0)
	{
		BRAIN* brain;
		brain = (BRAIN*)malloc(sizeof(*brain));
		brain = brain_list->first;

		while (brain->id != member_list->logged->brain_id && brain != NULL)
		{
			brain = brain->next;
			if (brain == NULL)
			{
				break;
			}
		}

		// IF USER HAS BORROWED A BRAIN, PRINT BRAIN INFORMATION
		printf("\n\n								Current brain : \n\n");
		printf("											Name : %s\n", brain->name);
		printf("											Description : %s\n\n\n", brain->desc);
	}
	else
	{
		// ELSE PRINT NONE
		printf("\n\n								Current brain : NONE\n\n\n");
	}

	printf("								+------+");
	printf("								|-MENU-|");
	printf("								+------+");

	printf("						1 - Edit description");
	printf("						2 - Return brain");
	printf("						3 - Delete account");
	printf("						9 - Return to main menu");

	int choice = 0;
	switch (choice)
	{
	case 1:
		char* new_desc;
		new_desc = (char*)malloc(sizeof(*new_desc));
		fgets(new_desc, 100, stdin);

		member_list->logged->desc = new_desc;
		fWriteMember(member_list);
		break;
	case 2:
		fReturnBrain(member_list, brain_list, member_list->logged);
		break;
	case 3:
		fDelMember(member_list, brain_list);
		break;
	case 9:
		fUserScreen(member_list->logged, brain_list, member_list);
		break;
	}
	fUserScreen(member_list->logged, brain_list, member_list);
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