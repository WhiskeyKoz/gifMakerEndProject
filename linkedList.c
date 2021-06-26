#define _CRT_SECURE_NO_WARNINGS
#include "linkedList .h"
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#define STR_LEN 300
#define STR_LEN_NAMES 50
//#include "D:/linkedList .h"
//#include "view.h"


/*
Receives a linked list and the structure.
function adds the structure to
the linked list at the end.
*/
void updateToEnd(FrameNode* theFirstOfTheList, FrameNode* someToadd)
{
    FrameNode* curr = theFirstOfTheList;
    while (curr)
    {
        if (curr->next == NULL)
        {
            curr->next = someToadd;
            break;
        }
        curr = curr->next;
    }
    
}
/*
Function will conecting link list
*/
FrameNode* conectedLinkedList(FrameNode* theFrameList)
{
    int i = 1;
    FrameNode* firstForReturn = theFrameList;
    FrameNode* add = NULL;

    if (theFrameList == NULL)
    {
        firstForReturn = getDetailsAndCreate(theFrameList);
    }
    else
    {
        FrameNode* add = getDetailsAndCreate(theFrameList);
        updateToEnd(firstForReturn, add);
    }
    return firstForReturn;
}

/*
Function will get a details for sturct
and call to buildFream to create
*/
FrameNode* getDetailsAndCreate(FrameNode* listFreams)
{
    int pathStrLen = 0;
    char name[STR_LEN] = "";
    char path[STR_LEN] = "";
    printf("*** Creating new frame ***\n");
    printf("Please insert frame path:\n");
    myFgets(path, STR_LEN);//!!!!!! nedd to check if file open
    checkFreamExist(path);
    getAndCheckNames(listFreams, name);  
    printf("Please insert frame duration<in miliseconds>: ");
    unsigned int duration = durationScanf();

    return buildFream(name, path, duration);
}
/*
get data to put in the struct
*/
FrameNode* buildFream(char name[], char path[], unsigned int duration)
{
    FrameNode* theFrame = NULL;
 
    char* dainamicPath = NULL;
    char* dainamicName = NULL;
    int pathStrLen = 0;
    theFrame = (FrameNode*)malloc(sizeof(FrameNode));
    theFrame->frame = (Frame*)malloc(sizeof(Frame));
    pathStrLen = strlen(path);
    dainamicPath = (char*)malloc(sizeof(char) * pathStrLen + 1);
    strncpy(dainamicPath, path, pathStrLen + 1);
    pathStrLen = strlen(name);
    dainamicName = (char*)malloc(sizeof(char) * (pathStrLen + 1));
    strncpy(dainamicName, name, pathStrLen + 1);
    theFrame->frame->name = dainamicName;
    theFrame->frame->path = dainamicPath;
    theFrame->frame->duration = duration;
    theFrame->next = NULL;

    return theFrame;
}
/*
check if the name was apper
*/
void getAndCheckNames(FrameNode* listFreams, char nameToCheck[])
{
    //char nameToCheck[STR_LEN] = "";
    FrameNode* curr = NULL;
    int flag = 0, pathStrLen;
    //printf("Enter the name of the frame\n");
    printf("Please choose a name for that frame:\n");
    myFgets(nameToCheck, STR_LEN);//!!!!!! nedd to check if file open
    curr = listFreams;
    if (curr == NULL)
    {
        flag = 1;
    }
    else
    {
        while (curr)
        {
            if (checkNamesAreSame(curr->frame->name, nameToCheck))
            {
                printf("The name is already taken, please enter another name\n");
                myFgets(nameToCheck, STR_LEN);//!!!!!! nedd to check if file open

                curr = listFreams;
            }
            else
            {
                curr = curr->next;
            }
        }
    }
    
    //free(dainamicName);
    
}
/*
check if path file of 
frame is exist 
*/

int checkFreamExist(char pathFile[])
{
    FILE* checkFile = fopen(pathFile, "r");
    if (checkFile == NULL)
    {
        printf("Error opening file");
        fclose(checkFile);
        return 1;
    }

    return checkFile != NULL;
}
/*
free the frame
*/
void dleateOnlyFrame(FrameNode* freeFrame)
{
    free(freeFrame->frame->name);
    free(freeFrame->frame->path);
    free(freeFrame->frame);
    free(freeFrame);
}
/*
free the all list of frames
*/
void delatelist(FrameNode* head)
{
    FrameNode* curr = head;
    FrameNode* save = NULL;
    while (curr) // when curr == NULL, that is the end of the list, and loop will end (NULL is false)
    {
        save = curr->next;
        dleateOnlyFrame(curr);
        curr = save;

    }
}

/*
Gets two names and checks if they are equal
*/
int checkNamesAreSame(char name1[], char name2[])
{
    return strcmp(name1, name2) == 0;
}
/*
scanf duration function
*/
unsigned int durationScanf()
{
    unsigned int duration = 0;
    scanf("%u", &duration);
    getchar();
    return duration;
}
/*
recorsive function
was get the length of
the link list
*/
int listLength(FrameNode* curr)
{
    int ans = 0;
    if (curr)
    {
        ans = 1 + listLength(curr->next);
    }
    return ans;

}
/*
func for inpot str
*/
void myFgets(char str[], int size)
{
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = 0;
}

FrameNode* conectedDebagList()
{
    FrameNode* first = NULL;
    FrameNode* next1 = NULL;
    FrameNode* next2 = NULL;
    FrameNode* next3 = NULL;
    FrameNode* next4 = NULL;
    FrameNode* next5 = NULL;
    first = buildFream("nave1", "E:\\magshimim\\C1_Introduction_to_Programming\\semester2\\THE_END_PROJECT\\untilWhennProjects\\superman\\1.png",  100);
    next1 = buildFream("nave2", "E:\\magshimim\\C1_Introduction_to_Programming\\semester2\\THE_END_PROJECT\\untilWhennProjects\\superman\\2.png",  200);
    next2 = buildFream("nave3", "E:\\magshimim\\C1_Introduction_to_Programming\\semester2\\THE_END_PROJECT\\untilWhennProjects\\superman\\3.png",  300);
    next3 = buildFream("nave4", "E:\\magshimim\\C1_Introduction_to_Programming\\semester2\\THE_END_PROJECT\\untilWhennProjects\\superman\\4.png",  400);
    next4 = buildFream("nave5", "E:\\magshimim\\C1_Introduction_to_Programming\\semester2\\THE_END_PROJECT\\untilWhennProjects\\superman\\5.png",  500);
    next5 = buildFream( "nave6", "E:\\magshimim\\C1_Introduction_to_Programming\\semester2\\THE_END_PROJECT\\untilWhennProjects\\superman\\6.png", 600);
    first->next = next1;
    next1->next = next2;
    next2->next = next3;
    next3->next = next4;
    next4->next = next5;
    next1->next = next2;
    return first;
}
