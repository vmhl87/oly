#include <iostream>
#include <stack>
using namespace std;

int main(){
	int n,m;cin>>n>>m;
	stack<int> adj[n];
	for(int i=0;i<m;i++){
		int a,b;cin>>a>>b;a--;b--;
		adj[a].push(b);
		adj[b].push(a);
	}
	int teams[n];for(int i=0;i<n;i++)teams[i]=0;
	int ptr=0;
	stack<int> dfs;
	while(ptr<n){
		if(!teams[ptr]){
			teams[ptr]=1;
			dfs.push(ptr);
			while(!dfs.empty()){
				int x=dfs.top();
				if(adj[x].empty())dfs.pop();
				else{
					int y=adj[x].top();
					if(teams[y]){
						if(teams[y]==teams[x])goto im;
						adj[x].pop();
					}else{
						teams[y]=3-teams[x];
						adj[x].pop();
						dfs.push(y);
					}
				}
			}
		}
		ptr++;
	}
	for(int i=0;i<n;i++)
		cout<<teams[i]<<' ';
	cout<<'\n';
	return 0;
im:
	cout<<"IMPOSSIBLE\n";
}
