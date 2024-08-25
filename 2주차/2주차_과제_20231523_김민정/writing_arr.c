#include "reading.h"
#include <stdio.h>

void writing_arr(int* arr) {
	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]); //각 인덱스는 페이지의 숫자 글자수에 해당한다. 이를 출력한다.
	}
}