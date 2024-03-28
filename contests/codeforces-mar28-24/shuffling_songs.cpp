#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define set unordered_set
#define map unordered_map

int optpath(int i,set<int> comp,set<int> adj[]){
	queue<int> ops;
	for(int j:adj[i])if(comp.count(j))ops.push(j);
	int best=1;
	while(ops.size()){
		int j=ops.front();ops.pop();
		comp.erase(j);
		int path=1+optpath(j,comp,adj);
		best=(path>best?path:best);
		comp.insert(j);
	}
	return best;
}

int bestpath(set<int> comp,set<int> adj[]){
	queue<int> ops;
	for(int i:comp)ops.push(i);
	int best=1;
	while(ops.size()){
		int i=ops.front();ops.pop();
		comp.erase(i);
		int path=optpath(i,comp,adj);
		best=(path>best?path:best);
		comp.insert(i);
	}
	return best;
}

void test_case(){
	map<string,set<int>> gen,art;
	int n;cin>>n;
	set<int> adj[n];
	for(int i=0;i<n;++i){
		string g,a;cin>>g>>a;
		gen[g].insert(i);
		art[a].insert(i);
	}
	for(auto &[k,s]:gen){
		while(s.size()){
			int i=*s.begin();s.erase(i);
			for(int j:s){
				adj[j].insert(i);
				adj[i].insert(j);
			}
		}
	}
	for(auto &[k,s]:art){
		while(s.size()){
			int i=*s.begin();s.erase(i);
			for(int j:s){
				adj[j].insert(i);
				adj[i].insert(j);
			}
		}
	}
	queue<int> bfs;
	bool vis[n];for(int i=0;i<n;++i)vis[i]=1;
	int best=0;
	for(int i=0;i<n;++i){
		if(vis[i]){
			bfs.push(i);vis[i]=0;
			set<int> comp;comp.insert(i);
			while(bfs.size()){
				int top=bfs.front();bfs.pop();
				for(int j:adj[top])if(vis[j]){
					vis[j]=0;bfs.push(j);
					comp.insert(j);
				}
			}
			int path=bestpath(comp,adj);
			best=(path>best?path:best);
		}
	}
	cout<<n-best<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
