#define _CRT_SECURE_NO_WARNINGS
#include "reading.h"
#include <stdio.h>

int main(void) {
	int page_input=0; //page_input:1~page_input까지 숫자 글자수를 센다.
	scanf("%d", &page_input);//page_input를 사용자에게 입력받는다.
	int page_count[10] = { 0,0,0,0,0,0,0,0,0,0 };//page_count 배열:각 인덱스가 페이지를 구성하는 0-9까지 개수이다.

	count_page(page_input, page_count);//입력받은 페이지수와, 0-9까지 갯수를 세는 배열을 글자수 세는 함수에 매개변수로 입력한다.
	writing_arr(page_count);//글자수 개수 배열을 출력한다.

	return 0;//program을 종료한다.
}