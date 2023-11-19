#include <iostream>
#include <set>
#include <string>
using namespace std;

int count=0,n,m;
set<string> traps;

bool trap_at(int x,int y){
	return traps.count(to_string(x)+','+to_string(y));
}

void recurse(int i,int left,int x,int y){
	if(x==n-1&&y==n-1){
		cout<<"boop\n";
		count++;
		if(count>=1000000007)count=0;
		return;
	}
	if(y<n-1&&left>0)if(!trap_at(x,y+1)){
		cout<<x<<','<<y<<"->"<<x<<','<<y+1<<'\n';
		recurse(i+1,left-1,x,y+1);
	}else cout<<x<<','<<y<<"->"<<x<<','<<y+1<<"uh oh!\n";
	if(x<n-1)if(!trap_at(x+1,y)){
		cout<<x<<','<<y<<"->"<<x+1<<','<<y<<'\n';
		recurse(i+1,left,x+1,y);
	}else cout<<x<<','<<y<<"->"<<x+1<<','<<y<<"uh oh!\n";
}

int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int t,r;cin>>t>>r;
		traps.insert(to_string(t-1)+','+to_string(r-1));
	}
	recurse(0,n,0,0);
	cout<<count<<'\n';
	return 0;
}
