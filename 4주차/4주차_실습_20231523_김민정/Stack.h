#include "LinkedList.h"


//1. 템플릿 클래스로 확장해야함
//2. Stack형식으로 Delete 함수 재정의해야함
//주의: first, current_size는 class의 멤버 변수이기 때문에 this 포인터를 사용하여 가져와야함

//LinkedList class를 상속받음
template<typename T>//템플릿으로 통해 클래스 확장
class Stack : public LinkedList<T> {
public:
	virtual bool Delete(T& element) {//상속을 받을 때 함수를 재정하기 위해 virtual 사용
		//first가 0이면 false반환
		if (this->first == 0) return false;//주의: first, current_size는 class의 멤버 변수이기 때문에 this 포인터를 사용하여 가져와야함

		Node<T>* current = this->first;//current함수를 초기로 표현
		this->first = this->first->link;//맨앞의 노드를 제거를 위해 다음 노드를 first로 설정
		element = current->data;//stack의 pop()의 반환을 구현
		delete current;//top 제거
		this->current_size--;//인덱스값제거
			// LinkedList와 달리 Stack은 current가 가리키는 곳을 삭제


			return true;
	}
};
