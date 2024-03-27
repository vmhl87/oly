#include <iostream>
#include <stack>
using namespace std;

typedef struct{
	stack<int> adj;
	stack<int> proc;
	int weight=1;
}node;

int main(){
	int n;cin>>n;
	node tree[n];
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;u--;v--;
		tree[u].adj.push(v);
		tree[v].adj.push(u);
	}
	bool vis[n];for(int i=0;i<n;++i)vis[i]=0;
	stack<int> dfs;
	dfs.push(0);vis[0]=1;
	while(dfs.size()){
		int top=dfs.top();
		if(tree[top].adj.size()){
			int next=tree[top].adj.top();
			tree[top].adj.pop();
			if(!vis[next]){
				vis[next]=1;
				tree[top].proc.push(next);
				dfs.push(next);
			}
		}else{
			while(tree[top].proc.size()){
				int cur=tree[top].proc.top();
				tree[top].proc.pop();
				tree[top].adj.push(cur);
				tree[top].weight+=tree[cur].weight;
			}
			dfs.pop();
		}
	}
	int bound=n/2;
	for(int i=0;i<n;++i){
		if(i&&(n-tree[i].weight)>bound)continue;
		bool w=1;
		while(tree[i].adj.size()){
			int cur=tree[i].adj.top();
			tree[i].adj.pop();
			if(tree[cur].weight>bound){
				w=0;break;
			}
		}
		if(w){
			cout<<i+1<<'\n';
			break;
		}
	}
}
