#pragma once
#include "Brainz-Saves.h"

typedef struct BRAIN BRAIN;
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

typedef struct BRAIN_LIST BRAIN_LIST;
struct BRAIN_LIST
{
	int size;
	BRAIN* first;
	BRAIN* last;
};

typedef struct MEMBER MEMBER;
struct MEMBER
{
	char* username;
	char* password;
	char* desc;
	int is_admin;
	BRAIN* current_brain;
};

typedef struct MEMBER_LIST MEMBER_LIST;
struct MEMBER_LIST
{
	int size;
	MEMBER* first;
	MEMBER* last;
};

typedef struct COMMENT COMMENT;
struct COMMENT
{
	MEMBER* member;
	char* comment;
	int note;
	char* date;
	COMMENT* previous;
	COMMENT* next;
};

typedef struct COMMENT_LIST COMMENT_LIST;
struct COMMENT_LIST
{
	int name;
	int size;
	COMMENT* first;
	COMMENT* last;
};