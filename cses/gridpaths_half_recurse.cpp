#include <iostream>
#include <set>
#include <string>
using namespace std;
 
set<string> traps;
 
bool trap_at(int x,int y){
	return traps.count(to_string(x)+','+to_string(y));
}
 
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int t,r;cin>>t>>r;
		traps.insert(to_string(t-1)+','+to_string(r-1));
	}
	int p[n],iter=0;
	bool a=true;
	for(int i=0;i<n;i++){
		if(a&&trap_at(0,i))a=false;
		if(a)p[i]=1;
		else p[i]=0;
	}
	while(n>++iter){
		int t;
		for(int i=0;i<n;i++){
			if(i)t=p[i-1];
			else t=0;
			p[i]+=t;
			if(p[i]>1000000007)p[i]%=1000000007;
			if(trap_at(iter,i))p[i]=0;
		}
	}
	cout<<p[n-1]<<'\n';
	return 0;
}
