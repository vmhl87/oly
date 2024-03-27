#include <unordered_set>
#include <iostream>
#include <vector>
using namespace std;

typedef struct{
	unordered_set<int> adj;
	int count=1;
}house;

typedef struct segtree{
	vector<int> tree;
	vector<house> houses;
	int n;
	bool possible(int i){
		i=tree[i];
		if(i<0)return 0;
		if(houses[i].adj.size()!=1)return 0;
		if(houses[i].count>houses[*houses[i].adj.begin()].count)return 0;
		return 1;
	}
	void prop(int i){
		if(possible(i<<1))tree[i]=tree[i<<1];
		else if(possible(i<<1|1))tree[i]=tree[i<<1|1];
		else tree[i]=-1;
	}
	segtree(int len):tree(len*2),houses(len),n(len){
		for(int i=0;i<n;++i)tree[i+n]=i;
		for(int i=1;i<n;++i){
			int u,v;cin>>u>>v;u--;v--;
			houses[u].adj.insert(v);
			houses[v].adj.insert(u);
		}
		for(int i=n-1;i>0;--i)prop(i);
	}
	int top(){
		return tree[1];
	}
	void relax(int i){
		int other=*houses[i].adj.begin();
		houses[other].count+=houses[i].count;
		houses[i].adj.clear();
		houses[other].adj.erase(i);
		i+=n;other+=n;
		tree[i]=-1;
		i>>=1;other>>=1;
		while(i){
			prop(i);
			i>>=1;
		}
		while(other){
			prop(other);
			other>>=1;
		}
	}
}segtree;

int main(){
	int n;cin>>n;
	segtree m(n);
	for(int i=1;i<n;++i){
		int top=m.top();
		if(top<0){
			cout<<"NO\n";
			return 0;
		}
		// cout<<"relaxing "<<top+1<<'\n';
		m.relax(top);
	}
	cout<<"YES\n";
}
