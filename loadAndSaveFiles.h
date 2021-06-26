#pragma once

#ifndef LOADANDSAVEFILES
#define LOADANDSAVEFILES

#include <stdbool.h>
#include <stdio.h>

#include "linkedList .h"
FrameNode* loadingProject();
FrameNode* readFileAndCreateTheList(FILE* theProject);
void getDataForSave(FrameNode* listToSave);
void saveListFrames(FrameNode* listToSave, FILE* theProject);
#endif
