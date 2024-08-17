// firstly we can essentially make k smaller by noticing that
// every path through the graph will always end in some cycle.
// this bounds the number of iterations at N, by nature.
// then we do a little bit of extra optimization by breaking the
// graph up into a collection of segments, each one indexed such
// that jumps along that segment can be determined in O(1).
// proving the complexity of this is somewhat complicated but
// it passes lol

#include <iostream>
#include <vector>

using LL = long long;
const int S = 200001;

int x[S], a[S], pos[S], which[S], vis[S], iscyc[S], indeg[S], cc;
std::vector<int> cyc[400000];

// process some node - we first process all ends (nodes with
// indegree 0) at which point all remaining vertices must be cycle

void proc(int i){
	// initial path block
	vis[i] = 1;
	which[i] = cc;
	pos[i] = 0;
	cyc[cc].push_back(i);
	int p = x[i], co = 0;
	while(!vis[p]){
		vis[p] = 1;
		which[p] = cc;
		pos[p] = ++co;
		cyc[cc].push_back(p);
		p = x[p];
	}
	cyc[cc].push_back(p);
	++cc;

	// if found cycle, compute cycle
	// (this is why we have >n bound
	// on count of cycles)
	if(which[p] == which[i]){
		which[p] = cc;
		pos[p] = 0;
		iscyc[p] = 1;
		cyc[cc].push_back(p);
		int k = x[p], co = 0;
		while(k!=p){
			which[k] = cc;
			pos[k] = ++co;
			iscyc[k] = 1;
			cyc[cc].push_back(k);
			k = x[k];
		}
		++cc;
	}
}

int main(){
	int n; LL k; std::cin >> n >> k;
	for(int i=0; i<n; ++i) std::cin >> x[i], --x[i];
	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<n; ++i) ++indeg[x[i]];

	// ends first, to avoid silly path chunking stuff
	for(int i=0; i<n; ++i) if(indeg[i] == 0) proc(i);
	for(int i=0; i<n; ++i) if(!vis[i]) proc(i);

	// debug print trust
	if(0) for(int i=0; i<cc; ++i){
		std::cout << iscyc[cyc[i][0]] << '|';
		for(int x : cyc[i]) std::cout << 1+x << ' ';
		std::cout << '\n';
	}

	for(int i=0; i<n; ++i){
		int j = i; LL r = k;
		while(r){
			if(iscyc[j]){
				j = cyc[which[j]][
						((LL)pos[j]+r)%((int)cyc[which[j]].size())
					];
				r=0;
			}else{
				// move as far as we can along the path chunk
				// this is why we can get away with having the
				// cycle portion still in the chunk: it really
				// makes no difference in the end
				LL rem = (int)cyc[which[j]].size()-1;
				rem -= pos[j];
				rem = std::min(rem, r);
				j = cyc[which[j]][pos[j]+rem];
				r -= rem;
			}
		}
		std::cout << a[j] << " \n"[i==n-1];
	}
}
