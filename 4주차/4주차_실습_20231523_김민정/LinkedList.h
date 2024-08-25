#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include <iostream>
using namespace std;

//LinkedList Node
//template을 이용해 확장
template <typename T>
class Node {
public:
	//데이터를 저장할 변수(T는 사용자가 원하는 자료형을 입력하면 됨)
	T data;
	//노드구조체 이용; 다음노드의 주소를 저장할 포인터(자료형이 변하기에 포인터도 자료형변환)
	Node<T>* link;

	Node(T element) {
		//노드에 입력하는 자료형이 변환
		data = element;
		link = 0;
	}
};

//LinkedList Class
template<typename T>
class LinkedList {
protected:
	//첫번째 노드의 주소를 저장할 포인터(자료형이 변화하기에 템플릿으로 노드 자료형 변화)
	Node<T>* first;
	int current_size;
public:
	//생성자, 초기화 
	LinkedList() {
		first = 0;
		current_size = 0;
	};

	//노드 개수를 리턴
	int GetSize() {
		return current_size;
	};

	//맨 앞에 원소를 삽입, LinkedList와 Stack 둘다 같다
	void Insert(T element);

	//맨 뒤의 원소를 삭제, 제일 나중에 들어온 원소 삭제  - LinkedList
	virtual bool Delete(T& element);//자료형에 상관없이 받기위해 템플릿 지정

	//리스트 출력
	void Print();
};


//새 노드를 맨 앞에 붙이고 값을 넣음
template<typename T>
void LinkedList<T>::Insert(T element) {
	//노드 생성
	Node<T>* newnode = new Node<T>(element);

	//새 노드가 첫번째 노드를 가리킴
	//newnode는 포인터이기 때문에 -> 를 사용해 함수, 변수를 불러옴 newnode.link와 뜻은 같다
	newnode->link = first;
	first = newnode;
	current_size++;
}

//마지막 노드의 값을 리턴하면서 메모리에서 할당 해제
template<typename T>
bool LinkedList<T>::Delete(T& element) {

	if (first == 0)
		return false;

	Node<T>* current = first;//처음에 시작후, 마지막 노드를 찾음
	Node<T>* previous = 0;

	//마지막 노드까지 찾아가는 반복문
	while (1) {
		if (current->link == 0) {  //마지막 노드를 찾는것
			if (previous)
				previous->link = current->link;
			else
				first = first->link;
			break;
		}
		previous = current;
		current = current->link;
	}
	element = current->data;
	delete current;
	current_size--;

	return true;
}

//리스트를 출력하는 Print 함수
template<typename T>
void LinkedList<T>::Print() {
	Node<T>* i;//T를 통해 자료형 자유롭게 변화
	int index = 1;

	if (current_size != 0) {
		for (i = first; i != NULL; i = i->link) {
			if (index == current_size) {
				cout << "[" << index << "|";
				cout << i->data << "]";
			}

			else {
				cout << "[" << index << "|";
				cout << i->data << "]->";
				index++;
			}
		}
		cout << endl;
	}

}


#endif
