#include <iostream>
#include <vector>

const int N = 1e5;

int a[N], d[N+1], e[N+1];
std::vector<int> c[N+1];

int make(int j, int i){
	int res = 0, p = 0;
	while(p < c[j].size()){
		++res;
		int np = c[j].size();
		for(int s=1<<18; s; s/=2)
			if(np >= s && c[j][np-s] > c[j][p]+i)
				np -= s;
		p = np;
	}
	return res;
}

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i)
		std::cin >> a[i],
		c[a[i]].push_back(i);
	
								// goofy ahh heuristic
	for(int i=1; i<=n; ++i) if(c[i].size()*100 < n)
		for(int s=1; s<=c[i].size(); ++s){
			int r = 0;
			for(int x=1<<18; x; x/=2)
				if(r+x <= n && make(i, r+x) >= s)
					r += x;
			++d[r+1], ++d[0];
		}
	else for(int j=1; j<=n; ++j)
		e[j] += make(i, j);

	for(int i=1; i<=n; ++i)
		std::cout << (d[0] -= d[i]) + e[i] << '\n';
}
