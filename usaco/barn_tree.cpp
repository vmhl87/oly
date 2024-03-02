#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

typedef struct{
	long long h; // amount of hay in node
	long long sum=0; // sum of subtree
	vector<int> adj;
}barn;

vector<barn> barns;
vector<bool> vis;

//:calcsum
long long calcsum(int i){
	if(vis[i])return 0;
	vis[i]=1;
	long long ret=barns[i].h;
	for(int x:barns[i].adj)
		ret+=calcsum(x);
	barns[i].sum=ret;
	return ret;
}

vector<tuple<int,int,long long>> orders;

//:distrib
void distribute(int i,int pre){
	// if(!vis[i])return;
	// vis[i]=0;
	for(int x:barns[i].adj)if(x!=pre){
		if(barns[x].sum>=0)
			distribute(x,i);
		if(barns[x].sum>0)
			orders.emplace_back(x,i,barns[x].sum);
	}
	for(int x:barns[i].adj)if(x!=pre){
		if(barns[x].sum<0)
			orders.emplace_back(i,x,-barns[x].sum);
		if(barns[x].sum<0)
			distribute(x,i);
	}
}

//:main
int main(){
	int n;cin>>n;
	barns.resize(n);
	orders.reserve(n-1);
	vis.resize(n);
	long long avg=0;
	// input hay amts
	for(int i=0;i<n;++i){
		cin>>barns[i].h;
		avg+=barns[i].h;
	}
	avg/=n;
	// normalize hay counts
	for(int i=0;i<n;++i)
		barns[i].h-=avg;
	// calculate adjacencies
	for(int i=1;i<n;++i){
		int a,b;cin>>a>>b;
		a--;b--;
		barns[a].adj.push_back(b);
		barns[b].adj.push_back(a);
	}
	calcsum(0);
	distribute(0,-1);
	cout<<size(orders)<<'\n';
	for(auto [a,b,v]:orders)
		cout<<a+1<<' '<<b+1<<' '<<v<<'\n';
}
