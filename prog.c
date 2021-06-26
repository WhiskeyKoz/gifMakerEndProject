/*********************************
* Class: MAGSHIMIM C2			 *
* openCV template      			 *
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "linkedList .h"
#include "loadAndSaveFiles.h"
#include <stdbool.h>

#include "view.h"
//#include <opencv2/core/core_c.h>
//#include <opencv2/highgui/highgui_c.h>
//#include <opencv2/imgcodecs/imgcodecs_c.h>


//gcc -o myProgram.exe  linkedList.c prog.c linkedList.h
#define FIRST_MENU_PRINT 1
#define ALL_RUN_MENU_PRINT 2

#define CREATE_PROJECT_CASE 0
#define LOAD_PROJECT_CASE 1
#define EXIT_MENU_CASE 0
#define ADD_FRAME_MENU_CASE 1
#define REMOVE_FRAME_MENU_CASE 2
#define CHANGE_FRAME_INDEX_MENU_CASE 3
#define CHANGE_FRAME_DURATION_MENU_CASE 4
#define CHANGE_ALL_FRAME_DURATION_MENU_CASE 5
#define PRINT_LIST_FRAMES_MENU_CASE 6
#define RUN_MOVIE_MENU_CASE 7
#define SAVE_MENU_CASE 8

//#define STR_LEN 50



int firstPrintAndGetUserChoice();
int printAndGetUserChoice();
int inputValidity(int userChoice);
int firstInputValidity(int userChoice);
void chengeDurationToAllMenuCase5(FrameNode* list);
void chengeDurationToframMenuCase4(FrameNode* list);
void menu(int firstUserChoice);
void myFgets(char str[], int size);
void printList(FrameNode* list);
FrameNode* removeFrameForMenuCase2(FrameNode* list, char nameToRemove[]);
FrameNode* chengeIndexFreamsMenuCase3(FrameNode* list);
int getDataForMenuCase3(char nameFream[]);

int main(void)
{
	int i, flag = 0;
    int firstUserChoice = 0;
    char project_path[STR_LEN];
    //printf("start!!!");
    firstUserChoice = firstPrintAndGetUserChoice();
    //userChoice = 0
    
	menu(firstUserChoice);
    
    printf("Leaks: %d\n", _CrtDumpMemoryLeaks());
    system("pause");
	return 0;
}
/*


*/
void menu(int firstUserChoice)
{
    
    int userChoice = 1, numOfPerson = 0, i = 0, lengthRcorsiveList, flag = 1;
    FrameNode* legenderyList = NULL;
    char nameToRemove[STR_LEN] = "";
    
    if (firstUserChoice == LOAD_PROJECT_CASE)
    {
        legenderyList = loadingProject();
    }
    else// only for debag
    {
        legenderyList = conectedDebagList();//debag list
    }
    while (flag == 1)
    {
        userChoice = printAndGetUserChoice();
        switch (userChoice)
        {
        case EXIT_MENU_CASE:
            if (legenderyList != NULL)
            {
                delatelist(legenderyList);
            }
            flag = 0;
            break;
        case ADD_FRAME_MENU_CASE:
            //legenderyList = conectedDebagList();//debag list
            legenderyList = conectedLinkedList(legenderyList);
            break;
        case REMOVE_FRAME_MENU_CASE:
            //printf("nave");
            printf("Enter the name of the frame you wish to erase\n");
            myFgets(nameToRemove, STR_LEN);
            legenderyList = removeFrameForMenuCase2(legenderyList, nameToRemove);
            break;
        case CHANGE_FRAME_INDEX_MENU_CASE:
            legenderyList = chengeIndexFreamsMenuCase3(legenderyList);
            break;
        case CHANGE_FRAME_DURATION_MENU_CASE:
            chengeDurationToframMenuCase4(legenderyList);
            break;
        case CHANGE_ALL_FRAME_DURATION_MENU_CASE:
            chengeDurationToAllMenuCase5(legenderyList);
            break;
        case PRINT_LIST_FRAMES_MENU_CASE:
            printf("\t\t\t Name\t\t\t Duration \t\t\t Path\n");            
            printList(legenderyList);
            break;
        case RUN_MOVIE_MENU_CASE:
            // printf("call to play");
            play(legenderyList);
            break;

        case SAVE_MENU_CASE:
            getDataForSave(legenderyList);
            break;
        }
    }
}

FrameNode* removeFrameForMenuCase2(FrameNode* list, char nameToRemove[])
{
    FrameNode* curr = list;
    FrameNode* save = NULL;
    FrameNode* first = list;
    if (curr == NULL)
    {

        return 1;
    }
    if (checkNamesAreSame(curr->frame->name, nameToRemove))
    {
        first = curr->next;
        dleateOnlyFrame(curr);
        return first;
    }
    else
    {
        while (curr)//
        {
            //checkNamesAreSame()

            if (curr->next != NULL && checkNamesAreSame(curr->next->frame->name, nameToRemove))
            {
                save = curr->next;
                curr->next = curr->next->next;
                dleateOnlyFrame(save);
                return first;
            }
            curr = curr->next;
        }
        printf("sorry cant find the name of the frame to remove\n");
        return first;
    }

}

int getDataForMenuCase3(char nameFream[])
{
    int indexMoveFream = 0;
    printf("Enter the name of the frame: \n");
    myFgets(nameFream, STR_LEN);
    printf("Enter the new index in the movie you wish to place the fream\n");
    while (true)
    {
        
        scanf("%d", &indexMoveFream);
        getchar();
        if (indexMoveFream <= 0)
        {
            printf("invald inpout do again(good inpout is up from 1)\n");
        }
        else
        {
            break;
        }
    }

    return indexMoveFream;
}
FrameNode* chengeIndexFreamsMenuCase3(FrameNode* list)
{
    FrameNode* curr = list;
    FrameNode* save = NULL;
    FrameNode* first = list;
    FrameNode* frameToMove  = NULL;
    FrameNode* frameIndex  = NULL;
    int indexMoveFream =  0, flagFirst = 0, index = 1, flag = 0, listSize =0;

    char nameFream[STR_LEN] = "";
    if (list == NULL)
    {
        printf("the list is empaty.\n");
        return list;
    }
    indexMoveFream = getDataForMenuCase3(nameFream);
    listSize = listLength(list);
    
    if (indexMoveFream > listSize)// if the user index is up from length list
    {
        printf("the input index big of the length of the list");
        return list;
    }
    if (checkNamesAreSame(curr->frame->name, nameFream))
    {
        flagFirst = 1;
        frameToMove = curr;
        flag += 1;
    }
    while (curr)
    {
        if (flagFirst == 0 && curr->next != NULL && checkNamesAreSame(curr->next->frame->name, nameFream))
        {
            
            frameToMove = curr;
            flag += 1;
            //return first;
        }
        // 1->2->3->4->5
        if (index == indexMoveFream)
        {
            frameIndex = curr;
            flag += 1;
        }
        if (flag == 2)
        {
            if (flagFirst != 1 && frameToMove->next == frameIndex)
            {
                return list;
            }
            else if (flagFirst)
            {
                if (frameToMove == frameIndex)
                {
                    return list;
                }
                save = frameIndex->next;  
                first = frameToMove->next;
                frameIndex->next = frameToMove;
                frameToMove->next = save;
            }
            else if (indexMoveFream == 1)// if index user == 1 (to the first at the list)
            {
                //printList(frameToMove);

                save = frameToMove->next;//3
                frameToMove->next = frameToMove->next->next;//2->4
                save->next = frameIndex;//3->1
                first = save;//updete list
            }
            else
            {
                save = frameToMove->next;//2
                frameToMove->next = frameToMove->next->next;//1->3
                save->next = frameIndex->next;//2->5
                frameIndex->next = save;//1->3->4->2->5
                //printList
            }
            break;
        }
        curr = curr->next;
        index++;   
    }
    if (flag != 2)
    {
        printf("sorry cant find the name of the frame\n");
    }
    return first;
}
/*
get name of frame from the user 
and number duration from the user 
and chenge duration of the frame name.
*/
void chengeDurationToframMenuCase4(FrameNode* list)
{
    FrameNode* curr = list;
    unsigned int duration;
    char nameFream[STR_LEN] = "";
    printf("Enter the name of the frame: \n");
    myFgets(nameFream, STR_LEN);
    checkNamesAreSame(curr->frame->name, nameFream);
    printf("Enter the duration this name frame: \n");
    duration = durationScanf();

    while (curr)
    {
        if (checkNamesAreSame(curr->frame->name, nameFream))
        {
            curr->frame->duration = duration;
            break;
        }
        curr = curr->next;
    }
}


/*
get number from the user 
and chenge duration in the all frames.
*/
void chengeDurationToAllMenuCase5(FrameNode* list)
{
    FrameNode* curr = list;
    
    printf("Enter the duration for all frames: \n");
    unsigned int duration = durationScanf();
    while (curr)
    {
        curr->frame->duration = duration;
        curr = curr->next;
    }
}

/*

Function was check input validity
*/
int firstInputValidity(int userChoice)
{
    return (userChoice == CREATE_PROJECT_CASE || userChoice == LOAD_PROJECT_CASE);
}
int inputValidity(int userChoice)
{
    return (userChoice >= EXIT_MENU_CASE && userChoice <= SAVE_MENU_CASE);
}
 

/*
func for print menu and
get inpot of user choice
*/
int firstPrintAndGetUserChoice()
{
    int userChoice = 0;
    int num = 0;

    while (true)
    {
        printf("Welcome to Magshimim Movie Maker what wohuld you like to do?\n");
        printf(" [0] Create a new project\n");
        printf(" [1] Load existing project\n");
        scanf("%d", &userChoice);
        //getchar();
        if (firstInputValidity(userChoice))
        {
            break;
        }
        else
        {
            getchar();
            printf("Worng input try again\n");
        }
    
    }
    return userChoice;
}
/*
func for print menu and
get inpot of user choice
*/
int printAndGetUserChoice()
{
    int userChoice = 0;
    
    while (true)
    {
        printf(" [0] Exit\n");
        printf(" [1] Add new Fram\n");
        printf(" [2] Remove a Fram\n");
        printf(" [3] Change frame index\n");
        printf(" [4] Change frame duration\n");
        printf(" [5] Change duration of all frames\n");
        printf(" [6] List frames\n");
        printf(" [7] Play movie\n");
        printf(" [8] Save project\n");
        scanf("%d", &userChoice);
        getchar();
        if (inputValidity(userChoice))
        {
            break;
        }
        else
        {
            printf("Worng input try again\n");
        }
    }
    return userChoice;
}



//************************************
// Method:    printList
// Returns:   void
// Description: prints list recursively
// Parameter: IntNode * list
//************************************
void printList(FrameNode* list)
{
    FrameNode* curr = list;
    while (curr) // when curr == NULL, that is the end of the list, and loop will end (NULL is false)
    {
        printf("\t\t\t %s\t\t\t %d ms \t\t\t %s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
        curr = curr->next;
    }
    printf("\n");
    /*
    if (list)
    {
        printf("\t\t\t %s\t\t\t %d ms \t\t\t %s\n", list->frame->name, list->frame->duration, list->frame->path);
        printList(list->next);
    }
    else
    {
        printf("\n");
    }*/
}
