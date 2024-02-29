#include <iostream>
#include <vector>
using namespace std;

typedef struct fenwicktree{
	vector<int> tree;
	int n;
	// i should be 0 indexed
	int sum(int i){
		int ret=0;
		while(i>=0){
			ret+=tree[i];
			// find start of range ending at i, and
			// subtract 1 to find start of next range
			i=(i&(i+1))-1;
		}
		return ret;
	}
	// construct with vector v
	fenwicktree(vector<int> v):tree(v.size()),n(v.size()){
		tree[0]=v[0];
		for(int i=1;i<n;++i)
			// add current element to rest of range
			tree[i]=v[i]+range(i&(i+1),i-1);
	}
	// expects range indices to be 0-indexed
	int range(int l,int r){
		return sum(r)-sum(l-1);
	}
}fenwicktree;

int main(){
	int n;cin>>n;
	vector<int> v(n);
	for(int i=0;i<n;++i)
		cin>>v[i];
	fenwicktree m(v);
	for(int i:m.tree)cout<<i<<' ';
	cout<<'\n';
	for(;;){
		int t;cin>>t;
		if(!t)break;
		int b;cin>>b;
		cout<<m.range(t-1,b-1)<<'\n';
	}
}
