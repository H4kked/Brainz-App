#pragma once

typedef struct MEMBER MEMBER;
typedef struct MEMBER_LIST MEMBER_LIST;
typedef struct COMMENT COMMENT;
typedef struct COMMENT_LIST COMMENT_LIST;
typedef struct BRAIN BRAIN;
typedef struct BRAIN_LIST BRAIN_LIST;

struct MEMBER
{
	char* username;
	char* password;
	char* desc;
	int is_admin;
	int brain_id;
	MEMBER* previous;
	MEMBER* next;
};
struct MEMBER_LIST
{
	int size;
	MEMBER* first;
	MEMBER* logged;
	MEMBER* last;
};
struct COMMENT
{
	struct MEMBER* member;
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
	float note;
	BRAIN* previous;
	BRAIN* next;
};
struct BRAIN_LIST
{
	int size;
	BRAIN* first;
	BRAIN* last;
};

void fMenuDisplay(MEMBER_LIST* list);
void clear_screen(char fill = ' ');
void fPrintLogo();
void fPrintLoading(MEMBER_LIST* member_list);
void fFullScreen();