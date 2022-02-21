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
	struct BRAIN* current_brain;
	struct MEMBER* previous;
	struct MEMBER* next;
};
struct MEMBER_LIST
{
	int size;
	struct MEMBER* first;
	struct MEMBER* logged;
	struct MEMBER* last;
};
struct COMMENT
{
	struct MEMBER* member;
	char* comment;
	int note;
	char* date;
	struct COMMENT* previous;
	struct COMMENT* next;
};
struct COMMENT_LIST
{
	int name;
	int size;
	struct COMMENT* first;
	struct COMMENT* last;
};
struct BRAIN
{
	int id;
	char* name;
	char* desc;
	int is_available;
	struct COMMENT_LIST* list;
	float note;
	struct BRAIN* previous;
	struct BRAIN* next;
};
struct BRAIN_LIST
{
	int size;
	struct BRAIN* first;
	struct BRAIN* last;
};

void fMenuDisplay(MEMBER_LIST* list);
void clear_screen(char fill = ' ');
void fPrintLogo();
void fPrintLoading();
void fLogIn(MEMBER_LIST* list);
void fSignUp(MEMBER_LIST* list);
void fLoggedMenu();