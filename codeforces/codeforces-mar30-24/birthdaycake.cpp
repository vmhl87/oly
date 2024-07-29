#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

void test_case(){
	int n,x,y;cin>>n>>x>>y;
	int p[x];for(int i=0;i<x;++i)cin>>p[i];
	sort(p,p+x);
	int ret=x-2;
	map<int,int> ev;
	int odd=0;
	for(int i=0;i<x;++i){
		int ni=(i+1==x?0:i+1),dist=p[ni]-p[i];
		dist=(dist<0?dist+n:dist);
		if(dist==2)ret++;
		else if(dist>2){
			if(dist&1)odd+=(dist>>1);
			else ev[(dist>>1)-1]++;
		}
	}
	for(auto &[v,c]:ev){
		if(y<v){
			ret+=y<<1;y=0;
		}
		int rem=min(c,y/v);
		y-=rem*v;ret+=rem*(v<<1|1);
	}
	if(y)ret+=min(odd,y)<<1;
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
