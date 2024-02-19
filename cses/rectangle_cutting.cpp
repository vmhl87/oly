#include <iostream>
using namespace std;

int cuts[501][501];
bool fin[501][501];

int mincut(int a,int b){
	if(a<b)return mincut(b,a);
	if(a%b==0)return a/b-1;
	if(fin[a][b])return cuts[a][b];
	int cmin=-1;
	for(int i=1;i<=a/2;i++){
		int res=mincut(i,b)+1+mincut(a-i,b);
		if(res<cmin||cmin<0)cmin=res;
	}
	for(int i=1;i<=b/2;i++){
		int res=mincut(a,i)+1+mincut(a,b-i);
		if(res<cmin||cmin<0)cmin=res;
	}
	fin[a][b]=1;
	cuts[a][b]=cmin;
	return cmin;
}

int main(){
	int a,b,c;cin>>a>>b;
	cout<<mincut(a,b)<<'\n';
}
