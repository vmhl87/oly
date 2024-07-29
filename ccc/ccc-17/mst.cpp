#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

// all pipes in sorted order. To avoid using a custom comparator,
// the structure of each pipe is:
//
//   0: cost of pipe (this ensures that pipes are sorted in strictly
//                    increasing cost first, then other attrib)
//
//   1: whether or not pipe is already active (0 if so, 1 if not)
//
//   2, 3: endpoints of pipe (essentially doesn't matter

std::array<int, 4> pipe[200000];

// unite-by-size dsu; mostly standard
int root[100000];
int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

// binlifting and associated memory for retraversal.
// edges store three properties:
//
//   0: other endpoint
//
//   1: cost of this edge
//
//   2: reduction (whether or not this pipe was active initially)

std::vector<std::array<int, 3>> adj[200000];

// jump structure stores essentially the same properties as
// do edges, but store the *maximum* cost of all edges over path
// and maximum reduction associated with such a maximum cost
std::array<int, 3> jump[200000], par[200000];
int depth[200000];

// helper function to handle merging of reductions
std::array<int, 3> merge(std::array<int, 3> a, std::array<int, 3> b){
	if(a[1] > b[1]) return a;
	if(b[1] > a[1]) return b;
	if(a[2] > b[2]) return a;
	return b;
}

// re-traversal recursor which also builds binlift jumps
void dfs(int i, int p){
	for(const auto &[x, cost, red] : adj[i]) if(x != p){
		depth[x] = depth[i] + 1;

		// so messy..
		if(depth[i] + depth[jump[jump[i][0]][0]] == depth[jump[i][0]]*2)
			jump[x][0] = jump[jump[i][0]][0], jump[x][1] = std::max(cost,
					std::max(jump[i][1], jump[jump[i][0]][1])),
				jump[x][2] = merge({0, cost, red}, merge(jump[i], jump[jump[i][0]]))[2];
		else jump[x][0] = i, jump[x][1] = cost, jump[x][2] = red;

		par[x][0] = i, par[x][1] = cost, par[x][2] = red;

		dfs(x, i);
	}
}

int main(){
	int n, m, d; std::cin >> n >> m >> d;

	// input and sort pipes
	for(int i=0; i<m; ++i) std::cin >> pipe[i][2] >> pipe[i][3] >> pipe[i][0],
		--pipe[i][2], --pipe[i][3], pipe[i][1] = i >= n-1;

	std::sort(pipe, pipe+m);

	// find MST and record # of days necessary to build this tree in 'first'.
	// we don't consider enhancer at all here.
	int first = 0;

	// init dsu etc. very standard
	for(int i=0; i<n; ++i) root[i] = -1;
	for(int i=0; i<m; ++i){
		int a = find(pipe[i][2]), b = find(pipe[i][3]);
		if(a == b) continue;

		if(a < b) root[a] += root[b], root[b] = a;
		else root[b] += root[a], root[a] = b;

		first += pipe[i][1];

		adj[pipe[i][2]].push_back({pipe[i][3], pipe[i][0], pipe[i][1]});
		adj[pipe[i][3]].push_back({pipe[i][2], pipe[i][0], pipe[i][1]});
	}

	// re-process tree to build binlifts; we can now efficiently determine
	// the result of adding back one edge to the tree and removing the
	// previously largest edge in the path
	dfs(0, -1);

	// best reduction, best # of days for such reduction
	int best = 0, days = first;

	// consider all possible edges, even ones that are in MST
	for(int i=0; i<m; ++i){
		// LCA-like algorithm
		int a = pipe[i][2], b = pipe[i][3];
		if(depth[a] < depth[b]) std::swap(a, b);

		// current maximal edge, as well as best reduction on all
		// edges of that maximal weight
		int curr = 0, red = 0;
		while(depth[a] > depth[b]){
			if(depth[jump[a][0]] < depth[b])
				red = merge({0, curr, red}, par[a])[2],
				curr = std::max(curr, par[a][1]), a = par[a][0];
			else red = merge({0, curr, red}, jump[a])[2],
				curr = std::max(curr, jump[a][1]), a = jump[a][0];
		}

		while(a != b){
			if(jump[a][0] == jump[b][0])
				 red = merge({0, curr, red}, merge(par[a], par[b]))[2],
					curr = std::max(curr, std::max(par[a][1], par[b][1])),
					 a = par[a][0], b = par[b][0];
			else red = merge({0, curr, red}, merge(jump[a], jump[b]))[2],
				curr = std::max(curr, std::max(jump[a][1], jump[b][1])),
				a = jump[a][0], b = jump[b][0];
		}

		// proposed cost reduction + days necessary to complete
		int prop = curr - std::max(0, pipe[i][0] - d), dy = first + pipe[i][1] - red;

		// update running bests
		if(prop > best) best = prop, days = dy;
		else if(prop == best && dy < days) days = dy;
	}

	std::cout << days << '\n';
}
