#include <iostream>
#include <stack>
using namespace std;

int main(){
	int n;cin>>n;
	int head;
	pair<stack<int>,int> adj[n];
	for(int i=0;i<n;++i){
		int t;cin>>t;
		if(t)adj[t-1].first.push(i);
		else head=i;
	}
	for(int i=0;i<n;++i)
		adj[i].second=adj[i].first.size();
	stack<int> dfs;
	int in=0,best=0;
	dfs.push(head);
	while(!dfs.empty()){
		int t=dfs.top();
		if(adj[t].first.empty()){
			int bal=1+(in-1)/dfs.size();
			if(bal>best)best=bal;
			in-=adj[t].second;
			dfs.pop();
		}else{
			int next=adj[t].first.top();
			adj[t].first.pop();
			dfs.push(next);in++;
		}
	}
	cout<<best<<'\n';
}
