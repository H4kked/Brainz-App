#pragma once
#include "Brainz-App.h"

void fMainSaves();
void fGetBrains(BRAIN_LIST* brain_list);
void fAddEnd(BRAIN_LIST* brain_list, int id, char* name, char* description, int is_available, float note);
void fSplitBrain(int* id, char* name, char* description, int* is_available, float* note, char* str);
void fDisplayBrainList(BRAIN_LIST* brain_list);
