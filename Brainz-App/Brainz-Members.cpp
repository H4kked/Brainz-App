#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <Windows.h>
#include "Brainz-Brains.h"
#include "Brainz-Menu.h"
#include "Brainz-Members.h"

void fMemberStart(MEMBER_LIST* member_list)
{
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
}
void fGetMember(MEMBER_LIST* member_list)
{
	printf("COUCOU je suis la \n");
	FILE* member_file;
	member_file = (FILE*)malloc(sizeof(FILE*));
	char path[] = "member.txt";
	fopen_s(&member_file, path, "r+");
	char* str;
	str = (char*)malloc(200);
	getchar();

	while (fgets(str, 200, member_file) != NULL)
	{
		printf("%s\n", str);
		int id = 0;
		char* username;
		char* password;
		char* description;
		int is_admin = 1;
		int brain_id = 0;
		password = (char*)malloc(20);
		username = (char*)malloc(20);
		description = (char*)malloc(180);
		fSplitMember(username, password, description, &is_admin, &brain_id, str);
		fAddMemberEnd(member_list, username, password, description, is_admin, brain_id);

		}
	fclose(member_file);
}
void fSplitMember(char* username, char* password, char* description, int* is_admin, int* brain_id, char* str)
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
	temp = (char*)malloc(200);

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

	// Recover the brain_id of the member
	for (int i = pos4; i < length; i++)
	{
		temp[i - pos4] = str[i];
	}
	temp[length - pos4 - 1] = '\0';
	*brain_id = atoi(temp);

	printf("%s %s %s %d %d\n", username, password, description, *is_admin, *brain_id);
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

	system("PAUSE");
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
	username = (char*)malloc(20);
	char* password;
	password = (char*)malloc(20);
	char* description;
	description = (char*)malloc(101);
	printf("Enter you username (15 characters max) : ");
	getchar();
	fgets(username, 15, stdin);
	username[strlen(username) - 1] = '\0';
	printf("Enter you password (15 characters max) : ");
	fgets(password, 15, stdin);
	password[strlen(password) - 1] = '\0';
	printf("Enter your description (100 characters max) : ");
	fgets(description, 100, stdin);
	description[strlen(description) - 1] = '\0';

	MEMBER* check_member;
	check_member = (MEMBER*)malloc(sizeof(*check_member));
	check_member = member_list->first;

	while (strcmp(check_member->username, username) != 0)
	{
		check_member = check_member->next;
		if (check_member == NULL)
		{
			break;
		}
	}

	if (check_member != NULL)
	{
		printf("This username is already taken, please choose another\n");
		fAddMember(member_list);
	}
	else {
		fAddMemberEnd(member_list, username, password, description, is_admin, NULL);
		fWriteMember(member_list);
	}
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
	fclose(member_file);
	fMemberStart(member_list);
}
void fDelMember(MEMBER_LIST* member_list, BRAIN_LIST* brain_list)
{
	MEMBER* del_member;
	del_member = (MEMBER*)malloc(sizeof(*del_member));
	del_member = member_list->first;

	char* del_username;
	del_username = (char*)malloc(15);
	printf("Enter the name of the member you want to delete : ");
	fgets(del_username, 15, stdin);
	del_username[strlen(del_username) - 1] = '\0';

	while (strcmp(del_member->username, del_username) != 0 && del_member != NULL)
	{
		del_member = del_member->next;
		if (del_member == NULL)
		{
			break;
		}
	}

	if (del_member == NULL)
	{
		printf("There is no member with this username.\n\n");
	}
	else
	{
		printf("\n");

		if (strcmp(del_member->username, member_list->last->username) == 0)
		{
			member_list->last = del_member->previous;
			del_member->previous->next = NULL;
		}
		else
		{
			fReturnBrain(member_list, brain_list, member_list->logged);
			del_member->previous->next = del_member->next;
			del_member->next->previous = del_member->previous;
			del_member = del_member->next;
			while (del_member != NULL)
			{
				del_member = del_member->next;
			}
		}
		member_list->size -= 1;
		fWriteMember(member_list);
	}
}
void fUpgradeMember(MEMBER_LIST* member_list)
{
	MEMBER* up_member;
	up_member = (MEMBER*)malloc(sizeof(*up_member));
	up_member = member_list->first;

	char* up_username;
	up_username = (char*)malloc(15);
	printf("Enter the name of the member you want to upgrade : ");
	fgets(up_username, 15, stdin);
	up_username[strlen(up_username) - 1] = '\0';

	while (strcmp(up_member->username, up_username) != 0 && up_member != NULL)
	{
		up_member = up_member->next;
		if (up_member == NULL)
		{
			break;
		}
	}
	if (up_member == NULL)
	{
		printf("There is no member with this username.\n\n");
		system("PAUSE");
		fUpgradeMember(member_list);
	}
	else
	{
		up_member->is_admin = 1;
		printf("Member upgraded.");
		system("PAUSE");

	}
	fWriteMember(member_list);
}
void fEditDescription(MEMBER_LIST* member_list)
{
	MEMBER* member;
	member = (MEMBER*)malloc(sizeof(*member));
	char* description;
	description = (char*)malloc(165);

	member = member_list->logged;
	printf("Previous description : \n%160s\n", member->desc);

	printf("Enter your new description : \n");
	fgets(description, 160, stdin);
	description[strlen(description) - 1] = '\0';

	member->desc = description;
	fWriteMember(member_list);
}

void fSignUp(MEMBER_LIST* member_list, BRAIN_LIST* brain_list)
{
	fAddMember(member_list);

	printf("\n\n										Account created. Welcome !\n");
	Sleep(3000);
	clear_screen(' ');
	fLogIn(member_list, brain_list);
}
void fLogIn(MEMBER_LIST* member_list, BRAIN_LIST* brain_list)
{
	//INITIALIZE LIST TO GO THROUGH
	MEMBER* current_member;
	current_member = (MEMBER*)malloc(sizeof(*current_member));
	current_member = member_list->first->next;

	//USER PARAMETERS
	char* username;
	char* password;
	username = (char*)malloc(sizeof(*username));
	password = (char*)malloc(sizeof(*password));

	clear_screen(' ');
	fPrintLogo();
	char c;
	scanf_s("%c", &c);

	printf("\n												Username: ");
	fgets(username, 15, stdin);
	username[strlen(username) - 1] = '\0';

	printf("\n												Password: ");
	fgets(password, 15, stdin);
	password[strlen(password) - 1] = '\0';

	printf("\n											Press 9 to exit. Enter 1 to continue.\n");
	int n, is_recognized = 0;
	scanf_s("%d", &n);

	if (n == 9)
	{
		clear_screen(' ');
		fMenuDisplay(member_list, brain_list);
	}
	else
	{
		//USER CHECK
		while (current_member != NULL)
		{
			printf("%s %s\n", current_member->username, current_member->password);
			printf("%s\n", current_member->next->username);
			if (strcmp(username, current_member->username) == 0)
			{
				if (strcmp(password, current_member->password) == 0)
				{
					//THE USER HAS BEEN RECOGNIZED
					member_list->logged = current_member;

					is_recognized = 1;
					printf("											    Connected ! Welcome, %s.\n", username);
					Sleep(3000);

					fLoggedMenu(member_list, brain_list, current_member);
				}
			}
			printf("next\n");
			current_member = current_member->next;
		}
	}
	printf("not recognized\n");
	if (is_recognized == 0)
	{
		//THE USER HAS NOT BEEN RECOGNIZED
		printf("									Incorrect username or password. Please try again.");
		Sleep(3000);
		free(current_member);
		fLogIn(member_list, brain_list);
	}
}
void fLoggedMenu(MEMBER_LIST* member_list, BRAIN_LIST* brain_list, MEMBER* current_member)
{
	if (current_member->is_admin == 1)
	{
		fAdminScreen(member_list->logged, brain_list, member_list);
		exit(0);
	}
	else if (current_member->is_admin == 0)
	{
		fUserScreen(current_member, brain_list, member_list);
		exit(0);
	}
	else
	{
		printf("A problem occured. Please contact an administrator for help.");
		Sleep(5000);
		exit(0);
	}
}

void fMemberManagement(MEMBER_LIST* member_list, BRAIN_LIST* brain_list)
{
	clear_screen(' ');
	Sleep(50);
	fPrintLogo();

	printf("										1 - ADD A MEMBER\n");
	printf("										2 - DELETE A MEMBER\n");
	printf("										3 - UPGRADE A MEMBER\n");
	printf("										4 - SEE MEMBER LIST\n");
	printf("\n										9 - EXIT\n");
	printf("\n										Entry : ");

	int choice = 0;
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
		clear_screen(' ');
		fPrintLogo();
		fAddMember(member_list);
		break;
	case 2:
		clear_screen(' ');
		fPrintLogo();
		fDelMember(member_list, brain_list);
		break;
	case 3:
		clear_screen(' ');
		fPrintLogo();
		fUpgradeMember(member_list);
		break;
	case 4:
		clear_screen(' ');
		fPrintLogo();
		fDisplayMemberList(member_list);
		break;
	case 9:
		fAdminScreen(member_list->logged, brain_list, member_list);
		break;
	}
	fAdminScreen(member_list->logged, brain_list, member_list);
}