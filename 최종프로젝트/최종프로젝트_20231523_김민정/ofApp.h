/*

	ofxWinMenu basic example - ofApp.h

	Copyright (C) 2016-2017 Lynn Jarvis.

	http://www.spout.zeal.co

	=========================================================================
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	=========================================================================
*/

#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon
#include "mazemade.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100
#define MAX_CH_LEN 7


class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key); 
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	bool readFile();//result.maz�� input�� graph�� ���ε��ϴ� �Լ�
	void freeMemory();//�̷θ� �׸����� ������ ������ ��� �ʱ�ȭ�ϴ� �Լ� input�� graph �޸� �����Լ�


	void opendraw();//ó������ȭ��׸����Լ�

	unsigned long long startTime;//���۽ð� ���庯��
	unsigned long long cur_score;//�ҿ�ð� ���庯��

	int upload_flag;//�����;��ε�(1�̸� ���ε� �Ϸ�, 0�̸� ���� ���ε尡 �ȵ�)
	int opendraw_flag;//�ʱ�ȭ������÷��� 1�̸� ���� 0�̸� ����
	int gamestart_flag = false;//���ӽ����÷���  1�̸� ���� 0�̸� ����
	int mazesize_flag = false;//����ڿ��� �̷��� ������ �ޱ� �غ��ϴ� �÷��� 1�̸� �ʺ�� ���̸� �ް� 0�̸� ���� �ʴ´�
	int curr_inputx = 1; int curr_inputy = 1;//���� ������� x, y��ġ�� �����ϴ� �Լ�
	int HEIGHT;//�̷��� ����
	int WIDTH;//�̷��� �ʺ�
	int draw_HEIGHT;//'-, |, +, '�� ������ �̷��� ����
	int draw_WIDTH;//'-, |, +, '�� ������ �̷��� �ʺ�
	int room_num = 0;//�� room�� ������ ����
	int final_flag = false;//����ȭ������÷��� 1�̸� ���� 0�̸� ����
	char** input;//�ؽ�Ʈ ������ ��� ������ ��� ������ �迭�̴�.
	int maze_col;//�̷�ĭ�� ���� �ε����� ����Ų��.
	int maze_row;//�̷�ĭ�� ���� �ε����� ����Ų��.
	int isOpen; //������ ���ȴ����� �Ǵ��ϴ� ����. 0�̸� �ȿ��Ȱ� 1�̸� ���ȴ�.
	struct node {
		int vertex;
		struct node* link;
	};
	typedef struct node* nodePointer;
	nodePointer* graph;
	//�׷��� ���� �ڷᱸ��



	// Menu
	ofxWinMenu* menu; // Menu object
	void appMenuFunction(string title, bool bChecked); // Menu return function

	// Used by example app
	ofTrueTypeFont menu_title;
	ofTrueTypeFont menu_text;
	ofTrueTypeFont size_text;
	ofTrueTypeFont myFont;
	//��Ʈ�� �����ϴ� ����
	ofImage opening;
	ofImage finalpic;
	//�̹����� �����ϴº���
	float windowWidth, windowHeight;
	HWND hWnd; // Application window
	HWND hWndForeground; // current foreground window

	// Example menu variables
	bool bShowInfo;
	bool bFullscreen;
	bool bTopmost;
	bool generatemaze;//�̷ΰ� �� ����������� Ȯ���ϴ� �Լ��̴�
	
	vector<string> linesOfTheFile;//input�迭�� �̷������� �ֱ� ���� �ӽ÷� ������ ����
	// Example functions
	void doFullScreen(bool bFull);
	void doTopmost(bool bTop);

	
};
