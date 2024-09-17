#include <iostream>
#include <array>

#include "highway.h"

#define active(w) (base/B-(base-ask(w))/(B-A))

std::vector<std::array<int, 2>> adj[900000];
bool vis[900000];

void find_pair(int N, std::vector<int> U, std::vector<int> V, int A, int B) {
	int m = U.size();

	std::vector<int> w(m);
	for(int i=0; i<m; ++i) w[i] = 1;
	long long base = ask(w);
	//std::cout << base << '\n';
	
	for(int i=0; i<m; ++i){
		adj[U[i]].push_back({V[i], i});
		adj[V[i]].push_back({U[i], i});
	}

	int remain = N;

	std::vector<std::vector<int>> levels;
	std::vector<int> level = {0}, cost;
	vis[0] = 1, --remain;

	while(remain){
		std::vector<int> next, add;
		for(int i : level){
			for(const auto &[x, e] : adj[i]){
				if(!vis[x]){
					next.push_back(x);
					add.push_back(e);
					vis[x] = 1, --remain;
				}
			}
		}

		levels.push_back(add);
		level = next;

		std::vector<int> w(m);
		for(int i : add) w[i] = 1;
		cost.push_back(active(w));
	}

	int l = 0;
	for(const auto &x : levels){
		std::cout << "( ";
		for(int i : x) std::cout << U[i] << '-' << V[i] << ' ';
		std::cout << ") : " << cost[l++] << '\n';;
	}

	answer(0, N - 1);
}
