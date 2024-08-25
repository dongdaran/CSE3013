* main.cpp, mazemade.cpp, mazemade.h, ofApp.cpp, ofApp.h, ofxWinMenu.cpp, ofxWindMenu.cpp 파일 위치
-> openframework file인 of_v0.12.0_vs_release->apps->myApps->MAZE->src 파일에 들어가 추가한다.
여기서 MAZE파일은 openframework generator를 통해 새롭게 프로젝트를 생성하여 만든 파일이니, 새로 프로젝트를 생성해서 위 cpp파일과 헤더파일을 넣어야한다.(여기서 이미 만들어져 있는 main.cpp, ofApp.cpp, ofApp.h는 내용을 복사 붙여넣기를 한다)


* EF_jejudoldam.ttf, verdana.ttf, final.jpg, opening.jpg, result.maz
-> openframework file인 of_v0.12.0_vs_release->apps->myApps->MAZE->bin->data 파일에 들어가 추가한다.

* mazemade.cpp에서 upload_maze_pic()함수에서 첫번째 줄에서 파일 위치를 읽어올때 result.maz가 있는 주소를 써야한다. 현재 쓰여있는 주소는 프로젝트 제작자의 프로젝트 주소이니 만약 이를 바꾸지 않고 실행하면 오류가 날 것이다. 

*처음화면이 뜨면 왼쪽마우스버튼을 클린하다. 이후 프롬포트 창에 높이와 너비를 입력하라고 뜰 것이다. 이후 높이와 너비를 쓰면 다시 화면으로 돌아와 미로 게임을 수행한다. 왼쪽 상단에서 아래쪽 맨끝하단으로 이동하면 된다. 캐릭터의 움직임은 방향키로 제어한다.

*마지막 화면이 뜰 때, 다시 게임을 하고 싶다면 R키를 누르고 프로그램을 종료하고 싶으면 Q를 누르면 된다.