#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n,max=0;cin>>n;
	int v[n];
	for(int i=0;i<n;i++)cin>>v[i];
	sort(v,v+n);
	long long ret=0;
	for(int i:v){
		if(i<=max){
			ret+=max+1-i;
			max++;
		}else max=i;
	}
	cout<<ret<<'\n';
}
