#include <iostream>
#include <set>
#include <string>
using namespace std;

set<string> traps;

bool trap_at(int x,int y){
	return traps.count(to_string(x)+','+to_string(y));
}

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			char c;cin>>c;
			if(c=='*')traps.insert(to_string(i)+','+to_string(j));
		}
	}
	int p[n];
	bool a=true;
	for(int i=0;i<n;i++){
		if(a&&trap_at(0,i))a=false;
		if(a)p[i]=1;
		else p[i]=0;
	}
	for(int iter=1;iter<n;iter++){
		int t;
		for(int i=0;i<n;i++){
			if(i)p[i]+=p[i-1];
			p[i]%=1000000007;
			if(trap_at(iter,i))p[i]=0;
		}
	}
	cout<<p[n-1]<<'\n';
	return 0;
}
