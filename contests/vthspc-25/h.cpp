#include <iostream>

long long a[200][200];

int main(){
	int x1, y1, x2, y2, x3, y3, x4, y4;
	std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
	++x1, ++y1, ++x2, ++y2, ++x3, ++y3, ++x4, ++y4;
	++x1, ++y1, ++x2, ++y2, ++x3, ++y3, ++x4, ++y4;
	++x1, ++y1, ++x2, ++y2, ++x3, ++y3, ++x4, ++y4;

	a[x1][y1] = 1;

	for(int i=1; i<200; ++i)
		for(int j=1; j<200; ++j)
			if(i != x1 || j != y1)
				if(i != x3 || j != y3)
					if(i != x4 || j != y4){
						a[i][j] = a[i-1][j] + a[i][j-1];
					}

	std::cout << a[x2][y2] << '\n';
}
