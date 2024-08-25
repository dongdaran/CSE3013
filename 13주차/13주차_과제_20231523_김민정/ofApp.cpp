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
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isDFS = false;
	isBFS = false;
	isOpen = 0;
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

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
	menu->AddPopupItem(hPopup, "Show DFS", false, false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS",false,false); // Not checked (default)
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
	//
	if (title == "Open") {
		readFile();
	}
	if (title == "Exit") {
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if (title == "Show DFS") {
		//bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			DFS();
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;

	}

	if (title == "Show BFS") {

		if (isOpen)
		{	
			BFS();
			bShowInfo = bChecked;

		}
		else
			cout << "you must open file first" << endl;

	}

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

}


//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(ofRandom(50, 100));
	ofSetLineWidth(5);
	int i, j;

	// TO DO : DRAW MAZE; 
	// 저장된 자료구조를 이용해 미로를 그린다.
	// add code here
	for (int y = 0; y < draw_HEIGHT; ++y) {
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
	}

	if (isDFS)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen)
			dfsdraw();
		else
			cout << "You must open file first" << endl;
	}

	if (isBFS)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen)
			bfsdraw();

		else
			cout << "You must open file first" << endl;
	}
	if (bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight() - 20);
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
	if (key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if (key == 'f') {
		bFullscreen = !bFullscreen;
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
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
bool ofApp::readFile()
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;
	vector < string > linesOfTheFile;


	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		//string fileName = "maze0.maz";
		printf("file name is %s\n", fileName);
		filePath = openFileResult.getPath();
		printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(fileName);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				cout << "We found the target file." << endl;
				isOpen = 1;
			}


			ofBuffer buffer(file);
			freeMemory();
			ofBackground(255);
			isDFS = false;
			isBFS = false;

			// Input_flag is a variable for indication the type of input.
			// If input_flag is zero, then work of line input is progress.
			// If input_flag is one, then work of dot input is progress.
			int input_flag = 0;

			// Idx is a variable for index of array.
			int idx = 0;

			// Read file line by line
			int cnt = 0;

			for (auto line : buffer.getLines()) {
				linesOfTheFile.push_back(line);
			}

			draw_WIDTH = linesOfTheFile[0].size();
			draw_HEIGHT = linesOfTheFile.size();
			WIDTH = (draw_WIDTH - 1) / 2;
			HEIGHT = (draw_HEIGHT - 1) / 2;


			// TO DO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다.
			buffer.resetLineReader();

			input = new char* [draw_HEIGHT];
			for (int i = 0; i < draw_HEIGHT; i++)
				input[i] = new char[draw_WIDTH + 1];


			for (auto line : buffer.getLines()) {
				strcpy(input[cnt], line.c_str());
				cnt++;
			}

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

			return true;
		}
		else {
			printf("  Needs a '.maz' extension\n");
			return false;
		}
	}
}
void ofApp::freeMemory() {
	nodePointer prev;
	nodePointer np;
	stack_pointer temp, sp=top;
	queue_pointer qtmp, qp = front;

	while (sp != NULL) {
		temp = sp;
		sp = sp->link;
		free(temp);

	}
	top = NULL;


	while (qp != NULL) {
		qtmp = qp;
		qp = qp->link;
		free(qtmp);

	}
	front = NULL;
	rear = NULL;
	
	

	for (int i = 0; i < room_num; i++) {
		np = graph[i];
		while (np != NULL) {
			prev = np;
			np = np->link;
			free(prev);
		}
	}



	for (int i = 0; i < draw_HEIGHT; i++) {
		delete[] input[i];
	}

	delete[] input;
	delete[] graph;

	free(trace);
	free(visited);
	free(parent);

	//TO DO
	// malloc한 memory를 free해주는 함수
}

bool ofApp::DFS()//DFS탐색을 하는 함수
{
	//TO DO
	//DFS탐색을 하는 함수 ( 3주차)

	if (!visited)
		free(visited);
	if (!trace)
		free(trace);

	isBFS = false;
	visited = (int*)malloc(sizeof(int) * room_num);
	trace = (int*)malloc(sizeof(int) * room_num*8);
	nodePointer w;
	bool adj;

	for (int i = 0; i < room_num; i++)
		visited[i] = 0;

	for (int i = 0; i < room_num * 8; i++)
		trace[i] = -1;

	trace_index = 0;

	push(&top, 0);
	visited[0] = 1;
	ofSetColor(ofColor::olive);
	while (top) {
		adj = false;

		if (top->item == room_num - 1) {
			isDFS = true;
			return true;
		}
		
		
		for (w = graph[top->item]; w; w = w->link) {
			if (!visited[w->vertex]) {
				push(&top, w->vertex);
				visited[w->vertex] = 1;
				adj = true;
				trace[trace_index++]= top->item - top->link->item;
				break;
			}
		}

		if (!adj) {
			trace[trace_index++] = top->link->item - top->item;
			pop(&top);
			
		}

		}
	
	isDFS = false;
	return false;
}

void ofApp::dfsdraw()
{	
	ofSetColor(ofColor::olive);
	int startX = 50, startY = 50;

	for (int i = 0; i < trace_index; i++) {
		if (trace[i] == WIDTH) {
			ofDrawLine(startX, startY, startX, startY + 100);
			startY += 100;
		}

		else if (trace[i] == -WIDTH) {
			ofDrawLine(startX, startY, startX, startY - 100);
			startY -= 100;
		}

		else if (trace[i] == 1) {
			ofDrawLine(startX, startY, startX + 100, startY);
			startX += 100;
		}

		else if (trace[i] == -1&&startX!=50) {
			ofDrawLine(startX, startY, startX - 100, startY);
			startX -= 100;
		}

	}


	stack_pointer up, down;

	ofSetColor(ofColor::aqua);

	startX = WIDTH * 100 - 50, startY = HEIGHT * 100 - 50;
	up = top;
	down = up->link;
	while (down) {
		if (down->item - up->item == WIDTH) {
			ofDrawLine(startX, startY, startX, startY + 100);
			startY += 100;
		}

		else if ( up->item- down->item == WIDTH) {
			ofDrawLine(startX, startY, startX, startY - 100);
			startY -= 100;
		}

		else if (down->item - up->item == 1) {
			ofDrawLine(startX, startY, startX + 100, startY);
			startX += 100;
		}

		else if (down->item - up->item == -1 && startX!=50) {
			ofDrawLine(startX, startY, startX - 100, startY);
			startX -= 100;
		}

		up = down;
		down = down->link;

	}



}


bool ofApp::BFS() {
	isDFS = false;
	int v;
	if (!visited)
		free(visited);
	if (!trace)
		free(trace);

	visited = (int*)malloc(sizeof(int) * room_num);
	trace = (int*)malloc(sizeof(int) * room_num * 8);
	parent = (int*)malloc(sizeof(int) * room_num);

	nodePointer w;

	for (int i = 0; i < room_num; i++)
		visited[i] = 0;

	for (int i = 0; i < room_num * 8; i++)
		trace[i] = -1;

	for (int i = 0; i < room_num; i++)
		parent[i] = -1;
	
	trace_index = 0;
	visited[0] = 1;
	addq(&front, &rear, 0);

	while (front) {
		v = front->item;
		deleteq(&front);

		if (v == room_num - 1) {
			isBFS = true;
			return true;
		
		}

		for (w = graph[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				visited[w->vertex] = 1;
				trace[trace_index++] = v;
				trace[trace_index++] = w->vertex;
				parent[w->vertex] = v;

				addq(&front, &rear, w->vertex);
			}
		}

	}

	isBFS = false;
	return false;

}

void ofApp::bfsdraw() {
	ofSetColor(ofColor::black);
	int cur_X=50, cur_Y=50, cur_room_idx;

	for (int i = 0; i < trace_index; i = i + 2) {
		cur_room_idx = trace[i];
		cur_Y = 50+100*(cur_room_idx / WIDTH);
		cur_X = 50 + 100*(cur_room_idx % WIDTH);

		if (trace[i] - trace[i + 1] == 1) 
			ofDrawLine(cur_X, cur_Y, cur_X - 100, cur_Y);

		else if (trace[i] - trace[i + 1] == -1)
			ofDrawLine(cur_X, cur_Y, cur_X + 100, cur_Y);

		else if (trace[i] - trace[i + 1] == WIDTH)
			ofDrawLine(cur_X, cur_Y, cur_X, cur_Y-100);

		else if (trace[i+1] - trace[i] == WIDTH)
			ofDrawLine(cur_X, cur_Y, cur_X, cur_Y+100);

	}

	
	ofSetColor(ofColor::aqua);
	int startX = WIDTH * 100 - 50, startY = HEIGHT * 100 - 50;
	int prev, curr;
	curr = room_num - 1;
	prev = parent[curr];

	while (prev != -1) {
		if (prev - curr == WIDTH) {
			ofDrawLine(startX, startY, startX, startY + 100);
			startY += 100;
		}

		else if (curr - prev == WIDTH) {
			ofDrawLine(startX, startY, startX, startY - 100);
			startY -= 100;
		}

		else if (curr - prev == 1) {
			ofDrawLine(startX, startY, startX - 100, startY);
			startX -= 100;
		}

		else if (curr-prev == -1) {
			ofDrawLine(startX, startY, startX + 100, startY);
			startX += 100;
		}

		curr = prev;
		prev = parent[prev];


	}
	

}

