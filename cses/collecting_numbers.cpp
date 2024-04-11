#include <algorithm>
#include <iostream>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;cin>>n;
	pair<int,int> a[n];
	for(int i=0;i<n;++i){
		cin>>a[i].first;
		a[i].second=i;
	}
	sort(a,a+n);
	int last=-1,ret=1;
	for(int i=0;i<n;++i){
		if(a[i].second<last)++ret;
		last=a[i].second;
	}
	cout<<ret<<'\n';
}
