#define _CRT_SECURE_NO_WARNINGS
#include "str.h"
#include <iostream>
using namespace std;

Str::Str(int leng)
{
	if (leng < 0)
	{/*���� ���ڿ��� ����(leng)�� ���̰� 0���ϸ� ����ó���� �Ͽ�
	 ����ڿ��� �����޽����� ������ ���α׷��� �����Ѵ�*/
		cout << "ERROR! : leng can't be negative";
		return;
	}
	else
	{
		len = leng;//���ڿ��� ���̸� �ǹ��ϴ� ������� len�� ����ڰ� �Է��� ���ڼ� ����
		str = new char[len + 1];//NULL��ұ��� ����Ͽ� ���ڿ� ����
		str[len] = '\0';//�� ������ ���ڿ��� ���� �˱��� NULL ����
	}

}

Str::Str(const char* neyong)
{
	if (neyong == NULL)
	{/*���� ���ڿ��� ������ ���ٸ� ����ó���� �Ͽ�
	 ����ڿ��� �����޽����� ������ ���α׷��� �����Ѵ�*/
		cout << "ERROR : input must not be NULL";
		return;
	}
	else
	{
		len = strlen(neyong);
		/*strlen: ���ڿ��� ���̸� ���ڷ� ��ȯ�ϴ� �Լ�.
		����ڰ� �Է��� ���ڿ��� ���̸� �Լ��� ���� �˾Ƴ���*/
		str = new char[len + 1]; //NULL��ұ��� ����Ͽ� ���ڿ� ����
		strcpy(str, neyong);//strcpy(s1,s2) : s2�� ������ s1 ���ڿ��迭�� �����ϴ� �Լ�

	}

}

Str::~Str()
{
	delete[] str;//���α׷� ����� ���ÿ� ��ü���� �����Ѵ�.
}


int Str::length(void)
{
	return len;//��ü�� ���̸� ��ȯ�Ѵ�.
}

char* Str::contents(void)
{
	return str;//��ü�� ���ڿ� ������ ��ȯ�Ѵ�.
}

int Str::compare(const class Str& a)
{
	return strcmp(str, a.str);
	/*strcmp(s1, s2)
	1. s1 > s2 : ��� ��ȯ
	2. s1 = s2 : 0 ��ȯ
	3. s1 < s2 : ���� ��ȯ
	*/
}

int Str::compare(const char* a)
{
	return strcmp(str, a);
	/*strcmp(s1, s2)
	1. s1 > s2 : ��� ��ȯ
	2. s1 = s2 : 0 ��ȯ
	3. s1 < s2 : ���� ��ȯ
	*/
}

void Str::operator=(const char* a)
{
	if (str != NULL) {
		delete[] str;//���� str�� ������ �����Ѵٸ� ������ �����Ѵ�.
	}
	len = strlen(a); // ����ڰ� �Է��� ���ڿ��� ���̸� ��´�
	str = new char[len + 1];//NULL��ұ��� ����Ͽ� ���ڿ� ����
	strcpy(str, a);
	/*strcpy(s1, s2) : s2�� ������ s1 ���ڿ��迭�� �����ϴ� �Լ�.
	a ���ڿ��� ������ ��ü�� �����Ѵ�*/
}
void Str::operator=(const class Str& a)
{
	if (str != NULL) {
		delete[]str;//���� str�� ������ �����Ѵٸ� ������ �����Ѵ�.
	}
	len = a.len;// ����ڰ� �Է��� ��ü ���ڿ��� ���̸� ��´�
	str = new char[len + 1];//NULL��ұ��� ����Ͽ� ���ڿ� ����
	strcpy(str, a.str);
	/*strcpy(s1, s2) : s2�� ������ s1 ���ڿ��迭�� �����ϴ� �Լ�.
	a��ü ���ڿ��� ������ ��ü�� �����Ѵ�*/

}
