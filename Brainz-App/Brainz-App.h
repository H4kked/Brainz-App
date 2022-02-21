#pragma once

typedef struct MEMBER MEMBER;
typedef struct MEMBER_LIST MEMBER_LIST;
typedef struct COMMENT COMMENT;
typedef struct COMMENT_LIST COMMENT_LIST;
typedef struct BRAIN BRAIN;
typedef struct BRAIN_LIST BRAIN_LIST;

void fMenuDisplay(MEMBER_LIST* list);
void clear_screen(char fill = ' ');
void fPrintLogo();
void fPrintLoading();
void fLogIn(MEMBER_LIST* list);
void fSignUp(MEMBER_LIST* list);
void fLoggedMenu();