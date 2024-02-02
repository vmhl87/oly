#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct{
	int i;
	int v;
}p;

bool comp(p a,p b){
	if(a.v==b.v)return a.i<b.i;
	return a.v<b.v;
}

int main(){
	ifstream cin("sort.in");
	ofstream cout("sort.out");
	int n,ret=0,t;cin>>n;
	p a[n];
	for(int i=0;i<n;i++){
		cin>>a[i].v;a[i].i=i;
	}
	sort(a,a+n,comp);
	for(int i=0;i<n;i++){
		int diff=a[i].i-i;
		if(diff>ret)ret=diff;
	}
	cout<<ret+1<<'\n';
}
