#include <iostream>

int best = 0, n, m;

int sol[20][20], cur[20][20];

int count[101];

bool rem[101][19][19];

void dfs(int now){
	if(now > best){
		best = now;
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j)
				sol[i][j] = cur[i][j];
	}

	for(int i=0; i<n-1; ++i)
		for(int j=0; j<m-1; ++j){
			if(!cur[i][j] && !cur[i+1][j] && !cur[i][j+1] && !cur[i+1][j+1]){
				if(now && rem[now-1][i][j]) continue;

				bool work = 1;

				auto test = [] (int a, int b, int v) {
					auto empty = [&] (int A, int B, int v) {
						if(A < 0 || B < 0 || A >= n || B >= m) return;
						int T = cur[A][B];
						if(T != 0) count[T] += v;
					};
					
					empty(a-1, b, v);
					empty(a+1, b, v);
					empty(a, b-1, v);
					empty(a, b+1, v);
				};

				test(i, j, -1);
				test(i+1, j, -1);
				test(i, j+1, -1);
				test(i+1, j+1, -1);

				for(int k=1; k<=now; ++k) if(count[k] <= 0) work = 0;

				auto test2 = [] (int a, int b) {
					if(a < 0 || b < 0 || a >= n || b >= m) return false;
					return cur[a][b] == 0;
				};

				if(!(test2(i-1, j) || test2(i-1, j+1) || test2(i, j-1) || test2(i+1, j-1) || test2(i, j+2) || test2(i+1, j+2) || test2(i+2, j) || test2(i+2, j+1))) work = 0;

				if(work){
					for(int a=0; a<2; ++a) for(int b=0; b<2; ++b) cur[i+a][j+b] = now+1;

					if(test2(i-1, j)) ++count[now+1];
					if(test2(i-1, j+1)) ++count[now+1];
					if(test2(i+2, j)) ++count[now+1];
					if(test2(i+2, j+1)) ++count[now+1];

					if(test2(i, j-1)) ++count[now+1];
					if(test2(i+1, j-1)) ++count[now+1];
					if(test2(i, j+2)) ++count[now+1];
					if(test2(i+1, j+2)) ++count[now+1];

					for(int I=0; I<n-1; ++I)
						for(int J=0; J<m-1; ++J)
							rem[work+1][I][J] = rem[work][I][J];

					dfs(now+1);

					for(int a=0; a<2; ++a) for(int b=0; b<2; ++b) cur[i+a][j+b] = 0;

				}else rem[work][i][j] = 1;

				test(i, j, 1);
				test(i+1, j, 1);
				test(i, j+1, 1);
				test(i+1, j+1, 1);
			}
		}
}

int main(){
	std::cin >> n >> m;

	dfs(0);

	std::cout << best << '\n';

	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j)
			if(sol[i][j]) std::cout << sol[i][j];
			else std::cout << ".";
		std::cout << '\n';
	}
}
