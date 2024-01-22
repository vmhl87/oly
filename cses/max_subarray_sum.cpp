#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	long long rsum[n+1];
	rsum[0]=0;
	long long sum=0,t;
	for(int i=0;i<n;i++){
		cin>>t;
		sum+=t;
		rsum[i+1]=sum;
	}
	long long max=0,diff;
	bool nset=1;
	int p1=0,p2=0;
	while(p1<n+1){
		if(rsum[p1]>rsum[p1+1])p2++;
		p1++;
		if(p1==p2)continue;
		diff=rsum[p1]-rsum[p2];
		if(diff>max||nset){max=diff;nset=0;}
	}
	while(p2<n+1){
		p2++;
		if(p1==p2)continue;
		diff=sum-rsum[p2];
		if(diff>max)max=diff;
	}
	cout<<max<<'\n';
}
