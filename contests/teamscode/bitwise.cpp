#include <algorithm>
#include <iostream>
using namespace std;

int nor[62],com[62],off[62],ord[62];
long long center[62];

bool comp_off(int a,int b){
	if(off[a]==off[b])return a<b;
	return off[a]<off[b];
}

long long idx(long long i,int pd=61){
	if(pd<0)return 0;
	int d=ord[pd];
	if(i>=center[d]){
		i-=(com[d]<<pd);
		return idx(i,pd-1)|(1<<pd);
	}else{
		i-=(nor[d]<<pd);
		return idx(i,pd-1);
	}
}

long long procsum(long long a,int i,int b){
	long long c=1LL<<(62-i),lb=(long long)b;
	if(lb>=c)return 1LL<<62;
	lb=(lb<<i)+a;
	if(lb&(1LL<<62))return 1LL<<62;
	return lb;
}

int main(){
	int n,l,r;cin>>n>>l>>r;
	for(int i=0;i<n;++i){
		long long a;cin>>a;
		for(int j=0;j<62;++j){
			nor[j]+=a&1;
			com[j]+=!(a&1);
			a>>=1;
		}
	}
	for(int i=0;i<62;++i){
		ord[i]=i;
		if(nor[i]>com[i]){
			int t=com[i];com[i]=nor[i];
			nor[i]=t;
		}
		off[i]=com[i]-nor[i];
	}
	sort(ord,ord+62,comp_off);
	long long last=0;
	for(int i=0;i<62;++i){
		int d=ord[i];
		center[d]=procsum(last,i,com[d]);
		last=procsum(last,i,nor[d]);
	}
	cout<<idx(r)-idx(l)+1<<'\n';
}
