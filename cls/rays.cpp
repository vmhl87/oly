#include <iostream>
#include <set>
#include <string>
using namespace std;

int gcd(int x,int y){
	if(y==0)return x;
	return gcd(y,x%y);
}

int main(){
	int N,x,y;
	cin>>N;
	set<string> pts;
	for(int i=0;i<N;i++){
		cin>>x>>y;
		int g=gcd(abs(x),abs(y));
		if(g>0)pts.insert(to_string(x/g)+'/'+to_string(y/g));
	}	
	cout<<pts.size()<<'\n';
	return 0;
}
