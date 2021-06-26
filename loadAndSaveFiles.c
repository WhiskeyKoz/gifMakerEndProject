#define _CRT_SECURE_NO_WARNINGS
#include "loadAndSaveFiles.h"
#define READ_FILE "r"
#define WRIHT_FILE "w"

#define FIND_NAME 1
#define FIND_PATH 2
#define FIND_DURATION 3
#define SPLIT_FREAM_SYMBLE ","[0]// if I was not do [0] the if is not work becosue "," is a string 
#define NEW_FREAME "\n"[0]// if I was not do [0] the if is not work becosue "\n" is a string 

FrameNode* loadingProject()
{
	FILE* theProject = NULL;
	char project_path[STR_LEN] = "";
	printf("Enter the path of the project? <including project name>:\n");
	getchar();
	myFgets(project_path, STR_LEN);
	
	theProject = fopen(project_path, READ_FILE);
	if (theProject == NULL)
	{
		printf("the path file wrong plaes create new project.\n");
		return;
	}
	return readFileAndCreateTheList(theProject);
}
/*
	while explaition:
	flag = 1: find the name.
	flag = 2: find the path.
	flag = 3: find the duration.
*/
FrameNode* readFileAndCreateTheList(FILE* theProject)
{
	char name[STR_LEN] = "";
	char path[STR_LEN] = "";
	char durationStr[10] = "";
	unsigned int duration = 0;
	char ch = 0;
	int i = 0, flag = 1, flagFirst = 1, freamsLength = 1;
	FrameNode* add = NULL;
	FrameNode* curr = NULL;
	FrameNode* listFreams = NULL;
	while ((ch = (char)fgetc(theProject)) != EOF)
	{
		if (ch == NEW_FREAME)
		{	
			duration = atoi(durationStr);
			
			if (flagFirst == 1)
			{
				listFreams = buildFream(name, path, duration);
				curr = listFreams;
			}
			else
			{
				add = buildFream(name, path, duration);
				curr->next = add;
				curr = curr->next;
			}
			flag = 1;
			flagFirst++;
			//Now need to reset the variables becosue new freams
			memset(name, 0, STR_LEN);
			memset(path, 0, STR_LEN);
			memset(durationStr, 0, 10);
		}
		else if (ch == SPLIT_FREAM_SYMBLE)
		{
			flag++;
		}
		else if (flag == 1)
		{
			strncat(name, &ch, 1);
			//printf("len name: %d\n", strlen(name));
		}
		else if (flag == 2)
		{
			strncat(durationStr, &ch, 1);
		}
		else if (flag == 3)
		{
			strncat(path, &ch, 1);
		}
		//printf("%c", ch);
	}
	fclose(theProject);
	//FrameNode* listFreams = buildFream(name, path, duration);

	return listFreams;
}
void getDataForSave(FrameNode* listToSave)
{	
	FILE* theProject = NULL;
	char project_path[STR_LEN] = "";
	if (listToSave == NULL)
	{
		printf("Noting to save, add frame to save\n");
		return;
	}
	printf("Where to save the project? enter a full path and file name\n");
	while (true)
	{
		myFgets(project_path, STR_LEN);
		theProject = fopen(project_path, WRIHT_FILE);
		if (theProject == NULL)
		{
			printf("the path file wrong try some else.\n");
		}
		else
		{
			break;
		}
	}
	saveListFrames(listToSave, theProject);
	fclose(theProject);
}
void saveListFrames(FrameNode* listToSave, FILE* theProject)
{
	FrameNode* curr = listToSave;
	char* dainamicPath = NULL;
	char* dainamicName = NULL;
	int pathStrLen = 0;
	while (curr)
	{
		char durtionStr[10] = "";
		pathStrLen = strlen(curr->frame->name);
		dainamicName = (char*)malloc(sizeof(char) * (pathStrLen + 1));
		strncpy(dainamicName, curr->frame->name, pathStrLen + 1);
		pathStrLen = strlen(curr->frame->path);
		dainamicPath = (char*)malloc(sizeof(char) * pathStrLen + 1);
		strncpy(dainamicPath, curr->frame->path, pathStrLen + 1);
		sprintf(durtionStr, "%u", curr->frame->duration);
		fprintf(theProject, "%s,%s,%s\n", dainamicName, durtionStr, dainamicPath);
		free(dainamicName);
		free(dainamicPath);
		curr = curr->next;
	}

}
