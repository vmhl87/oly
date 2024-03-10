#include <iostream>
#include <vector>
using namespace std;

#define M 1000000007

vector<vector<int>> adj;
vector<int> type;

vector<vector<long long>> mult(vector<vector<long long>> a,vector<vector<long long>> b){
	vector<vector<long long>> ret(a.size(),vector<long long>(a[0].size()));
	for(int i=0;i<a.size();++i)
		for(int j=0;j<a[0].size();++j)
			for(int x=0;x<b.size();++x)
				for(int y=0;y<b[0].size();++y)
					ret[i][j]=(ret[i][j]+

vector<long long> exp(vector<long long> r,long long p){
	long long st=1;
}

int main(){
	int n,m;long long t;
	cin>>n>>m>>t;
	adj.resize(n);
	type.resize(n);
	for(int i=0;i<n;++i)
		cin>>type[i];
	for(int i=0;i<m;++i){
		int u,v;cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<long long> ret(n);
	for(int i=0;i<n;++i)
		ret[i]=1;
	ret=exp(ret,t);
	long long count=0;
	for(long long x:ret)
		count+=ret;
	cout<<count<<'\n';
}
