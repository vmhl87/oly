#include <algorithm>
#include <iostream>
using namespace std;

typedef struct ev{
	long long loc,diff;
	bool operator<(const ev o)const{
		if(loc==o.loc)return diff<o.diff;
		return loc<o.loc;
	}
}ev;

int main(){
	long long l,n;cin>>l>>n;
	long long maxtime=0;
	ev ships[n*2];
	for(int i=0;i<n;++i){
		long long t,x,y,w;
		cin>>t>>x>>y>>w;
		if(t>maxtime)maxtime=t;
		x+=t;
		// to account for the length of tom's ship,
		// we can cheat and instead increase the length
		// of the other ships and advance their starts,
		// because the result is "basically the same".
		x-=l;w+=l;
		// notice that diagonal projections are identical
		// to subtracting y from x
		x-=y;
		// because ships can't touch at all we have to add and
		// subtract 1 to the ends
		ships[i].loc=x-1;
		ships[i].diff=1;
		ships[i+n].loc=x+w+1;
		ships[i+n].diff=-1;
	}
	for(ev &i:ships)i.loc-=maxtime;
	sort(ships,ships+n*2);
	// do the sweep line stuff!
	long long col=0;
	for(ev i:ships){
		col+=i.diff;
		if(col==0&&i.loc>=0){
			cout<<i.loc<<'\n';
			return 0;
		}
	}
	cout<<ships[n*2-1].loc<<'\n';
}
