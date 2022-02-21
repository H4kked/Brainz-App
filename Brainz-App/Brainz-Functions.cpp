#include <stdio.h>
#include <Windows.h>
#include "Brainz-App.h"

struct MEMBER
{
	char* username;
	char* password;
	char* desc;
	int is_admin;
	BRAIN* current_brain;
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
	fPrintLogo();
	fPrintLoading();
	Sleep(1000);
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