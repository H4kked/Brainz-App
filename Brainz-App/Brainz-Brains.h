#pragma once
#include "Brainz-Menu.h"
#include "Brainz-Members.h"

void fMainSaves();
void fGetBrains(BRAIN_LIST* brain_list);
void fAddEnd(BRAIN_LIST* brain_list, int id, char* name, char* description, int is_available, float note);
void fSplitBrain(int* id, char* name, char* description, int* is_available, float* note, char* str);
void fDisplayBrainList(BRAIN_LIST* brain_list);
void fAddBrain(BRAIN_LIST* brain_list);
void fWriteBrain(BRAIN_LIST* brain_list);
void fDelBrain(BRAIN_LIST* brain_list);
void fSetAvailability(BRAIN_LIST* brain_list, char* ch_name);
void fBrainStart(BRAIN_LIST* brain_list);
void fBorrowBrain(MEMBER_LIST* member_list, BRAIN_LIST* brain_list, MEMBER* current_member);
