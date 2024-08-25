#define _CRT_SECURE_NO_WARNINGS
#include "str.h"
#include <iostream>
using namespace std;

Str::Str(int leng)
{
	if (leng < 0)
	{/*만약 문자열의 길이(leng)의 길이가 0이하면 예외처리를 하여
	 사용자에게 에러메시지를 보내고 프로그램을 종료한다*/
		cout << "ERROR! : leng can't be negative";
		return;
	}
	else
	{
		len = leng;//문자열의 길이를 의미하는 멤버변수 len에 사용자가 입력한 글자수 저장
		str = new char[len + 1];//NULL요소까지 고려하여 문자열 설정
		str[len] = '\0';//맨 마지막 문자열의 끝을 알기위 NULL 삽입
	}

}

Str::Str(const char* neyong)
{
	if (neyong == NULL)
	{/*만약 문자열에 내용이 없다면 예외처리를 하여
	 사용자에게 에러메시지를 보내고 프로그램을 종료한다*/
		cout << "ERROR : input must not be NULL";
		return;
	}
	else
	{
		len = strlen(neyong);
		/*strlen: 문자열의 길이를 숫자로 변환하는 함수.
		사용자가 입력한 문자열의 길이를 함수를 통해 알아낸다*/
		str = new char[len + 1]; //NULL요소까지 고려하여 문자열 설정
		strcpy(str, neyong);//strcpy(s1,s2) : s2의 내용을 s1 문자열배열에 복사하는 함수

	}

}

Str::~Str()
{
	delete[] str;//프로그램 종료와 동시에 객체들을 삭제한다.
}


int Str::length(void)
{
	return len;//객체의 길이를 반환한다.
}

char* Str::contents(void)
{
	return str;//객체의 문자열 내용을 반환한다.
}

int Str::compare(const class Str& a)
{
	return strcmp(str, a.str);
	/*strcmp(s1, s2)
	1. s1 > s2 : 양수 반환
	2. s1 = s2 : 0 반환
	3. s1 < s2 : 음수 반환
	*/
}

int Str::compare(const char* a)
{
	return strcmp(str, a);
	/*strcmp(s1, s2)
	1. s1 > s2 : 양수 반환
	2. s1 = s2 : 0 반환
	3. s1 < s2 : 음수 반환
	*/
}

void Str::operator=(const char* a)
{
	if (str != NULL) {
		delete[] str;//만약 str의 내용이 존재한다면 내용을 삭제한다.
	}
	len = strlen(a); // 사용자가 입력한 문자열의 길이를 얻는다
	str = new char[len + 1];//NULL요소까지 고려하여 문자열 설정
	strcpy(str, a);
	/*strcpy(s1, s2) : s2의 내용을 s1 문자열배열에 복사하는 함수.
	a 문자열의 내용을 객체로 복사한다*/
}
void Str::operator=(const class Str& a)
{
	if (str != NULL) {
		delete[]str;//만약 str의 내용이 존재한다면 내용을 삭제한다.
	}
	len = a.len;// 사용자가 입력한 객체 문자열의 길이를 얻는다
	str = new char[len + 1];//NULL요소까지 고려하여 문자열 설정
	strcpy(str, a.str);
	/*strcpy(s1, s2) : s2의 내용을 s1 문자열배열에 복사하는 함수.
	a객체 문자열의 내용을 객체로 복사한다*/

}
