#include <iostream>
#include <stack>
using namespace std;

int main(){
	int n,m;cin>>n>>m;
	stack<int> adj[n];
	for(int i=0;i<m;i++){
		int a,b;cin>>a>>b;
		a--;b--;
		adj[a].push(b);
		adj[b].push(a);
	}
	stack<int> dfs;
	stack<int> roots;
	int ptr=0;
	bool vis[n];for(int i=0;i<n;i++)vis[i]=1;
	while(ptr<n){
		roots.push(ptr);
		dfs.push(ptr);
		vis[ptr]=0;
		while(!dfs.empty()){
			int x=dfs.top();
			if(adj[x].empty())dfs.pop();
			else{
				vis[adj[x].top()]=0;
				dfs.push(adj[x].top());
				adj[x].pop();
			}
		}
		while(!vis[ptr]&&ptr<n)ptr++;
	}
	cout<<roots.size()-1<<'\n';
	int t=roots.top();roots.pop();
	while(!roots.empty()){
		cout<<t+1<<' '<<roots.top()+1<<'\n';
		roots.pop();
	}
}
