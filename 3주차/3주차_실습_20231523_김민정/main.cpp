#include "Array.h"
#include "RangeArray.h"
#include <iostream>
using namespace std;

int main(void)
{
	int i, x, y;
	Array a(10), b(5);
	for (i = 0; i < a.length(); i++) a[i] = i + 1; //left value
	for (i = 0; i < b.length(); i++) b[i] = i * 2;
	cout << "a(10)"; a.print();
	cout << "b(5)"; b.print();
	cout << "a[-1] ";
	a[-1] = 7; // Array bound error!
	x = a[0]; y = b[0]; // right value
	cout << "a[0]=" << x << " b[0]=" << y << endl;
	RangeArray c(-1, 3), d(3, 7);
	for (i = c.baseValue(); i <= c.endValue(); i++) c[i] = i * 3; //left value
	for (i = d.baseValue(); i <= d.endValue(); i++) d[i] = i * 4;
	cout << "c(-1,3)"; c.print();
	cout << "d(3,7)"; d.print();
	cout << "c[-2] ";
	c[-2] = 3; // Array bound error!
	x = c[-1]; y = d[3]; // right value
	cout << "c[-1]=" << x << " d[3]=" << y << endl;
	return 0;


}
