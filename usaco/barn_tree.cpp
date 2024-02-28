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
	vector<op> ops;
	ops.reserve(n-1);
	// root the tree arbitrarily - at 0?
	bool vis[n];for(int i=0;i<n;++i)vis[i]=1;
	stack<int> dfs;dfs.push(0);vis[0]=0;
	while(!dfs.empty()){
		int t=dfs.top();
		if(barns[t].adj.empty()){
			// relax along edge and proc
			dfs.pop();
			if(!dfs.empty()){
cout<<"relaxing node "<<t<<" to "<<dfs.top()<<'\n';
				// compare under to w*avg
				op nx;nx.a=t;nx.b=dfs.top();
				nx.m=barns[t].under-barns[t].w*avg;
				if(nx.m<0){
					nx.m=-nx.m;nx.a=dfs.top();nx.b=t;
				}
				if(nx.m!=0)ops.push_back(nx);
				// add weight + hay of previous
				// node onto current one
				int x=dfs.top();
				barns[x].w+=barns[t].w;
				barns[x].under+=barns[t].under;
			}
		}else{
			int x=barns[t].adj.top();
			if(vis[x]){
cout<<"appending node "<<x<<" from "<<t<<'\n';
				vis[x]=0;
				dfs.push(x);
			}
			barns[t].adj.pop();
		}
	}
	cout<<ops.size()<<'\n';
}
