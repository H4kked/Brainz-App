#pragma once

typedef struct BRAIN BRAIN;
struct BRAIN
{
	int id;
	char* name;
	char* desc;
	int is_available;

	int note;
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