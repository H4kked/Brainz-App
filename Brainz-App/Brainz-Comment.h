#pragma once
#include "Brainz-Menu.h"

void fCommentStart(MASTER_COMMENT* master_list);
void fTestComment();
void fGetComment(MASTER_COMMENT* master_list);
void fSplitComment(int* id, char* date, char* description, float* note, char* member_name, char* str);
void fAddCommentList(MASTER_COMMENT* master_list, int brain_id, char* date, char* description, float note, char* member_name);
void fAddComment(MASTER_COMMENT* master_list, int brain_id, char* date, char* description, float note, char* member_name);
void fDisplayCommentList(MASTER_COMMENT* master_list);
void fDisplayComment(MASTER_COMMENT* master_list, int brain_id);
void fPostComment(MASTER_COMMENT* master_list, MEMBER_LIST* member_list, int brain_id);
void fWriteComment(MASTER_COMMENT* master_list);
void fDelComment(MASTER_COMMENT* master_list, int brain_id);

