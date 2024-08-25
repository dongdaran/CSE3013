#define _CRT_SECURE_NO_WARNINGS
#include "reading.h"
#include <stdio.h>


void count_page(int page_input, int* arr_page_count) {
	int current_page = 1;//페이지를 이루는 숫자들을 세는 현재의 페이지 설정. 1~page_input까지 세니 처음은 1부터 시작한다.
	int cal;//각 자리수를 계산하기 위해 current_page의 값을 복사한 변수.(current_page값을 유지하기 위해 cal을 설정함)
	int current_cal_page;//current_page의 각 자리 숫자.
	for (; current_page <= page_input; current_page++) {
		//for(*)의 의미 입력한 페이지수가 될 때까지 연산을 계속한다.
		cal = current_page;//line8에서 말한 것처럼 각 자리 수를 계산하기 위해 current_page의 값을 cal에 복사한다.
		while (cal>0) {//while(*)의 의미:currnet_page의 자릿수를 모두 구한다.
			current_cal_page = cal % 10;//current_cal_page: cal을 10으로 나누면서 일의자리수부터 최대자리수까지 자리값을 구한다.
			arr_page_count[current_cal_page]++;//해당 자리수의 숫자의 인덱스를 늘려 총 글자수를 구한다.
			cal /= 10;//현재자릿수를 구하면 /10을 하여 다음 자리수를 구할 준비를 한다.
		}

	}



}