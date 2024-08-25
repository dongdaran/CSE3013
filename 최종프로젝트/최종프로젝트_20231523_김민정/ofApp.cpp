/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.

	Copyright (C) 2016-2017 Lynn Jarvis.

	https://github.com/leadedge

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

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetScreenWidth();
	windowHeight = ofGetScreenHeight();//��üȭ���� �������� ����
	isOpen = 0;
	opendraw_flag = true;
	upload_flag = false;
	generatemaze = false;
	// Centre on the screen
	ofSetWindowShape(windowWidth, windowHeight);
	ofSetWindowPosition(0, 0);//ȭ���� ��üȭ������ ����

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);
	menu_text.loadFont("EF_jejudoldam.ttf", 30, true, true);
	menu_title.loadFont("EF_jejudoldam.ttf", 60, true, true);
	size_text.loadFont("EF_jejudoldam.ttf", 150, true, true);//�۲� ���ε�

	// Load an image for the example
	opening.load("opening.jpg");
	finalpic.load("final.jpg");//���� ���ε�

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked

	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();

} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	if (title == "Exit") {
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//

	if (title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if (title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

	

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {
	if (mazesize_flag&&!generatemaze) {
		mazemade();
		readFile();
		generatemaze = true;
	}//gamesetting�����̴�. ����ڰ����� �ʱ�ȭ�鿡 ���ʸ��콺��ư�� Ŭ���ϸ� mazesize_flag�� 1�� �Ǿ� �̰����� �����Ѵ�

}


//--------------------------------------------------------------
void ofApp::draw() {
	


	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(ofRandom(50, 100));
	ofSetLineWidth(5);
	int i, j;

	// TO DO : DRAW MAZE; 
	// ����� �ڷᱸ���� �̿��� �̷θ� �׸���.
	// add code here
	

	if (opendraw_flag)
		opendraw();//�ʱ�ȭ���� �׸����Լ��̴�
	

	if (bShowInfo) {
		
		// Show keyboard duplicates of menu functions
		sprintf(str, " MAZEGAME");
		myFont.drawString(str, 15, ofGetHeight() - 20);//mazegame���� �������ϴܿ� ���� �Լ��̴�
	}

	if (gamestart_flag) {
		ofSetColor(ofRandom(50, 100));
		ofSetLineWidth(5);
		for (int y = 0 ; y < draw_HEIGHT; ++y) {
			int startY = (y / 2) * 100;
			for (int x = 0; x < draw_WIDTH; ++x) {
				int startX = (x / 2) * 100;
				char element = input[y][x];
				switch (element) {
				case '-':
					ofDrawLine(startX, startY, startX + 100, startY);
					break;
				case '|':
					ofDrawLine(startX, startY, startX, startY + 100);
					break;
				default:
					break;
				}
			}
		}//�̷θ� �׸����Լ��̴�. readfile�� ���� input�Լ��� ������ �޾� �̷� �׸��� �׸���

		ofSetColor(ofColor::aquamarine);
		ofDrawCircle(curr_inputx * 100 / 2, curr_inputy * 100 / 2, 30);//���������� ��ġ�� �׸���. �Ķ����� ���� ������� ��ġ�̴�

	}

	if (final_flag) {//������ fianlȭ���� �׸����Լ��̴�. ���� ���� jpg�� ���ε��ϰ� ���� gameclear�۾��� ����� ����ð��� �׸���.
		ofSetColor(ofColor::white);
		finalpic.draw(0, 0, windowWidth, windowHeight);
		string finalstring = "GAMECLEAR!";
		string timetake = "Total time:"+std::to_string(cur_score) + " ms";
		float fw= menu_title.stringWidth(finalstring);
		float tw = menu_title.stringWidth(timetake);
		float h = menu_text.stringHeight(timetake);
		ofSetColor(ofColor::black);
		menu_title.drawString(finalstring, (windowWidth - fw) / 2, (windowHeight + h) / 2 - 400);
		menu_title.drawString(timetake, (windowWidth - tw) / 2, (windowHeight + h) / 2 - 300);
		

	}

} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if (bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else {
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU));
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth() - ofGetWidth()) / 2, (ofGetScreenHeight() - ofGetHeight()) / 2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if (bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if (bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if (GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// Escape key exit has been disabled but it can be checked here
	if (key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if (bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info

	if (key == 'f') {
		bFullscreen = !bFullscreen;
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

	if (gamestart_flag) {//�����ϸ鼭 ������� ��ġ�� ���ε��ϴ� �Լ��̴�. ���� �ش� ����Ű�� ������ ���� ��ġ�� ���� �ִٸ� �������� ���Ѵ�. (=���� |-�̶��)
		switch (key) {
		case OF_KEY_RIGHT:
			if (input[curr_inputy][curr_inputx + 1] != '|')
				curr_inputx += 2;
			break;
		case OF_KEY_LEFT:
			if (input[curr_inputy][curr_inputx - 1] != '|')
				curr_inputx -= 2;
			break;
		case OF_KEY_UP:
			if (input[curr_inputy - 1][curr_inputx] != '-')
				curr_inputy -= 2;
			break;
		case OF_KEY_DOWN:
			if (input[curr_inputy + 1][curr_inputx] != '-')
				curr_inputy += 2;
			break;
		}

		if (curr_inputx == 2 * WIDTH - 1 && curr_inputy == 2 * HEIGHT - 1) {//������ �������ϴܿ� �����ϸ� ������ �����ϰ� ����ȭ��(final.jpg)���� �̵�
			final_flag = true;//fianlȭ���� Ű�� �÷���
			gamestart_flag = false;//game���������� Ȯ���ϴ� �÷���
			curr_inputx = 1;
			curr_inputy = 1;//���� �ٽ� ������ �������� ���� ����Ͽ� ������� ��ġ�� ���� ������� �����Ѵ�.
			cur_score = ofGetElapsedTimeMillis() - startTime;//������� ����ð��� ����Ѵ�
		}

		
	}

	if (final_flag) {
		if (key == 'r') {//����ȭ�鿡�� RŰ�� ������ ��, �ٽ� ������ �����ϴ� ����̴�. �ٽ� ������ �����ϹǷ� ��� �÷��׿� ������ ó�������� ��ó�� ������ �ʱ�ȭ�Ѵ�.
			final_flag = false;
			opendraw_flag = true;
			generatemaze = false;
			mazesize_flag = false;
			freeMemory();
			group_index = 1; 
			height_index = 0; 

			maze.width = 0;
			maze.height = 0;
			maze.maze_group = nullptr;

			result.all_width = 0;
			result.all_height = 0;
			result.maze_info = nullptr;
			
		}

		if (key == 'q') {//����ȭ�鿡�� QŰ�� ������ ��, ������ �����ϴ� ����̴�.
			ofExit();
		}
	
	}
} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
		if (opendraw_flag) {//�ʱ�ȭ�鿡�� ���ʸ��콺��ư�� Ŭ������ ��, ���ӽ����� ���ؼ� �÷��׸� ���ε��ϴ� ����̴�.
			opendraw_flag = false;
			mazesize_flag = true;

		}
		
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

bool ofApp::readFile() {
	string filePath = "result.maz"; //mademaze()�� ���� ���� result.maz������ ȭ�鿡 �׸��� ���� ���� ����
	

	ofFile file(filePath);  //file�� result.maz ���� ������ �д´�

	if (!file.exists()) {
		cout << "Target file does not exist." << endl;
		return false;//������ �������� ���� ���� ���
	}
	else {
		cout << "We found the target file." << endl;//������ ������ ���� ���
		isOpen = 1;
		ofBuffer buffer(file);
		freeMemory();
		ofBackground(255);
		linesOfTheFile.clear();
		int input_flag = 0;//input�� ����� ������ ���� 1�� ����, ���ε� ���ϸ� 0
		int idx = 0;//�迭�� �ε����� ��Ÿ��

		int cnt = 0;//result�迭�� ���̸� �˱����� ����ϴ� tmp�Լ�
		for (auto line : buffer.getLines()) {
			linesOfTheFile.push_back(line);
		}
		draw_WIDTH = linesOfTheFile[0].size();
		draw_HEIGHT = linesOfTheFile.size();
		WIDTH = (draw_WIDTH - 1) / 2;
		HEIGHT = (draw_HEIGHT - 1) / 2;
		// TO DO
		// .maz ������ input���� �޾Ƽ� ������ �ڷᱸ���� �ִ´�.
		buffer.resetLineReader();

		input = new char* [draw_HEIGHT];
		for (int i = 0; i < draw_HEIGHT; i++)
			input[i] = new char[draw_WIDTH + 1];

		for (auto line : buffer.getLines()) {
			strcpy(input[cnt], line.c_str());
			cnt++;
		}//���� result.maz������ ������ ���͸� ���� input�迭�� �ű�� �����̴�


		//input �迭�� ���� ��������Ʈ graph�� �ϼ���Ű�� �����̴�
		room_num = HEIGHT * WIDTH;
		nodePointer prev = NULL;
		nodePointer np;
		graph = new nodePointer[room_num];

		for (int i = 0; i < room_num; i++) graph[i] = NULL;

		for (int i = 1; i < draw_HEIGHT;) {
			for (int j = 1; j < draw_WIDTH;) {
				if (input[i][j + 1] == ' ') {
					np = (nodePointer)malloc(sizeof(struct node));
					np->vertex = idx + 1;
					np->link = NULL;
					graph[idx] = np;
					prev = np;

				}

				if (input[i + 1][j] == ' ') {
					np = (nodePointer)malloc(sizeof(struct node));
					np->vertex = idx + WIDTH;
					np->link = NULL;
					if (graph[idx] == NULL) {
						graph[idx] = np;
						prev = np;
					}
					else {
						prev->link = np;
						prev = np;
					}
				}

				if (input[i][j - 1] == ' ') {
					np = (nodePointer)malloc(sizeof(struct node));
					np->vertex = idx - 1;
					np->link = NULL;
					if (graph[idx] == NULL) {
						graph[idx] = np;
						prev = np;
					}
					else {
						prev->link = np;
						prev = np;
					}
				}

				if (input[i - 1][j] == ' ') {
					np = (nodePointer)malloc(sizeof(struct node));
					np->vertex = idx - WIDTH;
					np->link = NULL;
					if (graph[idx] == NULL) {
						graph[idx] = np;
						prev = np;
					}
					else {
						prev->link = np;
						prev = np;
					}
				}
				j = j + 2;
				idx++;
			}
			i = i + 2;
		}

		//gamesetting�� ������ game�� �����Ѵ�. �÷��׸� ���� ����
		gamestart_flag = true;
		startTime = ofGetElapsedTimeMillis();//game���۽ð� ����
		mazesize_flag = false;
		return true;
	}
}



void ofApp::freeMemory() {
	nodePointer prev;
	nodePointer np;
	
	
	//���ӽ��� �������� �ʱ�ȭ�� graph�� input �����޸� ����
	if (graph != nullptr) {
		for (int i = 0; i < room_num; i++) {
			np = graph[i];
			while (np != NULL) {
				prev = np;
				np = np->link;
				free(prev);
			}
		}
		delete[] graph;
		graph = nullptr; 
	}

	if (input != nullptr) {
		for (int i = 0; i < draw_HEIGHT; i++) {
			delete[] input[i];
		}
		delete[] input;
		input = nullptr; 
	}


	group_index = 1;  
	height_index = 0; 
	maze.width = 0;
	maze.height = 0;
	maze.maze_group = nullptr;
	result.all_width = 0;
	result.all_height = 0;
	result.maze_info = nullptr;
	//TO DO
	// malloc�� memory�� free���ִ� �Լ�
}



void ofApp::opendraw() {//�ʱ����ȭ���� �׸��� �Լ�. ���� ���� jpg�� ���ε��ϰ� ���ڸ� ���ε��Ѵ�.
	ofSetColor(ofColor::white);
	opening.draw(0,0,windowWidth, windowHeight);

	ofSetColor(ofColor::black);
	string program_start1 = "PRESS LEFT MOUSEKEY";
	string program_start2 = "AND START";
	float ps1Width = menu_text.stringWidth(program_start1);
	float ps2Width = menu_text.stringWidth(program_start2);
	float ps1Height = menu_text.stringHeight(program_start1);
	menu_text.drawString(program_start1, (windowWidth - ps1Width) / 2, (windowHeight + ps1Height) / 2 - 400);
	menu_text.drawString(program_start2, (windowWidth - ps2Width) / 2, (windowHeight + ps1Height) / 2 - 340);
}


