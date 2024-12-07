#include <iostream>

char a[10][10];

int s(int a, int b, int c, int d){
	return std::abs(a-c) + std::abs(b-d);
}

int main(){
	int h, w, d; std::cin >> h >> w >> d;

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			std::cin >> a[i][j];

	int best = 0;

	for(int x1=0; x1<h; ++x1)
		for(int y1=0; y1<w; ++y1)
			if(a[x1][y1] == '.')
			for(int x2=0; x2<h; ++x2)
				for(int y2=0; y2<w; ++y2)
					if(a[x2][y2] == '.'){
					int res = 0;
					for(int i=0; i<h; ++i)
						for(int j=0; j<w; ++j)
							if(a[i][j] == '.')
								if(s(x1, y1, i, j) <= d ||
								   s(x2, y2, i, j) <= d)
									++res;
					best = std::max(best, res);
				}

	std::cout << best << '\n';
}
