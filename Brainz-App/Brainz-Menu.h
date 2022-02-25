#pragma once

typedef struct MEMBER MEMBER;
typedef struct MEMBER_LIST MEMBER_LIST;
typedef struct COMMENT COMMENT;
typedef struct COMMENT_LIST COMMENT_LIST;
typedef struct MASTER_COMMENT MASTER_COMMENT;
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
	char* member_name;
	char* comment;
	float note;
	char* date;
	int brain_id;
	COMMENT* previous;
	COMMENT* next;
};
struct COMMENT_LIST
{
	int brain_id;
	int size;
	COMMENT* first;
	COMMENT* last;
	COMMENT_LIST* next;
	COMMENT_LIST* previous;
};

struct MASTER_COMMENT
{
	int size;
	COMMENT_LIST* first;
	COMMENT_LIST* last;
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

void fMenuDisplay(MEMBER_LIST* list, BRAIN_LIST* brain_list, MASTER_COMMENT* master_list);
void clear_screen(char fill = ' ');
void color_screen();
void fPrintLogo();
void fPrintLoading(MEMBER_LIST* member_list, BRAIN_LIST* brain_list, MASTER_COMMENT* master_list);
void fFullScreen();

void fUserScreen(BRAIN_LIST* brain_list, MEMBER_LIST* member_list, MASTER_COMMENT* master_list);
void fAdminScreen(BRAIN_LIST* brain_list, MEMBER_LIST* member_list, MASTER_COMMENT* master_list);
void fMemberAccountScreen(MEMBER_LIST* member_list, BRAIN_LIST* brain_list, MASTER_COMMENT* master_list);
void fAdminAccountScreen(MEMBER_LIST* member_list, BRAIN_LIST* brain_list, MASTER_COMMENT* master_list);
void fMemberBrainPage(MASTER_COMMENT* master_list, MEMBER_LIST* member_list, BRAIN_LIST* brain_list, BRAIN* brain);

void fGetDate(char* date);