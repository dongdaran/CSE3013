#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct _MAZE{
int width;
int height;
int **maze_group;
} MAZE;

typedef struct _DRAWMAZE{
int all_width;
int all_height;
int **maze_info;
} DRAWMAZE;

MAZE maze;
DRAWMAZE result;
int group_index=1;
int height_index=0;

void Init_Maze();
void upload_maze_pic();
void group_ornot();
void made_sero_group();
void last_group_ornot();

#endif