// Lights, Camera, Airplane  -  https://codesprintla24.kattis.com/contests/codesprintla24highschool/problems/lightscameraairplane
// Long problem; I'll write up the full edi later.
// Esssentially, we can solve using a DFS and CRT.

#include <iostream>
#include <cmath>
#include <array>
#include <stack>
#include <queue>

#include <stdlib.h>

int gcd(int a, int b){
	if(a < b) return gcd(b, a);
	if(b == 0) return a;
	return gcd(b, a%b);
}

long long inv(int a, int p){
	int m0 = p, t, q;
	int x0 = 0, x1 = 1;
	if(p == 1) return 0;
	while(a > 1){
		q = a/p, t = p;
		p = a%p, a = t;
		t = x0;
		x0 = x1 - q*x0;
		x1 = t;
	}
	if(x1 < 0) x1 += m0;
	return x1;
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
	if(g == b) return c;
	if(g == d) return a;
	if(a == b) a = 0;
	if(c == d) c = 0;

	for(int i=2; i<=g; ++i){
		if(g%i == 0){
			int j = i;
			while(g%(j*i) == 0) j *= i;
			if((b/j)%i != 0) b /= j;
			else if((d/j)%i != 0) d /= j;
			g /= j;
		}else if(i*i > g){
			if((b/g)%g != 0) b /= g;
			else if((d/g)%g != 0) d /= g;
			break;
		}
	}

	a %= b, c %= d;

	int g1 = gcd(b, c), g2 = gcd(d, a);

	long long i1 = inv(b/g1, d) * (long long)(c/g1),
		 	  i2 = inv(d/g2, b) * (long long)(a/g2);

//	if(i1 < 0 || i2 < 0) for(;;){}

	i1 %= d, i2 %= b, i1 *= b, i2 *= d;

	long long o = (long long)b * (long long)d;

	i1 += i2, i1 %= o;

	if(i1 > 1<<30) i1 = -1;

	return i1;
}

/*
void crt(int a, int b, int c, int d){
	std::cout << "(" << a << " mod " << b << ") | (" << c << " mod " << d << ") results in (" <<
		crt_n(a, b, c, d) << " mod " << crt_d(a, b, c, d) << ")\n";
}

void testcrt(int t){
	int a = 3 + rand()%20, b = 3 + rand()%20, c = 3 + rand()%20, d = 3 + rand()%20;
	a %= b, c %= d;
	int n = crt_n(a, b, c, d), m = crt_d(a, b, c, d);
	if(n != -1 && (n%b != a || n%d != c))
		std::cout << a << ',' << b << ',' << c << ',' << d << " -> " << n << '|' << m << '\n' <<
			"\t" << n%b << '|' << b << ", " << n%d << '|' << d << "\n\n";
	if(t) testcrt(t-1);
}
*/

int main(){
	int n, t; std::cin >> n >> t;

	// ret, EOL, mod
	int ans[n] = {}, del[n], mod[n] = {}, parent[n] = {};
	for(int i=0; i<n; ++i) del[i] = t;
	std::queue<int> adj[n];

	for(int i=0; i<n; ++i){
		int r; std::cin >> mod[i];

		for(int j=0; j<mod[i]; ++j)
			std::cin >> r, adj[i].push(r-1), parent[r-1] = i+1;
	}

	for(int i=1; i<n; ++i){
		int a, b, c; std::cin >> a >> b >> c;
		if(parent[a-1] == b) b = a;
		del[b-1] = c;
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
				crt_n(a%b, b, (mod[u]-adj[u].size()+1)%mod[u], mod[u]),
				crt_d(a%b, b, (mod[u]-adj[u].size()+1)%mod[u], mod[u])
			}), adj[u].pop();
		else{
			if(a != -1 && mod[u] == 0){
				ans[u] += (e-1)/b;
				if(a == 0) a = b;
				if((e-1)%b >= a) ++ans[u];
			}
			dfs.pop();
			if(a != -1 && dfs.size()){
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

//	if(sum < t) for(;;){}

	std::cout << '\n';
}
