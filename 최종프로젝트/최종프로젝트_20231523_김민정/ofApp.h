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
	bool readFile();//result.maz를 input과 graph에 업로드하는 함수
	void freeMemory();//미로를 그리기전 이전의 설정을 모두 초기화하는 함수 input과 graph 메모리 해제함수


	void opendraw();//처음시작화면그리기함수

	unsigned long long startTime;//시작시간 저장변수
	unsigned long long cur_score;//소요시간 저장변수

	int upload_flag;//데이터업로드(1이면 업로드 완료, 0이면 아직 업로드가 안됨)
	int opendraw_flag;//초기화면실행플래그 1이면 실행 0이면 종료
	int gamestart_flag = false;//게임실행플래그  1이면 실행 0이면 종료
	int mazesize_flag = false;//사용자에게 미로의 정보를 받기 준비하는 플래그 1이면 너비와 높이를 받고 0이면 받지 않는다
	int curr_inputx = 1; int curr_inputy = 1;//현재 사용자의 x, y위치를 저장하는 함수
	int HEIGHT;//미로의 높이
	int WIDTH;//미로의 너비
	int draw_HEIGHT;//'-, |, +, '를 포함한 미로의 높이
	int draw_WIDTH;//'-, |, +, '를 포함한 미로의 너비
	int room_num = 0;//총 room의 갯수를 저장
	int final_flag = false;//최종화면실행플래그 1이면 실행 0이면 종료
	char** input;//텍스트 파일의 모든 정보를 담는 이차원 배열이다.
	int maze_col;//미로칸의 열의 인덱스를 가리킨다.
	int maze_row;//미로칸의 행의 인덱스를 가리킨다.
	int isOpen; //파일이 열렸는지를 판단하는 변수. 0이면 안열렸고 1이면 열렸다.
	struct node {
		int vertex;
		struct node* link;
	};
	typedef struct node* nodePointer;
	nodePointer* graph;
	//그래프 관련 자료구조



	// Menu
	ofxWinMenu* menu; // Menu object
	void appMenuFunction(string title, bool bChecked); // Menu return function

	// Used by example app
	ofTrueTypeFont menu_title;
	ofTrueTypeFont menu_text;
	ofTrueTypeFont size_text;
	ofTrueTypeFont myFont;
	//폰트를 저장하는 변수
	ofImage opening;
	ofImage finalpic;
	//이미지를 저장하는변수
	float windowWidth, windowHeight;
	HWND hWnd; // Application window
	HWND hWndForeground; // current foreground window

	// Example menu variables
	bool bShowInfo;
	bool bFullscreen;
	bool bTopmost;
	bool generatemaze;//미로가 다 만들어졌는지 확인하는 함수이다
	
	vector<string> linesOfTheFile;//input배열에 미로정보를 넣기 위해 임시로 도입한 변수
	// Example functions
	void doFullScreen(bool bFull);
	void doTopmost(bool bTop);

	
};
