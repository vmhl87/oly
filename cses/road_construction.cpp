// Road Construction  -  https://cses.fi/problemset/result/8996120/
// Pretty trivial with DSU unite

#include <iostream>
#include <stack>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;cin>>n>>m;
	// DSU array stores parent of node and "weight" (size of subtree)
	pair<int,int> dsu[n];
	// infill - each node is root (non connected) and weight is 1
	for(int i=0;i<n;++i){
		dsu[i].first=-1;
		dsu[i].second=1;
	}
	// there are n components initially with max size 1
	int count=n,max=1;
	// process each query
	while(m--){
		// input vertices of road
		int a,b;cin>>a>>b;--a;--b;
		// find root of a and fast unite
		stack<int> touch;
		while(dsu[a].first>-1){
			touch.push(a);
			a=dsu[a].first;
		}
		while(touch.size()){
			dsu[touch.top()].first=a;
			touch.pop();
		}
		// same with b
		while(dsu[b].first>-1){
			touch.push(b);
			b=dsu[b].first;
		}
		while(touch.size()){
			dsu[touch.top()].first=b;
			touch.pop();
		}
		// if belong to different components, unite their components
		// and update count/max
		if(a!=b){
			--count;
			dsu[b].first=a;
			dsu[a].second+=dsu[b].second;
			max=(dsu[a].second>max?dsu[a].second:max);
		}
		// output info
		cout<<count<<' '<<max<<'\n';
	}
}
