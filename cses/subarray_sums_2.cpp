#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using p=struct p;
struct p{
	int i;
	long long v;
	bool operator<(const p o)const{
		if(v==o.v&&o.i>-1&&i>-1)return i<o.i;
		return v<o.v;
	}
	bool operator==(const p o)const{
		return v==o.v;
	}
	bool operator>(const p o)const{
		if(v==o.v&&o.i>-1&&i>-1)return i>o.i;
		return v>o.v;
	}
};

p mp(long long v,int i){
	p t;t.v=v;t.i=i;
	return t;
}

int main(){
	int n;long long x;
	cin>>n>>x;
	vector<p> a;
	a.reserve(n+1);
	a.push_back(mp(0,0));
	for(int i=0;i<n;i++){
		long long t;cin>>t;
		a.push_back(mp(a[i].v+t,i+1));
	}
	sort(a.begin(),a.end());
	long long ret=0;
	for(int i=0;i<n;i++){
		p xp=mp(a[i].v+x,-1);
		auto lbound=lower_bound(a.begin(),a.end(),xp),
			ubound=upper_bound(a.begin(),a.end(),xp);
		long long b2=ubound-upper_bound(lbound,ubound,mp(a[i].v+x,a[i].i));
		ret+=b2;
	}
	cout<<ret<<'\n';
}
