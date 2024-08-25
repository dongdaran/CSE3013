#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>

typedef struct _MAZE {//room�� �������� ����� �迭�� �׿� ���� ����(�ʺ�, ����)�� �����ϴ� ����ü
	int width;
	int height;
	int** maze_group;
} MAZE;

typedef struct _DRAWMAZE {//room�� ������ '-,+,|, '�� ����� �迭�� �׿� ���� ����(�ʺ�, ����)�� �����ϴ� ����ü
	int all_width;
	int all_height;
	int** maze_info;
} DRAWMAZE;

MAZE maze;
DRAWMAZE result;
int group_index = 1;//room�� ������ ��Ÿ���� �ε���
int height_index = 0;//������ ��ġ�� ��Ÿ���� �ε���

void Free_Memeory();//result.maz �����ϰ� ���� ��� �����޸𸮸� �����ϴ� �Լ�
void mazemade();//result.maz�� �����ϴ� ��ü���Լ�
void Init_Maze();//ó�� eller�˰����� ������ �� �ְ� �̷��� �� ���ٱ��� �����ϴ� �Լ�
void upload_maze_pic();//������ ������ result.maz�� �����ϴ� �Լ�
void group_ornot();//������ room�� ���� ���տ� ���Խ�ų�� ���� ����
void made_sero_group();//���� �������� �׷��� ���� �׷쿡 ���Խ�ų�� ���� �����ϴ� �Լ�
void last_group_ornot();//���������� ������� �ٸ� ������ room�̶�� ������ �㹫�� �Լ�

#endif