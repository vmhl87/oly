#include <iostream>
#include <cmath>
#include <array>
#include <stack>
#include <queue>

int gcd(int a, int b){
	if(a < b) return gcd(b, a);
	if(b == 0) return a;
	return gcd(b, a%b);
}

long long inv(int a, int p){
	long long r = 1;
	int pow = 1;
	while(pow <= p-2){
		if((p-2) & pow) r = r*a % p;
		a = a*a % p;
		pow <<= 1;
	}
	return r;
}

int crt_d(int a, int b, int c, int d){
	int g = gcd(b, d);
	long long ret = (long long)(b/g) * (long long)d;
	if(ret > 1<<30) return 1<<30;
	return ret;
}

int crt_n(int a, int b, int c, int d){
	if(a == -1 || c == -1) return -1;
	if(b == 1<<30){
		if(a%d == c%d) return a;
		return -1;
	}
	int g = gcd(b, d);
	if(a%g != c%g) return -1;
	a /= g, b /= g, c /= g, d /= g;
	if(a == b) a = 0;
	if(c == d) c = 0;

	long long i1 = inv(b, d) * (long long)c,
		 	  i2 = inv(d, b) * (long long)a;

	if(i1 < 0 || i2 < 0) for(;;){}

	i1 %= d, i2 %= b, i1 *= b, i2 *= d;

	long long o = (long long)b * (long long)d;

	i1 += i2, i1 %= o, i1 *= g;

	if(i1 > 1<<30) i1 = -1;

	return i1;
}

void crt(int a, int b, int c, int d){
	std::cout << "(" << a << " mod " << b << ") | (" << c << " mod " << d << ") results in (" <<
		crt_n(a, b, c, d) << " mod " << crt_d(a, b, c, d) << ")\n";
}

int main(){
	int n, t; std::cin >> n >> t;

	// ret, EOL, mod
	int ans[n] = {}, del[n], mod[n] = {};
	for(int i=0; i<n; ++i) del[i] = t;
	std::queue<int> adj[n];

	for(int i=0; i<n; ++i){
		int r; std::cin >> mod[i];

		for(int j=0; j<mod[i]; ++j)
			std::cin >> r, adj[i].push(r-1);
	}

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> a >> b;
		del[a-1] = b;
	}

	// index, EOL, a mod b
	std::stack<std::array<int, 4>> dfs;
	dfs.push({0, t+1, 0, 1});

	while(dfs.size()){
		int u = dfs.top()[0],
			e = dfs.top()[1],
			a = dfs.top()[2],
			b = dfs.top()[3];

		if(adj[u].size())
			dfs.push({
				adj[u].front(), std::min(e, del[adj[u].front()]),
				crt_n(a, b, (mod[u]-adj[u].size()+1)%mod[u], mod[u]),
				crt_d(a, b, (mod[u]-adj[u].size()+1)%mod[u], mod[u])
			}), adj[u].pop();
		else{
//			std::cout << "node " << u+1 << " hits every " << a << " mod " << b << " cycles, " <<
//				"and rolls from days 1 to " << e-1 << '\n';
			if(a != -1 && mod[u] == 0){
//				std::cout << "\tthis results in " << (e-1)/b << " full cycles\n";
				ans[u] += (e-1)/b;
//				std::cout << "\tand a partial cycle of " << (e-1)%b << " days\n";
				if(a == 0) a = b;
				if((e-1)%b >= a) ++ans[u];
			}
			dfs.pop();
			if(a != -1 && dfs.size())
				if(e < dfs.top()[1]){
//					std::cout << "\t\t overflows to node " << dfs.top()[0]+1 << " over interval " <<
//						e << " to " << dfs.top()[1]-1 << '\n';
					u = dfs.top()[0];
					ans[u] += (dfs.top()[1]-1)/b - (e-1)/b;
					if(a == 0) a = b;
					if((dfs.top()[1]-1)%b >= a) ++ans[u];
					if((e-1)%b >= a) --ans[u];
				}
		}
	}

	int sum = 0;

	for(int i=0; i<n; ++i){
		if(i) std::cout << ' ';
		std::cout << ans[i];
		sum += ans[i];
	}

	if(sum < t) for(;;){}

	std::cout << '\n';
}
