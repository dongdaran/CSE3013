#define _CRT_SECURE_NO_WARNINGS
#include "reading.h"
#include <stdio.h>

int main(void) {
	int page_input=0; //page_input:1~page_input���� ���� ���ڼ��� ����.
	scanf("%d", &page_input);//page_input�� ����ڿ��� �Է¹޴´�.
	int page_count[10] = { 0,0,0,0,0,0,0,0,0,0 };//page_count �迭:�� �ε����� �������� �����ϴ� 0-9���� �����̴�.

	count_page(page_input, page_count);//�Է¹��� ����������, 0-9���� ������ ���� �迭�� ���ڼ� ���� �Լ��� �Ű������� �Է��Ѵ�.
	writing_arr(page_count);//���ڼ� ���� �迭�� ����Ѵ�.

	return 0;//program�� �����Ѵ�.
}