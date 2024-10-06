#include <iostream>
#include <vector>

using ll = long long;
const int MAXN = 100100;
typedef unsigned __int128 lll;

std::vector<int> adj[MAXN];
int indeg[MAXN];

void plll(lll i){
	std::vector<char> out;
	if(!i) out.push_back('0');
	while(i){
		out.push_back('0' + (int)(i % (lll)(10)));
		i /= (lll)(10);
	}
	for(int j=out.size()-1; j>=0; --j){
		std::cout << out[j];
	}
}

struct rational{
	lll n, d;
	lll gcd(lll a, lll b){
		if(a < b) return gcd(b, a);
		if(b == 0) return a;
		return gcd(b, a%b);
	}
	void add(lll nn, lll dd){
		lll gg = gcd(d, dd);
		lll n2 = n*(dd/gg) + nn*(d/gg), d2 = d*(dd/gg),
		   gc = gcd(n2, d2);
		n2 /= gc, d2 /= gc;
		n = n2, d = d2;
	}
	void add(lll nn) { add(nn, 1); }
	void add(rational r) { add(r.n, r.d); }
	rational div(lll i){
		rational r; lll gc = gcd(n, i);
		r.n = n/gc, r.d = d*(i/gc);
		return r;
	}
	void pr(){
		plll(n), std::cout << ' ';
		plll(d), std::cout << '\n';
	}
};

rational hold[MAXN];

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i){
		int d; std::cin >> d;
		while(d--){
			int j; std::cin >> j;
			adj[i].push_back(j-1);
			++indeg[j-1];
		}
	}

	for(int i=0; i<n; ++i) hold[i].d = 1;

	std::vector<int> sort, order;

	for(int i=0; i<n; ++i) if(!indeg[i]) sort.push_back(i);

	while(sort.size()){
		int t = sort.back(); sort.pop_back();

		order.push_back(t);
		for(int x : adj[t]) if(!--indeg[x])
			sort.push_back(x);
	}

	for(int i=0; i<m; ++i){
		hold[i].add(1);

		for(int t : order) if(adj[t].size()){
			rational r = hold[t].div(adj[t].size());
			for(int x : adj[t]) hold[x].add(r);
			hold[t].n = 0, hold[t].d = 1;
		}
	}

	for(int i=0; i<n; ++i) if(!adj[i].size()) hold[i].pr();
}
