#pragma once
#include "Brainz-App.h"

void fMainSaves();
void fGetBrains(BRAIN_LIST* brain_list);
void fSplitBrain(int* id, char* name, char* description, int* is_available, int* note, char* str);
void fDisplayBrainList(BRAIN_LIST* brain_list);
