#include"holiday.h"

#include <iostream>

using ll = long long;

ll left[3000][3000], right[3000][3000];

ll findMaxAttraction(int n, int start, int d, int attr[]){
	for(int i=1; i<3000; ++i)
		left[i] = attr[start], right[i] = attr[start];
}
