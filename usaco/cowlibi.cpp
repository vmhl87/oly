#include <algorithm>
#include <iostream>
using namespace std;

typedef struct event{
	long long x;
	long long y;
	long long t;
	bool operator<(const event o)const{
		return t<o.t;
	}
	bool operator==(const event o)const{
		return t==o.t;
	}
	bool operator>(const event o)const{
		return t>o.t;
	}
}event;

bool disp(long long x,long long y,long long t,event e){
	long long timedf=e.t-t;
	timedf*=timedf;
	long long nec=(e.x-x)*(e.x-x);
	nec-=timedf;
	nec+=(e.y+y)*(e.y+y);
	if(nec>0)return 1;
	return 0;
}

int main(){
	long long g,n;cin>>g>>n;
	event events[g];
	for(long long i=0;i<g;i++)
		cin>>events[i].x>>events[i].y>>events[i].t;
	sort(events,events+g);
	long long ret=0;
	for(long long i=0;i<n;i++){
//cout<<ret<<'\n';
		long long x,y,t;cin>>x>>y>>t;
		if(t<=events[0].t){
//cout<<"comparing cow "<<i+1<<" with event "<<0<<'\n';
			if(disp(x,y,t,events[0]))ret++;
		}else if(t>=events[g-1].t){
//cout<<"comparing cow "<<i+1<<" with event "<<g-1<<'\n';
			if(disp(x,y,t,events[g-1]))ret++;
		}else{
			event r;r.t=t;
			event r2;r2.t=t-1;
			auto upper=upper_bound(events,events+g,r),
				lower=upper-1;
//cout<<"comparing cow "<<i+1<<" with events "<<upper-events<<','<<lower-events<<'\n';
			if(disp(x,y,t,*upper)||disp(x,y,t,*lower))ret++;
		}
	}
	cout<<ret<<'\n';
}
