#include <unordered_set>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct{
	unordered_set<int> adj;
	int count=1;
}house;

typedef struct sol{
	queue<int> leaf;
	vector<bool> leafed;
	vector<house> houses;
	int n;
	bool is_leaf(int i){
		return houses[i].adj.size()==1;
	}
	bool possible(int i){
		return houses[i].count<=houses[*houses[i].adj.begin()].count;
	}
	void add_leaf(int i){
		if(leafed[i])return;
		leafed[i]=1;
		leaf.push(i);
	}
	sol(int len):leafed(len),houses(len),n(len){
		for(int i=1;i<n;++i){
			int u,v;cin>>u>>v;u--;v--;
			houses[u].adj.insert(v);
			houses[v].adj.insert(u);
		}
		for(int i=0;i<n;++i){
			if(is_leaf(i))add_leaf(i);
		}
	}
	int top(){
		int l=leaf.size();
		for(int i=0;i<l;++i){
			int top=leaf.front();
			leaf.pop();
			if(possible(top))return top;
			else leaf.push(top);
		}
		return -1;
	}
	void relax(int i){
		int other=*houses[i].adj.begin();
		houses[other].count+=houses[i].count;
		houses[i].adj.clear();
		houses[other].adj.erase(i);
		if(is_leaf(other))add_leaf(other);
		for(int j:houses[other].adj){
			if(is_leaf(j))add_leaf(j);
		}
	}
}sol;

int main(){
	int n;cin>>n;
	sol m(n);
	for(int i=1;i<n;++i){
		int top=m.top();
		if(top<0){
			cout<<"NO\n";
			return 0;
		}
		// cout<<"relaxing "<<top+1<<" -> "<<(*m.houses[top].adj.begin())+1<<'\n';
		m.relax(top);
	}
	cout<<"YES\n";
}
