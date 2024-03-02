// Barn tree  -  https://usaco.org/index.php?page=viewproblem2cpid=1254
//
// This was my first attempt at solving barn tree.
//
// Initially I made the observation that the barns,
// represented as a tree, could be arbitrarily rooted
// and then traversed (using dfs) to calculate the "hay
// sum" of each barn; that being the amount of hay contained
// in itself and the nodes under it.
//
// Then, each edge was processed - if a barn had too much hay,
// that edge would need to transport away some exact amount,
// and if a barn had too little hay, the same would happen.
//
// However, I did not find an efficient solution to order the
// edges in a way that would keep the hay counts of each barn
// non-negative upon each move.

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef struct{
	int h; // amount of hay in node
	int under; // hay in nodes under
	int w=1; // number of nodes under
	stack<int> adj;
}barn;

typedef struct{
	int a;
	int b;
	int m; // how much hay to transfer
}op;

int main(){
	int n;cin>>n;
	barn barns[n];
	int avg=0;
	for(int i=0;i<n;++i){
		cin>>barns[i].h;
		avg+=barns[i].h;
		barns[i].under=barns[i].h;
	}
	avg/=n;
	for(int i=1;i<n;++i){
		int a,b;cin>>a>>b;
		a--;b--;
		barns[a].adj.push(b);
		barns[b].adj.push(a);
	}
	// save operations
	int ops=0;
	stack<op> dep[n];
	stack<int> root;
	// root the tree arbitrarily - at 0?
	bool vis[n];for(int i=0;i<n;++i)vis[i]=1;
	stack<int> dfs;dfs.push(0);vis[0]=0;
	while(!dfs.empty()){
		int t=dfs.top();
		if(barns[t].adj.empty()){
			// relax along edge and proc
			dfs.pop();
			if(!dfs.empty()){
				// compare under to w*avg
				op nx;nx.a=t;nx.b=dfs.top();
				nx.m=barns[t].under-barns[t].w*avg;
				if(nx.m<0){
					nx.m=-nx.m;nx.a=dfs.top();nx.b=t;
				}
				if(nx.m>0){
					ops++;
					// depends barn t have >= m hay
					dep[t].push(nx);
					if(barns[t].h>=nx.m)
						root.push(t);
				}
				// add weight + hay of previous
				// node onto current one
				int x=dfs.top();
				barns[x].w+=barns[t].w;
				barns[x].under+=barns[t].under;
			}
		}else{
			int x=barns[t].adj.top();
			if(vis[x]){
				vis[x]=0;
				dfs.push(x);
			}
			barns[t].adj.pop();
		}
	}
	cout<<ops<<'\n';
	for(int i=0;i<n;++i)vis[i]=1;
	// propagate from root, try to ensure
	// no barns are pushed when not ready
	while(!root.empty()){
		int r=root.top();root.pop();
		if(!vis[r])continue;
		vis[r]=0;dfs.push(r);
		while(!dfs.empty()){
			int t=dfs.top();
			if(dep[t].empty()){
				dfs.pop();
			}else{
				op nx=dep[t].top();
				dep[t].pop();
				// print edge
				cout<<nx.a+1<<' '<<nx.b+1
					<<' '<<nx.m<<'\n';
				if(vis[nx.b]){
					vis[nx.b]=0;
					dfs.push(nx.b);
				}
			}
		}
	}
	// print untraversed
	for(int i=0;i<n;++i)if(!vis[i]){
		while(!dep[i].empty()){
			op x=dep[i].top();
			cout<<x.a+1<<' '<<x.b+1
				<<' '<<x.m<<'\n';
			dep[i].pop();
		}
	}
}
