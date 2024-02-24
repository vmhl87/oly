#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

typedef struct{
	int day;
	int cow;
	int change;
}event;

bool comp_events(event a,event b){
	return a.day<b.day;
}

typedef struct segtree{
	vector<pair<int,int>> tree;
	int n;
	void proc(int i){
		if(tree[i<<1].first>tree[(i<<1)+1].first){
			tree[i].first=tree[i<<1].first;
			tree[i].second=tree[i<<1].second;
		}else if(tree[i<<1].first<tree[(i<<1)+1].first){
			tree[i].first=tree[(i<<1)+1].first;
			tree[i].second=tree[(i<<1)+1].second;
		}else{
			tree[i].first=tree[i<<1].first;
			tree[i].second=tree[i<<1].second+
				tree[(i<<1)+1].second;
		}
	}
	segtree(int l,int g):tree(l*2,make_pair(g,1)){
		n=l;
		for(int i=n-1;i>0;--i)
			proc(i);
	}
	bool set(int i,int v){
		i+=n;int oi=i;
		int om=tree[1].first,oc=tree[1].second;
		bool was=tree[i].first==om;
		tree[i].first+=v;i>>=1;
		while(i){
			proc(i);
			i>>=1;
		}
		if(oc!=tree[1].second)return 1;
		if(om!=tree[1].first)
			return was^(tree[1].first==tree[oi].first);
		return 0;
	}
}segtree;

int main(){
	ifstream cin("measurement.in");
	ofstream cout("measurement.out");
	int n,g;cin>>n>>g;
	event events[n];
	map<int,int> indexmap;
	int index=0;
	for(int i=0;i<n;++i){
		int day,cow,change;
		char t;cin>>day>>cow>>t>>change;
		if(!indexmap.count(cow)){
			indexmap[cow]=index;
			index++;
		}
		events[i].day=day;events[i].cow=indexmap[cow];
		if(t=='-')events[i].change=-change;
		else events[i].change=change;
	}
	sort(events,events+n,comp_events);
	segtree m(index+1,g);
	int ret=0;
	for(event e:events)
		if(m.set(e.cow,e.change))ret++;
	cout<<ret<<'\n';
}
