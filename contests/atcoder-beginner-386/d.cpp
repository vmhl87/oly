#include <algorithm>
#include <iostream>
#include <array>
#include <set>

const int N = 1<<18;

std::array<int, 3> a[N];
char b[N];

bool t[N*2];
int c[N], v;

void set(int i){
	int j = 0;
	for(int s=1<<20; s; s/=2)
		if(j+s < v && c[j+s] <= i)
			j += s;
	for(j+=N; j; j/=2) t[j] = 1;
}

bool range(int i){
	int j = 0;
	for(int s=1<<20; s; s/=2)
		if(j+s < v && c[j+s] <= i)
			j += s;
	for(j+=N+1; j; j/=2) if((j&1) && t[--j]) return 1;
	return 0;
}

int main(){
	std::set<int> s;
	int n, m; std::cin >> n >> m;
	for(int i=0; i<m; ++i) std::cin >> a[i][0] >> a[i][1] >> b[i];
	for(int i=0; i<m; ++i) s.insert(a[i][1]), a[i][2] = b[i];
	std::sort(a, a+m);

	for(int x : s) c[v++] = x;

	for(int i=0; i<m; ++i)
		if(a[i][2] == 'W') set(a[i][1]);
		else if(range(a[i][1])) std::cout << "No\n", exit(0);

	std::cout << "Yes\n";
}
