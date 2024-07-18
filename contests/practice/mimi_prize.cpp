// Mimi and Prize  -  https://dmoj.ca/problem/dmpg18s4
// DMPG '18 S4
//
// Tree DP - keep track for each node the number of
// alternating-color paths in its subtree that are
// of odd and even length; computing paths then is
// pretty simple casework

#include <iostream>
#include <vector>

using LL = long long;

std::vector<int> adj[200000];
int a[200000];

LL dp[200000][2], res;

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p) dfs(x, i);

	// each node is a path of length 1
	dp[i][1] = 1;
	
	// accumulate paths from children
	for(int x : adj[i]) if(x != p && a[i] != a[x])
		dp[i][0] += dp[x][1], dp[i][1] += dp[x][0];

	// select any two children a, b: any odd-length
	// path on one child can be matched with an even-length
	// path on the other child to form a valid path
	LL ac = 0, bc = 0;
	for(int x : adj[i]) if(x != p && a[i] != a[x]){
		res += ac * dp[x][0], res += bc * dp[x][1];
		ac += dp[x][1], bc += dp[x][0];
	}

	// if a is a 1, count all paths coming from itself
	// to children, as they will be valid: additionally,
	// any {alternating color} path going from itself to
	// a child of parity 1 can be counted twice
	if(a[i]){
		// also, pick any two children a, b; select even-
		// length paths from each one and form two valid
		// paths
		ac = 0, ++res;
		for(int x : adj[i]) if(x != p && a[i] != a[x]){
			res += ac * dp[x][0];
			ac += dp[x][0]*2;

			res += dp[x][0]*2 + dp[x][1];
		}
	
	// similar, but for 0 case
	}else{
		ac = 0;
		for(int x : adj[i]) if(x != p && a[i] != a[x]){
			res += ac * dp[x][1];
			ac += dp[x][1]*2;

			res += dp[x][1];
		}
	}
}

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i) std::cin >> a[i], a[i] &= 1;

	for(int i=1; i<n; ++i){
		int l, r; std::cin >> l >> r, --l, --r;
		adj[l].push_back(r), adj[r].push_back(l);
	}

	dfs(0, -1);

	std::cout << res << '\n';
}
