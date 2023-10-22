#include <iostream>
#include <map>
using namespace std;

int main(){
	int n,q;cin>>n>>q;
	int arr[n];
	for(int i=0;i<n;i++)cin>>arr[i];
	while(q-->0){
		int x,y;cin>>x>>y;
		map<int,int> counts;
		for(int i=x-1;i<y;i++){
			if(counts.find(arr[i])==counts.end())counts[arr[i]]=1;
			else counts[arr[i]]++;
		}
		int ret=-1,half=(y-x+1)/2;
		for(auto k:counts){
			if(k.second>half){
				ret=k.first;break;
			}
		}
		cout<<ret<<'\n';
	}
	return 0;
}
