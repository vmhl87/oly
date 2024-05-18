// attempt at using the dsu trick to simplify things, though
// it isn't faster than sparse table

#include <iostream>
#include <array>
#include <stack>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;

	int a[n], b[n], r[q];
	for(int i=0; i<n; ++i) std::cin >> a[i];

	std::stack<std::array<int, 2>> x[n];
	for(int i=0; i<q; ++i){
		int c, d; std::cin >> c >> d, x[d-1].push({c-1, i});
	}

	std::stack<int> s;
	for(int i=0; i<n; ++i){
		while(s.size() && a[i] < a[s.top()])
			b[s.top()] = i, s.pop();
		s.push(i);
		b[i] = -1;
		while(x[i].size()){
			int p = x[i].top()[0];
			std::stack<int> c;
			while(b[p] > -1) c.push(p), p = b[p];
			while(c.size()) b[c.top()] = p, c.pop();
			r[x[i].top()[1]] = p;
			x[i].pop();
		}
	}

	for(int i : r) std::cout << a[i] << '\n';
}
