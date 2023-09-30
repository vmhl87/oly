#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct cow{
	int i;
	bool spots;
};

bool compCows(struct cow a, struct cow b){
	return a.i<b.i;
}

int main(){
	int n,a,b;
	cin>>n>>a>>b;
	struct cow cows[n];
	for(int i=0;i<n;i++){
		char c;int t;cin>>c;
		if(c=='S'){
			cin>>t;cows[i].spots=true;
		}else{
			cin>>c;cin>>t;cows[i].spots=false;
		}
		cows[i].i=t;
	}
	sort(cows,cows+n,compCows);
	
	int start=-1;
	int end=n;
	int ret=0;
	for(int i=0;i<n-1;i++){
		if(cows[i].i<a&&cows[i+1].i>a){
			start=i;break;
		}
	}
	for(int i=start+1;i<n;i++){
		if(cows[i].i>b&&cows[i-1].i<b){
			end=i;break;
		}
	}
	if(start==-1)ret+=cows[0].spots?cows[0].i-a:0;
	else{
		int sum=cows[start].i+cows[start+1].i;
		if(sum%2==0&&sum/2>=a){
			sum/=2;
			if(cows[start].spots&&!cows[start+1].spots)ret++;
		}else{
			sum=(sum+1)/2;
		}
		if(a>sum){
			if(cows[start+1].spots)ret+=cows[start+1].i-a;
		}else{
			if(a<sum&&cows[start].spots)ret+=sum-a;
			if(cows[start+1].spots)ret+=cows[start+1].i-sum;
		}
	}
	if(end==n)ret+=cows[n-1].spots?b-cows[n-1].i:0;
	else{
		int sum=cows[end].i+cows[end-1].i;
		if(sum%2==0&&sum/2<=b){
			sum/=2;
			if(!cows[end].spots&&cows[end-1].spots)ret++;
		}else{
			sum=(sum+1)/2;
		}
		if(b<sum){
			if(cows[end-1].spots)ret+=b-cows[end-1].i;
		}else{
			if(cows[end].spots)ret+=b-sum+1;
			if(cows[end-1].spots)ret+=sum-cows[end-1].i-1;
		}
	}
	for(int i=start+1;i<end-1;i++){
		int s=cows[i].spots?1:0;
		s+=cows[i+1].spots?1:0;
		if(s==1){
			int t=cows[i+1].i-cows[i].i-1;
			if(t%2==0)t/=2;
			else t=(t+1)/2;
			ret+=t;
		}
		if(s==2)ret+=cows[i+1].i-cows[i].i-1;
		if(cows[i].spots)ret++;
	}
	if(cows[end-1].spots)ret++;
	cout<<ret<<'\n';
	
	return 0;
}
