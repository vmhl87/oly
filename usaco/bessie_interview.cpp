#include <iostream>
#include <queue>
#include <set>
#include <map>
using namespace std;

int main(){
	int n,k;cin>>n>>k;
	priority_queue<long long> q;
	long long farmers[k];
	for(int i=0;i<k;++i,--n){
		cin>>farmers[i];
		q.push(-farmers[i]);
	}
	map<long long,set<long long>> back;
	while(n--){
		long long t,top=q.top();cin>>t;
		q.pop();q.push(top-t);
		back[t-top].insert(-top);
	}
	long long t=-q.top();cout<<t<<'\n';
	set<long long> vis;
	queue<long long> bfs;bfs.push(t);
	while(bfs.size()){
		for(int x:back[bfs.front()])
			if(!vis.count(x)){
				vis.insert(x);
				bfs.push(x);
			}
		bfs.pop();
	}
	for(int i=0;i<k;++i)
		cout<<vis.count(farmers[i]);
	cout<<'\n';
}
