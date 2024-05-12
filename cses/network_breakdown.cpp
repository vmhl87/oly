// Network Breakdown  -  https://cses.fi/problemset/task/1677/
// This problem becomes quite trivial if we consider it in reverse:
// rather than starting with the fully built graph and determining
// if the removal of an edge splits a component, we can start with
// the final broken graph, and add each edge that gets broken - we
// can use DSU to easily determine whether or not new components
// are made.

#include <iostream>
#include <array>
#include <stack>
#include <set>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	int n, m, k; std::cin >> n >> m >> k;
	// initial and added edges - we will need to filter out the
	// added edges from the initial before building graph
	std::set<std::array<int, 2>> init;
	std::array<int, 2> add[k];
	// input all initial, including added
	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b;
		init.insert({a, b});
	}
	// input added edges, and erase them from initial
	for(int i=0; i<k; ++i){
		std::cin >> add[i][0] >> add[i][1];
		init.erase(add[i]);
		// can possibly be reversed
		init.erase({add[i][1], add[i][0]});
	}
	// inline dsu - 1-indexed because the input format is
	int dsu[n] = {0}, comps = n;
	// for each initial add, unite the cities and update comps
	for(auto x : init){
		int a = x[0]-1, b = x[1]-1;
		// path contraction!
		std::stack<int> tr;
		while(dsu[a]) tr.push(a), a = dsu[a]-1;
		while(dsu[b]) tr.push(b), b = dsu[b]-1;
		if(a != b) tr.push(b), --comps;
		while(tr.size()) dsu[tr.top()] = a+1, tr.pop();
	}
	// add each removed edge in backwards order (and store the
	// component count *before* addition, so it can be reversed
	// in the final output)
	int ret[k];
	for(int i=k-1; i>=0; --i){
		ret[i] = comps;
		// identical dsu to the other one
		int a = add[i][0]-1, b = add[i][1]-1;
		std::stack<int> tr;
		while(dsu[a]) tr.push(a), a = dsu[a]-1;
		while(dsu[b]) tr.push(b), b = dsu[b]-1;
		if(a != b) tr.push(b), --comps;
		while(tr.size()) dsu[tr.top()] = a+1, tr.pop();
	}
	for(int i=0; i<k; ++i){
		if(i) std::cout << ' ';
		std::cout << ret[i];
	}
	std::cout << '\n';
}
