#define _CRT_SECURE_NO_WARNINGS
#include "reading.h"
#include <stdio.h>


void count_page(int page_input, int* arr_page_count) {
	int current_page = 1;//�������� �̷�� ���ڵ��� ���� ������ ������ ����. 1~page_input���� ���� ó���� 1���� �����Ѵ�.
	int cal;//�� �ڸ����� ����ϱ� ���� current_page�� ���� ������ ����.(current_page���� �����ϱ� ���� cal�� ������)
	int current_cal_page;//current_page�� �� �ڸ� ����.
	for (; current_page <= page_input; current_page++) {
		//for(*)�� �ǹ� �Է��� ���������� �� ������ ������ ����Ѵ�.
		cal = current_page;//line8���� ���� ��ó�� �� �ڸ� ���� ����ϱ� ���� current_page�� ���� cal�� �����Ѵ�.
		while (cal>0) {//while(*)�� �ǹ�:currnet_page�� �ڸ����� ��� ���Ѵ�.
			current_cal_page = cal % 10;//current_cal_page: cal�� 10���� �����鼭 �����ڸ������� �ִ��ڸ������� �ڸ����� ���Ѵ�.
			arr_page_count[current_cal_page]++;//�ش� �ڸ����� ������ �ε����� �÷� �� ���ڼ��� ���Ѵ�.
			cal /= 10;//�����ڸ����� ���ϸ� /10�� �Ͽ� ���� �ڸ����� ���� �غ� �Ѵ�.
		}

	}



}