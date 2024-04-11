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

namespace seg{
	vector<pair<int,int>> tree;
	int n;
	void prop(int i){
		if(tree[i<<1].first==tree[i<<1|1].first){
			tree[i].first=tree[i<<1].first;
			tree[i].second=tree[i<<1].second+
				tree[i<<1|1].second;
		}else if(tree[i<<1].first>tree[i<<1|1].first){
			tree[i].first=tree[i<<1].first;
			tree[i].second=tree[i<<1].second;
		}else{
			tree[i].first=tree[i<<1|1].first;
			tree[i].second=tree[i<<1|1].second;
		}
	}
	void init(int l,int g){
		n=l;
		tree.resize(l*2,make_pair(g,1));
		for(int i=n-1;i>0;--i)prop(i);
	}
	bool set(int i,int v){
		i+=n;
		pair<int,int> o=tree[1];
		int oi=i;bool was=tree[i].first==o.first;
		tree[i].first+=v;
		while(i){
			i>>=1;prop(i);
		}
		if(o.second!=tree[1].second)return 1;
		if(o.first!=tree[1].first)
			return was^(tree[1].first==tree[oi].first);
		return 0;
	}
}

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
	seg::init(index+1,g);
	int ret=0;
	for(event e:events)
		if(seg::set(e.cow,e.change))ret++;
	cout<<ret<<'\n';
}
