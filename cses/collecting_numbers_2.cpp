#include <iostream>
using namespace std;

int main(){
	int n,m;cin>>n>>m;
	int x[n],p[n];
	for(int i=0;i<n;++i){
		int j;cin>>j;
		x[j-1]=i;
		p[i]=j-1;
	}
	int rounds=1;
	for(int i=1;i<n;++i){
		if(x[i-1]>x[i])++rounds;
	}
	while(m--){
		int a,b;cin>>a>>b;--a;--b;
		int c=p[a],d=p[b];
		int cur=0;
		if(c&&x[c-1]>x[c])++cur;
		if(c<n-1&&x[c]>x[c+1])++cur;
		if(d&&x[d-1]>x[d])++cur;
		if(d<n-1&&x[d]>x[d+1])++cur;
		if(c==d-1&&x[c]>x[d])--cur;
		if(d==c-1&&x[d]>x[c])--cur;
		int t=p[a];p[a]=p[b];p[b]=t;
		t=x[c];x[c]=x[d];x[d]=t;
		int now=0;
		if(c&&x[c-1]>x[c])++now;
		if(c<n-1&&x[c]>x[c+1])++now;
		if(d&&x[d-1]>x[d])++now;
		if(d<n-1&&x[d]>x[d+1])++now;
		if(c==d-1&&x[c]>x[d])--now;
		if(d==c-1&&x[d]>x[c])--now;
		rounds+=now-cur;
		cout<<rounds<<'\n';
	}
}
