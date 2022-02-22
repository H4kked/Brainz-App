#pragma once
#include "Brainz-Menu.h"

void fMemberSaves();
void fGetMember(MEMBER_LIST* member_list);
void fSplitMember(char* username, char* password, char* description, int* is_admin, int brain_id, char* str);
void fDisplayMemberList(MEMBER_LIST* member_list);
void fAddMemberEnd(MEMBER_LIST* member_list, char* username, char* password, char* description, int is_admin, int brain_id);
void fWriteMember(MEMBER_LIST* member_list);
void fAddMember(MEMBER_LIST* member_list);

void fLogIn(MEMBER_LIST* list);
void fSignUp(MEMBER_LIST* list);
void fLoggedMenu(MEMBER_LIST* list, MEMBER* member);