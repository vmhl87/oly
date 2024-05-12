// Network Breakdown  -  https://cses.fi/problemset/task/1677/
#include <iostream>
#include <array>
#include <stack>
#include <set>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	int n, m, k; std::cin >> n >> m >> k;
	std::set<std::array<int, 2>> init;
	std::array<int, 2> add[k];
	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b;
		init.insert({a, b});
	}
	for(int i=0; i<k; ++i){
		std::cin >> add[i][0] >> add[i][1];
		init.erase(add[i]);
		init.erase({add[i][1], add[i][0]});
	}
	int dsu[n] = {0}, comps = n;
	for(auto x : init){
		int a = x[0]-1, b = x[1]-1;
		std::stack<int> tr;
		while(dsu[a]) tr.push(a), a = dsu[a]-1;
		while(dsu[b]) tr.push(b), b = dsu[b]-1;
		if(a != b) tr.push(b), --comps;
		while(tr.size()) dsu[tr.top()] = a+1, tr.pop();
	}
	std::stack<int> ret;
	for(int i=k-1; i>=0; --i){
		ret.push(comps);
		int a = add[i][0]-1, b = add[i][1]-1;
		std::stack<int> tr;
		while(dsu[a]) tr.push(a), a = dsu[a]-1;
		while(dsu[b]) tr.push(b), b = dsu[b]-1;
		if(a != b) tr.push(b), --comps;
		while(tr.size()) dsu[tr.top()] = a+1, tr.pop();
	}
	std::cout << ret.top(), ret.pop();
	while(ret.size()) std::cout << ' ' << ret.top(), ret.pop();
	std::cout << '\n';
}
