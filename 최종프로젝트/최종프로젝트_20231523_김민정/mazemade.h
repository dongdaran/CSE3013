#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>

typedef struct _MAZE {//room의 갯수만을 고려한 배열과 그에 대한 정보(너비, 높이)를 저장하는 구조체
	int width;
	int height;
	int** maze_group;
} MAZE;

typedef struct _DRAWMAZE {//room의 갯수와 '-,+,|, '을 고려한 배열과 그에 대한 정보(너비, 높이)를 저장하는 구조체
	int all_width;
	int all_height;
	int** maze_info;
} DRAWMAZE;

MAZE maze;
DRAWMAZE result;
int group_index = 1;//room의 집합을 나타내는 인덱스
int height_index = 0;//높이의 위치를 나타내는 인덱스

void Free_Memeory();//result.maz 제작하고 이후 모든 동적메모리를 해제하는 함수
void mazemade();//result.maz를 제작하는 총체적함수
void Init_Maze();//처음 eller알고리즘을 실행할 수 있게 미로의 맨 윗줄까지 설정하는 함수
void upload_maze_pic();//생성된 파일을 result.maz에 저장하는 함수
void group_ornot();//인접한 room과 같은 집합에 포함시킬지 말지 결정
void made_sero_group();//세로 방향으로 그룹을 같은 그룹에 포함시킬지 말지 결정하는 함수
void last_group_ornot();//마지막줄은 상관없이 다른 집합의 room이라면 무조건 허무는 함수

#endif