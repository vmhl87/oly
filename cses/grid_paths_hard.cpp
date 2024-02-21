#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define M 1000000007

typedef struct{
	int x;
	int y;
	vector<int> adj;
	bool fin=0;
	long long ret;
}tr;

vector<tr> traps;

bool eq(tr a,tr b){
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}

long long inv(long long a,long long p){
	long long p2=1,iter=0,pn=p-2;
	long long pa=a,ret=1;
	while(p2<=pn){
		if(pn&(1<<iter))ret=(ret*pa)%p;
		pa=(pa*pa)%p;
		p2*=2;
		iter++;
	}
	return ret;
}

long long nck(int n,int k){
	long long num=1,den=1;
	for(long long i=0;i<k;i++){
		den=(den*(i+1))%M;
		num=(num*(n-i))%M;
	}
	den=inv(den,M);
	return (num*den)%M;
}

long long choose(int n,int k){
	return nck(n,min(k,n-k));
}

long long trav(int tr,int x1,int y1,int x2,int y2){
	if(traps[tr].fin)return traps[tr].ret;
	long long ret=choose(x2-x1+y2-y1,x2-x1);
	for(int i:traps[tr].adj){
if(traps[tr].x==1&&traps[tr].y==1)cout<<"computing "<<i<<'\n';
		ret=(ret-choose(traps[i].x-x1+traps[i].y-y1,traps[i].x-x1)*
		trav(i,traps[i].x,traps[i].y,x2,y2))%M;
	}
	ret=(ret+M+M)%M;
	traps[tr].fin=1;traps[tr].ret=ret;
//cout<<" to go from "<<traps[tr].x<<','<<traps[tr].y<<" to end has "<<ret<<" ways\n";
//cout<<"  adj to ";for(int i:traps[tr].adj)cout<<traps[i].x<<','<<traps[i].y<<' ';
//cout<<'\n';
	return ret;
}

int main(){
	long long n,m;
	cin>>n>>m;
	vector<tr> ts;
	ts.reserve(m);
	for(int i=0;i<m;i++){
		int x,y;tr t;cin>>x>>y;
		t.x=x;t.y=y;
		ts.push_back(t);
	}
	sort(ts.begin(),ts.end(),eq);
	traps.reserve(m);
	tr root;root.x=1;root.y=1;
	root.adj.reserve(m);
	int lx=-1,ly=-1,nm=0;
	for(int i=0;i<m;i++){
		if(ts[i].x!=lx||ts[i].y!=ly){
			traps.push_back(ts[i]);
			root.adj.push_back(nm++);
		}
		lx=ts[i].x;ly=ts[i].y;
	}
cout<<"flipped\n";
	traps.push_back(root);
	m=nm;
	for(int i=0;i<m;i++)
		for(int j=i+1;j<m;j++){
			if(traps[i].x>=traps[j].x&&traps[i].y>=traps[j].y)
				traps[j].adj.push_back(i);
			if(traps[i].x<=traps[j].x&&traps[i].y<=traps[j].y)
				traps[i].adj.push_back(j);
		}
cout<<"calculated adj\n";
	long long ret=trav(m,1,1,n,n);
	cout<<ret<<'\n';
}
