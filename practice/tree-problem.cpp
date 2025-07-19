// tree problem:
//   given tree of n vertices, color edges white & black to maximize # of alternating-color paths
//
// idea:
//   observe that you can take an entire subtree and flip the colors of all of its edges and
//   the number of alternating paths within it will not change; therefore, we can do some sort
//   of tree dp where we optimally color subtrees first and then merge them where they meet
//   it appears that this merge operation requires the use of knapsack:
//     suppose that we have all the subtrees of a node processed, and we know the number of
//     alternating-color paths that end at their respective roots. we now want to optimally
//     color the connections from the original node to the roots of the subtrees in order
//     to maximize the # of new alternating-color paths
//     essentially if there are n valid total paths extending down from the orig node, we want
//     to partition them such that x of them have a white first edge and n-x of them with black
//     thus the number of new paths is x(n-x) <- observe that this is maximized when x is close
//     to n/2 <- in order to accomplish this we now have knapsack
//   thus because knapsack is going to be a slow operation we ideally should use centroid decomp

#include <iostream>
#include <vector>

// maxn
const int N = 1e5;

std::vector<int> tree[N];

void dfs(int i, int p){
	for(int j : tree[i]) if(j != p){
		dfs(j, i);
	}
}

int main(){
	// standard input format...
	int n; std::cin >> n;

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		tree[--a].push_back(--b);
		tree[b].push_back(a);
	}

	dfs(0, 0);
}
