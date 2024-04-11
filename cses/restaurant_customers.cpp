#include <algorithm>
#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	pair<int,int> a[n<<1];
	for(int i=0;i<n;++i){
		cin>>a[i].first>>a[i+n].first;
		a[i].second=1;a[i+n].second=-1;
	}
	sort(a,a+(n<<1));
	int count=0,max=0;
	for(pair<int,int> x:a){
		count+=x.second;
		max=(count>max?count:max);
	}
	cout<<max<<'\n';
}
