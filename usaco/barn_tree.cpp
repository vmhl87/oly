#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

typedef struct{
	int h; // amount of hay in node
	int sum=0; // sum of subtree
	vector<int> adj;
}barn;

barn nb(int i){
	barn t;t.h=i;
	return t;
}

vector<barn> barns;
vector<bool> vis;

//:calcsum
int calcsum(int i){
	if(vis[i])return 0;
	vis[i]=1;
	int ret=0;
	for(int x:barns[i].adj)
		ret+=calcsum(x);
	barns[i].sum=ret;
	return ret;
}

vector<tuple<int,int,int>> orders;

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
	barns.reserve(n);
	orders.reserve(n-1);
	vis.assign(n,0);
	int avg=0;
	// input hay amts
	for(int i=0;i<n;++i){
		int t;cin>>t;
		barns.push_back(nb(t));
		avg+=t;
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
