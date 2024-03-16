#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
	int n,m;cin>>n>>m;
	vector<int> adj[n];
	while(m--){
		int u,v;cin>>u>>v;u--;v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int id[n];
	int vis[n];for(int i=0;i<n;++i)vis[i]=0;
	for(int j=0;j<n;++j)if(!vis[j]){
		id[j]=0;
		queue<int> bfs;bfs.push(j);
		while(!bfs.empty()){
			int t=bfs.front();bfs.pop();
			vis[t]=2;
			bool nx[3]={1,1,1};
			for(int x:adj[t])
				if(vis[x]>1)nx[id[x]]=0;
				else{
					bfs.push(x);
					vis[x]=1;
				}
			for(int i=0;i<3;++i)
				if(nx[i]){
					id[t]=i;
					break;
				}
		}
	}
	for(int i=0;i<n;++i)
		cout<<id[i]+1<<' ';
	cout<<'\n';
}
