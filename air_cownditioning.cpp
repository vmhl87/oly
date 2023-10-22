#include <iostream>
#include <algorithm>
using namespace std;

#define DEBUG 1

struct event{
	int type;
	int cell;
	int amount=0;
	int cost=0;
	int id=0;
};

bool comp_events(struct event a, struct event b){
	return a.cell<b.cell;
}

int main(){
	int n,m,mincost=0;cin>>n>>m;
	struct event events[n+n+m+m];
	for(int i=0;i<n;i++){
		int s,e,c;cin>>s>>e>>c;
		events[i*2].type=2;events[i*2].cell=s*4+2;events[i*2].amount=c;
		events[i*2+1].type=3;events[i*2+1].cell=e*4-2;
	}
	for(int i=n;i<n+m;i++){
		int s,e,c,m;cin>>s>>e>>c>>m;mincost+=m;
		events[i*2].type=0;events[i*2].cell=s*4-1;events[i*2].amount=c;
		events[i*2].cost=m;events[i*2].id=i-n;
		events[i*2+1].type=1;events[i*2+1].cell=e*4+1;
		events[i*2+1].amount=c;events[i*2+1].id=i-n;
	}
	sort(events,events+n+n+m+m,comp_events);
	if(DEBUG)for(struct event e:events){
		if(e.type==0)cout<<"aircon "<<e.id<<" starts "<<e.amount<<'\n';
		if(e.type==1)cout<<"aircon "<<e.id<<" stops "<<e.amount<<'\n';
		if(e.type==2)cout<<"cow starts "<<e.amount<<'\n';
		if(e.type==3)cout<<"cow stops\n";
	}
	int target=1;for(int i=0;i<m;i++)target*=2;
	for(int i=0;i<target;i++){
		int cost=0,cool=0,need=0;
		for(struct event e:events){
			if(e.type>1||(i&(1<<e.id))){
				if(e.type==0){
					cool+=e.amount;cost+=e.cost;
				}else if(e.type==1)cool-=e.amount;
				else if(e.type==2)need=e.amount;
				else need=0;
				if(cool<need||cost>mincost){
					cost=0;break;
				}
			}
		}
		if(cost>0&&cost<mincost)mincost=cost;
	}
	cout<<mincost<<'\n';
	return 0;
}
