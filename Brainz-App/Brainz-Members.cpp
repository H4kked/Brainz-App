#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <Windows.h>
#include "Brainz-Menu.h"
#include "Brainz-Members.h"

void fMemberSaves()
{
	MEMBER_LIST* member_list;
	member_list = (MEMBER_LIST*)malloc(sizeof(*member_list));
	MEMBER* first_member;
	first_member = (MEMBER*)malloc(sizeof(*member_list));
	first_member->desc = (char*)"The first member ever";
	first_member->username = (char*)"Username";
	first_member->password = (char*)"Password";
	first_member->desc = (char*)"Description";
	first_member->is_admin = 1;
	first_member->brain_id = 0000;
	first_member->next = NULL;
	first_member->previous = NULL;

	member_list->first = first_member;
	member_list->last = first_member;
	member_list->size = 0;
	fGetMember(member_list);
	fDisplayMemberList(member_list);
	fAddMember(member_list);
	fDisplayMemberList(member_list);
}
void fGetMember(MEMBER_LIST* member_list)
{

	FILE* member_file;
	member_file = (FILE*)malloc(sizeof(FILE*));
	char path[] = "member.txt";
	fopen_s(&member_file, path, "r+");
	char* str;
	str = (char*)malloc(200);

	while (fgets(str, 200, member_file) != NULL)
	{
		//printf("%s\n", str);
		int id = 0;
		char* username;
		char* password;
		char* description;
		int is_admin = 1;
		int brain_id = 0;
		password = (char*)malloc(20);
		username = (char*)malloc(20);
		description = (char*)malloc(180);
		fSplitMember(username, password, description, &is_admin, brain_id, str);
		fAddMemberEnd(member_list, username, password, description, is_admin, brain_id);

		//printf("last : %s\nbefore_last : \nsecond : %s\nfirst : \n\n", member_list->last->name, member_list->last->previous->name, member_list->first->next->name, member_list->first->name);
	}
	fclose(member_file);
}
void fSplitMember(char* username, char* password, char* description, int* is_admin, int brain_id, char* str)
{
	int pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
	char splitter = '/';
	int length = strlen(str);

	for (int i = 0; i < length; i++)
	{
		if (str[i] == splitter)
		{
			if (pos1 == 0)
			{
				pos1 = i + 1;
			}
			else if (pos2 == 0)
			{
				pos2 = i + 1;
			}
			else if (pos3 == 0)
			{
				pos3 = i + 1;
			}
			else if (pos4 == 0)
			{
				pos4 = i + 1;
			}
		}
	}

	char* temp;
	temp = (char*)malloc(100);

	// Recover the name of the member
	for (int i = 0; i < pos1; i++)
	{
		username[i] = str[i];
	}
	username[pos1 - 1] = '\0';

	// Recover the name of the member
	for (int i = pos1; i < pos2; i++)
	{
		password[i - pos1] = str[i];
	}
	password[pos2 - pos1 - 1] = '\0';

	// Recover the description of the member
	for (int i = pos2; i < pos3; i++)
	{
		description[i - pos2] = str[i];
	}
	description[pos3 - pos2 - 1] = '\0';

	// Recover the availability of the member
	for (int i = pos3; i < pos4; i++)
	{
		temp[i - pos3] = str[i];
	}
	temp[pos4 - pos3 - 1] = '\0';
	*is_admin = atoi(temp);

	// Recover the note of the member
	for (int i = pos4; i < length; i++)
	{
		temp[i - pos4] = str[i];
	}
	temp[length - pos4 - 1] = '\0';
	brain_id = atoi(temp);
}
void fDisplayMemberList(MEMBER_LIST* member_list)
{
	/*
	* We want the information to be displayed as the example below :
	+-----------------+-----------------+----------+-----------------+
	|       Name      |     Password    | Is Admin |  Current Brain  |
	+-----------------+-----------------+----------+-----------------+
	|                 |                 |		   |                 |
	|                 |                 |     	   |		         |
	+-----------------+-----------------+----------+-----------------+
	*/

	MEMBER* member;
	member = (MEMBER*)malloc(sizeof(*member));
	member = member_list->first;                      // Recover the first member in an object of the type member
	member = member->next->next;				     //  The third member on the list is the first that we want to display
	char* admin;
	admin = (char*)malloc(sizeof(*admin));

	printf("+-----------------+-----------------+-----------+-----------------+\n");
	printf("|       Name      |     Password    |  Is Admin |  Current Brain  | \n");
	printf("+-----------------+-----------------+-----------+-----------------+\n");
	while (member != NULL)
	{
		// We want to know if the member is admin or not
		if (member->is_admin == 1) // if member->is_admin == 0 then member is NOT_admin, else the member is admin
		{
			admin = (char*)"    ADMIN\0";
		}
		else
		{
			admin = (char*)"NOT_ADMIN\0";
		}
		printf("| %15s | %15s | %s |            %04d |\n", member->username, member->password, admin, member->brain_id);

		member = member->next;
	}
	printf("+-----------------+-----------------+-----------+-----------------+\n");
	printf("  number of members : %04d\n", member_list->size - 1);
}
void fAddMemberEnd(MEMBER_LIST* member_list, char* username, char* password, char* description, int is_admin, int brain_id)
{
	MEMBER* my_member;
	my_member = (MEMBER*)malloc(sizeof(*my_member));

	// Set the value of the different objects of the member
	my_member->username = username;
	my_member->password = password;
	my_member->desc = description;
	my_member->is_admin = is_admin;
	my_member->brain_id = brain_id;

	// Link the new member in the list
	my_member->previous = member_list->last;
	my_member->next = NULL;
	member_list->last->next = my_member;
	member_list->last = my_member;

	// Add one to the size of the list
	member_list->size += 1;
}
void fAddMember(MEMBER_LIST* member_list)
{
	int is_admin = 0;
	char* username;
	username = (char*)malloc(15);
	char* password;
	password = (char*)malloc(15);
	char* description;
	description = (char*)malloc(100);
	printf("Enter you username (15 characters max) : ");
	fgets(username, 15, stdin);
	username[strlen(username) - 1] = '\0';
	printf("Enter you password (15 characters max) : ");
	fgets(password, 15, stdin);
	password[strlen(password) - 1] = '\0';
	printf("Enter your description (100 characters max) : ");
	fgets(description, 50, stdin);
	description[strlen(description) - 1] = '\0';

	fAddMemberEnd(member_list, username, password, description, is_admin, NULL);
	fWriteMember(member_list);
}
void fWriteMember(MEMBER_LIST* member_list)
{
	FILE* member_file;
	member_file = (FILE*)malloc(sizeof(*member_file));
	char path[] = "member.txt";
	fopen_s(&member_file, path, "w+");

	MEMBER* my_member;
	my_member = (MEMBER*)malloc(sizeof(*my_member));
	my_member = member_list->first->next;

	// We want the member to be written as : username/password/description/is_admin/current_brain->id
	while (my_member != NULL)
	{
		fprintf(member_file, "%s/%s/%s/%d/%04d\n", my_member->username, my_member->password, my_member->desc, my_member->is_admin, my_member->brain_id);
		my_member = my_member->next;
	}

}

void fSignUp(MEMBER_LIST* member_list)
{
	MEMBER* new_member;
	new_member = (MEMBER*)malloc(sizeof(*new_member));


	//CREATES MEMBER PARAMETERS
	char* username;
	char* password;
	char* desc;
	username = (char*)malloc(sizeof(*username));
	password = (char*)malloc(sizeof(*password));
	desc = (char*)malloc(sizeof(*desc));
	new_member->next = NULL;

	//ASSIGN PARAMETERS TO NEW MEMBER
	getchar();
	printf("											Username: ");
	fgets(new_member->username, 20, stdin);
	new_member->username[strlen(username) - 1] = '\0';
	printf("											Password: ");
	fgets(new_member->password, 20, stdin);
	new_member->password[strlen(password) - 1] = '\0';
	printf("											Description: ");
	fgets(new_member->desc, 100, stdin);
	new_member->desc[strlen(desc) - 1] = '\0';

	//PLACES NEW MEMBER IN MEMBER LIST
	member_list->last->next = new_member;
	new_member->previous = member_list->last;
	new_member = member_list->last;

	printf("\n\n										Account created. Welcome, %s !\n", username);
	Sleep(3000);
	clear_screen(' ');
	fLogIn(member_list);
}
void fLogIn(MEMBER_LIST* member_list)
{
	//INITIALIZE LIST TO GO THROUGH
	MEMBER* current;
	MEMBER* pending;
	current = (MEMBER*)malloc(sizeof(*current));
	pending = (MEMBER*)malloc(sizeof(*pending));
	current = member_list->first;

	//USER PARAMETERS
	char* username;
	char* password;
	getchar();
	printf("\n												Username: ");
	username = (char*)malloc(sizeof(*username));
	fgets(username, 15, stdin);
	username[strlen(username) - 1] = '\0';
	printf("\n												Password: ");
	password = (char*)malloc(sizeof(*password));
	fgets(password, 15, stdin);
	password[strlen(password) - 1] = '\0';
	printf("\n									Press 9 to exit. Press any key to continue.\n");
	int n;
	scanf_s("%d", &n);

	//USER CHECK
	do
	{
		if (n == 9)
		{
			clear_screen(' ');
			fMenuDisplay(member_list);
		}
		if (strcmp(username, current->username) == 0)
		{
			if (strcmp(password, current->password) == 0)
			{
				//THE USER HAS BEEN RECOGNIZED
				printf("											Connected ! Welcome, %s.\n", username);
				Sleep(2000);

				fLoggedMenu(member_list, current);
			}
		}
	} while (current->next != NULL);

	//THE USER HAS NOT BEEN RECOGNIZED
	printf("									Incorrect username or password. Please try again.");
	Sleep(3000);
	fLogIn(member_list);
}
void fLoggedMenu(MEMBER_LIST* member_list, MEMBER* current)
{
	
}