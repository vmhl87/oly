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
//	for(p i:a)cout<<i.v<<','<<i.i<<' ';cout<<'\n';
	int ret=0;
	for(int i=0;i<n;i++){
		p xp=mp(a[i].v+x,-1);
		int lbound=lower_bound(a.begin(),a.end(),xp)-a.begin(),
			ubound=upper_bound(a.begin(),a.end(),xp)-a.begin();
//		cout<<a[i].v<<','<<a[i].i<<' '<<lbound<<','<<ubound<<':';
		for(int j=lbound;j<ubound;j++){
//			cout<<' '<<a[j].v<<','<<a[j].i;
			if(a[j].i>a[i].i)ret++;
		}
//		cout<<'\n';
	}
	cout<<ret<<'\n';
}
