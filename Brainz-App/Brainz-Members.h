#pragma once
#include "Brainz-Menu.h"

void fMemberStart(MEMBER_LIST* member_list);
void fGetMember(MEMBER_LIST* member_list);
void fSplitMember(char* username, char* password, char* description, int* is_admin, int* brain_id, char* str);
void fDisplayMemberList(MEMBER_LIST* member_list);
void fAddMemberEnd(MEMBER_LIST* member_list, char* username, char* password, char* description, int is_admin, int brain_id);
void fWriteMember(MEMBER_LIST* member_list);
void fAddMember(MEMBER_LIST* member_list);
void fDelMember(MEMBER_LIST* member_list, BRAIN_LIST* brain_list);
void fUpgradeMember(MEMBER_LIST* member_list);
void fEditDescription(MEMBER_LIST* member_list);


void fLogIn(MEMBER_LIST* member_list, BRAIN_LIST* brain_list, MASTER_COMMENT* master_list);
void fSignUp(MEMBER_LIST* member_list, BRAIN_LIST* brain_list, MASTER_COMMENT* master_list);
void fLoggedMenu(MEMBER_LIST* list, BRAIN_LIST* brain_list, MEMBER* member);

void fMemberManagement(MEMBER_LIST* member_list, BRAIN_LIST* brain_list);