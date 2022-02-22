#pragma once

void fMemberSaves();
void fGetMember(MEMBER_LIST* member_list);
void fSplitMember(char* username, char* password, char* description, int* is_admin, int* brain_id, char* str);
void fDisplayMemberList(MEMBER_LIST* member_list);

void fLogIn(MEMBER_LIST* list);
void fSignUp(MEMBER_LIST* list);
void fLoggedMenu(MEMBER_LIST* list, MEMBER* member);