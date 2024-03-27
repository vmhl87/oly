#include <iostream>
#include <stack>
using namespace std;

int main(){
	int n,q;cin>>n>>q;
	int from[n];
	long long weight[n],val[n];
	for(int i=0;i<n;++i){
		cin>>val[i];
		weight[i]=val[i];
	}
	stack<int> adj[n];
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;u--;v--;
		adj[u].push(v);adj[v].push(u);
	}
	from[0]=-1;
	bool vis[n];for(int i=0;i<n;++i)vis[i]=1;
	stack<int> dfs;dfs.push(0);vis[0]=0;
	while(dfs.size()){
		int top=dfs.top();
		if(adj[top].empty()){
			long long w=weight[top];
			dfs.pop();
			if(dfs.size())
				weight[dfs.top()]+=w;
		}else{
			int next=adj[top].top();
			adj[top].pop();
			if(vis[next]){
				vis[next]=0;
				from[next]=top;
				dfs.push(next);
			}
		}
	}
	while(q--){
		int t;cin>>t;
		if(t-1){
			int i;cin>>i;
			cout<<weight[i-1]<<'\n';
		}else{
			int s;long long x;
			cin>>s>>x;s--;
			x-=val[s];val[s]+=x;
			while(s+1){
				weight[s]+=x;
				s=from[s];
			}
		}
	}
}
