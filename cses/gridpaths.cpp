#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define M 1000000007

int n,m,ret;

typedef struct tr{
	int x;
	int y;
	int gets=0;
} tr;

bool diag(tr a,tr b){
	return a.x+a.y>b.x+b.y;
}

vector<tr> traps;

int inv(long long a,long long p){
	int p2=1,iter=0,pn=(int)p-2;
	long long pa=a,ret=1;
	while(p2<=pn){
		if(pn&(1<<iter))ret=(ret*pa)%p;
		pa=(pa*pa)%p;
		p2*=2;
		iter++;
	}
	return (int)ret;
}

int choose(int n,int k){
	long long num=1,den=1;
	for(long long i=0;i<k;i++){
		den=(den*(i+1))%M;
		num=(num*(n-i))%M;
	}
	int invden=inv(den,(long long)M);
	long long ret=(num*(long long)invden)%M;
	return (int)ret;
}

int trav(int xoff,int yoff){
	return choose(xoff+yoff,min(xoff,yoff));
}

int trav(int x1,int y1,int x2,int y2){
	return trav(x2-x1,y2-y1);
}

int main(){
	cout<<choose(335433,6324)<<'\n';return 0;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y;tr t;cin>>x>>y;
		t.x=x;t.y=y;
		traps.push_back(t);
	}
	sort(traps.begin(),traps.end(),diag);
	if(m-1<traps.size()&&traps[m-1].x==1&&traps[m-1].y==1){
		cout<<0<<'\n';
		return 0;
	}
	for(int i=0;i<m;i++){
		
	}
	ret=trav(1,1,n,n);
	cout<<ret<<'\n';
}
