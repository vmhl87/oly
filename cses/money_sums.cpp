// Money Sums  -  https://cses.fi/problemset/task/1745/
// knapsack dp. not much else to say

#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	int xs[n],sum=0;
	for(int i=0;i<n;++i){
		cin>>xs[i];
		sum+=xs[i];
	}
	bool can[sum+1];
	for(int i=1;i<=sum;++i)can[i]=0;
	can[0]=1;
	for(int i:xs)
		for(int j=sum-i;j>=0;--j)
			can[j+i]|=can[j];
	bool f=0;
	int count=0;
	for(int i=1;i<=sum;++i)if(can[i])count++;
	cout<<count<<'\n';
	for(int i=1;i<=sum;++i)if(can[i]){
		if(f)cout<<' ';f=1;
		cout<<i;
	}
	cout<<'\n';
}
