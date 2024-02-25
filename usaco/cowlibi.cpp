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
	return (x-e.x)*(x-e.x)+(y-e.y)*(y-e.y)>(t-e.t)*(t-e.t);
}

int main(){
	long long g,n;cin>>g>>n;
	event events[g];
	for(long long i=0;i<g;i++)
		cin>>events[i].x>>events[i].y>>events[i].t;
	sort(events,events+g);
	long long ret=0;
	for(long long i=0;i<n;i++){
		long long x,y,t;cin>>x>>y>>t;
		if(t<=events[0].t){
			if(disp(x,y,t,events[0]))ret++;
		}else if(t>=events[g-1].t){
			if(disp(x,y,t,events[g-1]))ret++;
		}else{
			event r;r.t=t;
			auto upper=upper_bound(events,events+g,r),
				lower=upper-1;
			if(disp(x,y,t,*upper)||disp(x,y,t,*lower))ret++;
		}
	}
	cout<<ret<<'\n';
}
