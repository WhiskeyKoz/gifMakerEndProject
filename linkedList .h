#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE

// Frame struct
typedef struct Frame
{

	char* name;
	unsigned int duration;
	char* path;
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;
#include <stdlib.h>
#include <string.h>
#define STR_LEN 300
unsigned int durationScanf();
FrameNode* buildFream(char name[], char path[], unsigned int duration);
FrameNode* conectedLinkedList(FrameNode* theFrameList);
FrameNode* getDetailsAndCreate(FrameNode* listFreams);
void getAndCheckNames(FrameNode* listFreams, char nameToCheck[]);
int checkFreamExist(char pathFile[]);
int checkNamesAreSame(char name1[], char name2[]);
void updateToEnd(FrameNode* theFirstOfTheList, FrameNode* someToadd);
void myFgets(char str[], int size);
void dleateOnlyFrame(FrameNode* freeFrame);
void delatelist(FrameNode* head);
int listLength(FrameNode* curr);
FrameNode* conectedDebagList();//only for debag


#endif
