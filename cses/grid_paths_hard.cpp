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

//vector<tr> traps;
tr *traps;

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

int nck(int n,int k){
	long long num=1,den=1;
	for(long long i=0;i<k;i++){
		den=(den*(i+1))%M;
		num=(num*(n-i))%M;
	}
	den=inv(den,(long long)M);
	long long ret=(num*den)%M;
	return (int)ret;
}

int choose(int n,int k){
	return nck(n,min(k,n-k));
}

int trav(int xoff,int yoff){
	return choose(xoff+yoff,min(xoff,yoff));
}

int trav(int x1,int y1,int x2,int y2){
	return trav(x2-x1,y2-y1);
}

int main(){
	//for(int i=0;i<=10000;i++)cout<<choose(335433,i)<<'\n';return 0;
	cin>>n>>m;
	traps=new tr[m];
	//traps.reserve(m);
	for(int i=0;i<m;i++){
		cin>>traps[i].x>>traps[i].y;
		//int x,y;tr t;cin>>x>>y;
		//t.x=x;t.y=y;
		//traps.push_back(t);
	}
	sort(traps,traps+m,diag);
	for(int i=0;i<m;i++){
		
	}
	ret=trav(1,1,n,n);
	delete[] traps;
	cout<<ret<<'\n';
}
