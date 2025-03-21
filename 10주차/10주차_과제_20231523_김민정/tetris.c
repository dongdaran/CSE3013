﻿#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);

	createRankList();
	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_RECOMMEND: recommendedPlay(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}
	
	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
	if(!recommend_flag){
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	}

	else{
		recRoot = (RecNode*)malloc(sizeof(RecNode));
	recRoot->lv = 0;
	recRoot->score = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			recRoot->f[i][j] = field[i][j];
		}
	}
	modified_recommend(recRoot);
		blockRotate=recRoot->recommendR;
		blockY=-1;
		blockX=recRoot->recommendX;

	}
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);
	move(8,WIDTH+10);
	DrawBox(9,WIDTH+10,4,8);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(15,WIDTH+10);
	printw("SCORE");
	DrawBox(16,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':

		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;

	if(command==QUIT) ret=QUIT;
	if(!recommend_flag){
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	}
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(17,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}

	for( i = 0; i < 4; i++ ){
		move(10+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[2]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawShadow(int y, int x, int blockID,int blockRotate){
	// user code
	int y_avail = y;
	while(CheckToMove(field, blockID, blockRotate, y_avail,x)==1) {
		y_avail++;
	}
	y_avail--;
	DrawBlock(y_avail, x, blockID,blockRotate,'/');
}

void DrawBlockWithFeatures(int y,int x, int blockID,int blockRotate, char tile){
	DrawBlock(y,x,blockID,blockRotate,tile);
	DrawShadow(y,x,blockID,blockRotate);
	DrawBlock(recRoot->recommendY, recRoot->recommendX,blockID,recRoot->recommendR, 'R');
	}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	recommend_flag=0;
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	
	recRoot = (RecNode*)malloc(sizeof(RecNode));
	recRoot->lv = 0;
	recRoot->score = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			recRoot->f[i][j] = field[i][j];
		}
	}
	modified_recommend(recRoot);
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();
			newRank(score);

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");

	refresh();
	getch();
	newRank(score);

	
	free(recRoot);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1&&f[blockY+i][blockX+j]==1){
				return 0;
			}
			else if(block[currentBlock][blockRotate][i][j]==1&&blockX+j>=WIDTH) return 0;
			else if(block[currentBlock][blockRotate][i][j]==1&&blockX+j < 0) return 0;
			else if(block[currentBlock][blockRotate][i][j]==1&&blockY+i>=HEIGHT) return 0;
			
		}
		return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	// user code

	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	//3. 새로운 블록 정보를 그린다. 
	int y_avail = blockY;
	int prev_blockRotate = (blockRotate+3)%4;

	
	switch(command){
		case KEY_UP:
		while(CheckToMove(field, currentBlock, prev_blockRotate, y_avail,blockX)==1) {
		y_avail++;
	}
	y_avail--;
		for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(block[currentBlock][prev_blockRotate][i][j]==1 &&i + blockY >=0){
				move(i+blockY+1, j+blockX+1);
				printw(".");}
			if(block[currentBlock][prev_blockRotate][i][j]==1 &&i + blockY >=0){
				move(i+y_avail+1, j+blockX+1);
				printw(".");
			}
		}
	}
	
		DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate, ' ');
		break;	
		case KEY_DOWN:
		while(CheckToMove(field, currentBlock, blockRotate, y_avail,blockX)==1) {
		y_avail++;
	}
		y_avail--;
		for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1 &&i + blockY-1 >=0){
				move(blockY+i,blockX+j+1);
				printw(".");
			}
			if(block[currentBlock][blockRotate][i][j]==1 &&i + blockY >=0){
				move(i+y_avail, j+blockX+1);
				printw(".");
		}
	}}
	
		DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate, ' ');
break;
		case KEY_RIGHT:
		while(CheckToMove(field, currentBlock, blockRotate, y_avail,blockX-1)==1) {
		y_avail++;
	}
	y_avail--;
		for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1&&i + blockY >=0){
				move(blockY+1+i,blockX+j);
				printw(".");
			}
			if(block[currentBlock][blockRotate][i][j]==1 &&i + blockY >=0){
				move(i+y_avail+1, j+blockX);
				printw(".");
			
		}
	}}
	
		DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate, ' ');
break;
		case KEY_LEFT:
		while(CheckToMove(field, currentBlock, blockRotate, y_avail,blockX+1)==1) {
		y_avail++;
	}
	y_avail--;
		for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1&&i + blockY >=0){
				move(blockY+i+1,blockX+j+2);
				printw(".");
			}
			if(block[currentBlock][blockRotate][i][j]==1 &&i + blockY >=0){
				move(i+y_avail+1, j+blockX+2);
				printw(".");
		}
	}}
		DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate, ' ');

		
		
}
}

void BlockDown(int sig){
	
	// user code
	int next_flag = CheckToMove(field,nextBlock[0],blockRotate, blockY+1, blockX);
	if(next_flag==1){
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
		
	}
	else if(next_flag==0){
		score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		PrintScore(score);
		if(blockY==-1) gameOver=1;
		score += DeleteLine(field);
		PrintScore(score);

		nextBlock[0]=nextBlock[1];
		nextBlock[1]=nextBlock[2];
		nextBlock[2]=rand()%7;
		DrawNextBlock(nextBlock);


		recRoot = (RecNode*)malloc(sizeof(RecNode));
		recRoot->lv = 0;
		recRoot->score = 0;
		for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                recRoot->f[i][j] = field[i][j];
            }
        }

		modified_recommend(recRoot);

		if(!recommend_flag){
		blockRotate=0;
		blockY=-1;
		blockX=WIDTH/2-2;
		DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
		}

		else{
			blockRotate=recRoot->recommendR;
			blockY=-1;
			blockX=recRoot->recommendX;
			DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');

		}

		
		
		DrawField();
	}
	
	timed_out=0;


	//강의자료 p26-27의 플로우차트를 참고한다.
}



int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int touched=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				f[blockY+i][blockX+j]=1;
				if((f[blockY+i][blockX+j]==1 && f[blockY+i+1][blockX+j]==1)||(f[blockY+i][blockX+j]==1 && blockY+i+1==HEIGHT)) touched++;
			}
			
		}
	}
	return touched*10;

	//Block이 추가된 영역의 필드값을 바꾼다.
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	// user code
	
	int plus_line=0;
	int line_flag=0;
	for(int line=0; line<HEIGHT; line++){
		line_flag=0;
		for(int i=0; i<WIDTH; i++){
		if(f[line][i]==0) break;
		if(i==WIDTH-1) line_flag=1;
		}
		if(line_flag==1){
			plus_line++;
			for(int j=line; j>0; j--){
				for(int k=0;k<WIDTH; k++){
					f[line][k]=f[line-1][k];
				}
			}
		}
	}
	return plus_line*plus_line*100;
	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	//2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
}

///////////////////////////////////////////////////////////////////////////


void createRankList(){
	// 목적: Input파일인 "rank.txt"에서 랭킹 정보를 읽어들임, 읽어들인 정보로 랭킹 목록 생성
// 1. "rank.txt"열기
// 2. 파일에서 랭킹정보 읽어오기
// 3. LinkedList로 저장
// 4. 파일 닫기
FILE *fp;
int score;
char name[NAMELEN+1];

//1. 파일 열기
fp = fopen("rank.txt", "r");
if(fp == NULL){
	fp=fopen("rank.txt", "w");
	fprintf(fp, "%d\n", 0);
	fclose(fp);
}

rank_cnt=0;
fscanf(fp,"%d", &rank_cnt);

Node *p =NULL;
p = (Node *)malloc(sizeof(Node));

fscanf(fp, "%s", name); strcpy(p->name, name);
fscanf(fp, "%d", &score); p->score =score;
p->next =NULL;
head =p;

for(int i =0; i<rank_cnt-1; i++){
	Node *p;
	p = (Node *)malloc(sizeof(Node));
	fscanf(fp, "%s", name); strcpy(p->name, name);
	fscanf(fp, "%d", &score); p->score =score;
	p->next =NULL;

	if(score > head->score){
		p->next = head;
		head =p;
	}
	
	else{
		Node *curr =head;
		Node *prev =NULL;
		while(curr!=NULL && score < curr->score){
			prev=curr;
			curr=curr->next;
		}
		p->next=curr;
		prev->next =p;
	}
}


}


void rank(){
	//목적: rank 메뉴를 출력하고 점수 순으로 X부터~Y까지 출력함
//1. 문자열 초기화
	int X=1, Y=rank_cnt, ch, i, j;
	clear();

//2. printw()로 3개의 메뉴출력
	printw("1. list ranks form X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");

//3. wgetch()를 사용하여 변수 ch에 입력받은 메뉴번호 저장
	ch=wgetch(stdscr);

//4. 각 메뉴에 따라 입력받을 값을 변수에 저장
//4-1. 메뉴1: X, Y를 입력받고 적절한 input인지 확인 후(X<=Y), X와 Y사이의 rank 출력
if (ch == '1') {
	printw("X: ");
	echo();
	scanw("%d", &X);
	printw("Y: ");
	scanw("%d", &Y);
	noecho();
	printw("       name     |      score      \n");
	printw("------------------------------------------\n");
	if(X>Y || rank_cnt ==0 || X > rank_cnt || Y >rank_cnt)
		mvprintw(8,0,"search failure : no rank in the list\n");
	else{
		if(X<1) X=1;
		if(Y>rank_cnt) Y=rank_cnt;
		Node *curr=head;
		for(int k=0; k<X-1; k++){
			curr=curr->next;
		}
		for(int k=X;k<=Y;k++){
			printw(" %-15s| %d\n", curr->name, curr->score);
			curr = curr->next;
		}
	}
	

}

//4-2. 메뉴2: 문자열을 받아 저장된 이름과 비교하고 이름에 해당하는 리스트를 출력
else if ( ch == '2') {
	char str[NAMELEN+1];
	int check = 0;
	Node *curr=head;

	printw("input the name:");
	echo();
	scanw("%s", &str);
	noecho();
	printw("       name     |      score      \n");
	printw("------------------------------------------\n");

	for(int i=1; i<=rank_cnt; i++){
		if(!strcmp(curr->name, str)){
			printw(" %-15s| %d\n", curr->name, curr->score);
			check++;
		}
		curr = curr->next;
	}

	if(check==0)
		mvprintw(8,0,"search failure : no name in the list\n");

}

//4-3. 메뉴3: rank번호를 입력받아 리스트에서 삭제
else if ( ch == '3') {
	int num;
	echo();
	Node *curr=head, *prev;

	printw("input the rank:");
	echo();
	scanw("%d", &num);

	if(num>rank_cnt || num<1){
	mvprintw(7,0,"search failure : no rank in the list\n");
	}

	else{
	if(num==1){
		head = head->next;
	}

	else{
		for(int i=1; i<num; i++){
			prev=curr;
			curr=curr->next;
		}
		prev->next=curr->next;
	}

	free(curr);
	rank_cnt--;
	writeRankFile();
	mvprintw(7,0,"result: the rank deleted");
	
	}

}
getch();

}

void writeRankFile(){
	// 목적: 추가된 랭킹 정보가 있으면 새로운 정보를 "rank.txt"에 쓰고 없으면 종료
//1. "rank.txt" 연다
FILE *fp = fopen("rank.txt", "wt");
Node *x =head;
//2. 랭킹 정보들의 수를 "rank.txt"에 기록
if(rank_cnt!=0) fprintf(fp, "%d\n", rank_cnt);

//3. 탐색할 노드가 더 있는지 체크하고 있으면 다음 노드로 이동, 없으면 종료
if (!rank_cnt) {
	fclose(fp);
	return;
}

while(x->next!=NULL){
	fprintf(fp, "%s %d\n",x->name,x->score);
	x=x->next;
}

fprintf(fp, "%s %d\n",x->name,x->score);
fclose(fp);

}

void newRank(int score){
	// 목적: GameOver시 호출되어 사용자 이름을 입력받고 score와 함께 리스트의 적절한 위치에 저장
	char str[NAMELEN+1];
	int i, j;
	clear();
//1. 사용자 이름을 입력받음
	printw("your name: ");
	echo();
	scanw("%s", &str);
	rank_cnt++;

//2. 새로운 노드를 생성해 이름과 점수를 저장, score_number가
	Node *p=NULL;
	p = (Node *)malloc(sizeof(Node));
	Node *curr=head;
	Node *prev=NULL;

	strcpy(p->name,str);
	p->score=score;

	if (head == NULL) head=p;
	if(rank_cnt==1) head=p;
	else if(score > head->score){
		p->next = head;
		head =p;
}
else {
	while(curr!=NULL && score < curr->score){
			prev=curr;
			curr=curr->next;
		}
		p->next=curr;
        prev->next = p;
		
}

writeRankFile();
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

int modified_recommend(RecNode *root){
	//추천 시스템을 위한 트리 생성
	char this_field[HEIGHT][WIDTH];
	for(int j=0; j<HEIGHT; j++)
		for(int i=0; i<WIDTH; i++)
			this_field[j][i] = root->f[j][i];

	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수
	int min=0;
	int score = root->score;
	int rotation;
	int blockY =-1;
	int blockX =WIDTH/2-2;
	int index = 0;

	switch(nextBlock[root->lv]){
		case 0:
		case 5:
		case 6: rotation =2; break;
		case 1:
		case 2:
		case 3: rotation =4; break;
		case 4: rotation =1; break;
		default: break;

	}

	for(int i=0; i<rotation; i++){
		for(int j=-2;j<WIDTH; j++){
			blockY = 0;
			blockX = j;
			if(!CheckToMove(this_field, nextBlock[root->lv], i, blockY,j)) continue; 

			int y_avail = blockY;
			while(CheckToMove(this_field, nextBlock[root->lv], i, y_avail,j)==1) { 
				y_avail++;
			}
			y_avail--;

			root->c[index] = (RecNode*)malloc(sizeof(RecNode));

			memcpy(root->c[index]->f, this_field, sizeof(this_field));
			root->c[index]->score = root->score + AddBlockToField(root->c[index]->f, nextBlock[root->lv], i, y_avail, j) + DeleteLine(root->c[index]->f);
			root->c[index]->lv = root->lv + 1;
			root->c[index]->curBlockID = nextBlock[root->lv];

			int tmp_score = 0;
			 if (root->c[index]->lv < VISIBLE_BLOCKS && root->c[index]->score >min) {
                tmp_score = modified_recommend(root->c[index]);
            } else {
                tmp_score = root->c[index]->score;
            }

            if (tmp_score > max) {
                max = tmp_score;
                if (root->lv == 0) {
                    recRoot->recommendR = i;
                    recRoot->recommendX = blockX;
                    recRoot->recommendY = y_avail;
                }
            }

			if (tmp_score < min) {
                min = tmp_score;
            }

            index++;
        }
    }

	return max;
}


void recommendedPlay(){
	// user code
	recommend_flag=1;
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	recRoot = (RecNode*)malloc(sizeof(RecNode));
	recRoot->lv = 0;
	recRoot->score = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			recRoot->f[i][j] = field[i][j];
		}
	}
	modified_recommend(recRoot);


	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);

	free(recRoot);
}
