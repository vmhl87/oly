#include <iostream>
#include <array>
#include "werewolf.h"

std::vector<std::array<int, 2>> tree;
unsigned int sz;

void build(std::vector<int> a){
	sz = a.size();
	tree.resize(sz*2);
	for(int i=0; i<sz; ++i)
		tree[i+sz] = {a[i], a[i]};
	for(int i=sz-1; i; --i)
		tree[i] = {
			std::min(tree[i<<1][0], tree[i<<1|1][0]),
			std::max(tree[i<<1][1], tree[i<<1|1][1])
		};
}

int rmin(int l, int r){
	int ret = tree[l+sz][0];
	for(l += sz, r += sz+1; l < r; l >>= 1, r >>= 1){
		if(l&1) ret = std::min(ret, tree[l++][0]);
		if(r&1) ret = std::min(ret, tree[--r][0]);
	}
	return ret;
}

int rmax(int l, int r){
	int ret = tree[l+sz][1];
	for(l += sz, r += sz+1; l < r; l >>= 1, r >>= 1){
		if(l&1) ret = std::max(ret, tree[l++][1]);
		if(r&1) ret = std::max(ret, tree[--r][1]);
	}
	return ret;
}

std::vector<int> check_validity(int n, std::vector<int> x, std::vector<int> y,
                                std::vector<int> s, std::vector<int> e,
                                std::vector<int> L, std::vector<int> R) {
	/*
  int Q = S.size();
  std::vector<int> A(Q);
  for (int i = 0; i < Q; ++i) {
    A[i] = 0;
  }
  return A;
  */
	// essentially for the line case - we wish to find the werewolf-
	// allowable region near E, and the human-allowable region near S
	// if they intersect it works
	// question now is how to achieve this
	// segtree walk?
	int q = s.size();
	std::vector<int> a(q);

	std::vector<int> adj[n];
	for(int i=0; i<x.size(); ++i)
		adj[x[i]].push_back(y[i]),
			adj[y[i]].push_back(x[i]);

	int root = 0;
	for(int i=0; i<n; ++i)
		if(adj[i].size() == 1) { root = i; break; }

	int last = -1;
	std::vector<int> line(n), at(n);
	for(int i=0; i<n; ++i){
		line[i] = root, at[root] = i;
		for(int x : adj[root]) if(x != last){
			last = root, root = x;
			break;
		}
	}

	//for(int i : line) std::cout << i << ' ';
	//std::cout << '\n';
	//for(int i=0; i<n; ++i) std::cout << at[i] << ' ';
	//std::cout << '\n';

	build(line);

	for(int i=0; i<q; ++i){
		int sl, sr, el, er;

		{
			int l = 0, r = at[s[i]];
			while(l < r){
				int m = (l+r)/2;
				if(rmin(m, at[s[i]]) < L[i])
					l = m+1;
				else r = m;
			}
			sl = l;
		}

		{
			int l = at[s[i]], r = n-1;
			while(l < r){
				int m = (l+r+1)/2;
				if(rmin(at[s[i]], m) < L[i])
					r = m-1;
				else l = m;
			}
			sr = l;
		}

		{
			int l = 0, r = at[e[i]];
			while(l < r){
				int m = (l+r)/2;
				if(rmax(m, at[e[i]]) > R[i])
					l = m+1;
				else r = m;
			}
			el = l;
		}

		{
			int l = at[e[i]], r = n-1;
			while(l < r){
				int m = (l+r+1)/2;
				if(rmax(at[e[i]], m) > R[i])
					r = m-1;
				else l = m;
			}
			er = l;
		}

		//std::cout << s[i] << ',' << e[i] << ' ' << L[i] << ',' << R[i] << '\n';
		//std::cout << ' ' << sl << ',' << sr << ' ' << el << ',' << er << '\n';

		a[i] = at[s[i]] > at[e[i]] ? er >= sl : sr >= el;
	}

	return a;
}
