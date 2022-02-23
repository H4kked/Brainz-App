#pragma once
#include "Brainz-Menu.h"

void fCommentStart(MASTER_COMMENT* master_list);
void fTestComment();
void fGetComment(MASTER_COMMENT* master_list);
void fSplitComment(int* id, char* date, char* description, float* note, char* member_name, char* str);
void fAddCommentList(MASTER_COMMENT* master_list, int brain_id, char* date, char* description, float note, char* member_name);
void fAddComment(MASTER_COMMENT* master_list, int brain_id, char* date, char* description, float note, char* member_name);
void fDisplayCommentList(MASTER_COMMENT* master_list);
