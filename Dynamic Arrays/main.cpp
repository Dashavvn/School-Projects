#include <iostream>
#include "dynarray.h"

using namespace std;
int main()
{
	Dynarray<int> d;
	for (int i=0; i < 1000; ++i) {
		d[i] = i;
	}
	d.shrink(10);
	for (int i=0; i < d.size(); ++i) {
		cout << d[i] << endl;
	}
	d[30] = -6;
	for (int i=0; i < d.size(); ++i) {
		cout << d[i] << endl;
	}
}

