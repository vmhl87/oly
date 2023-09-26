#include <iostream>
using namespace std;

int main(){
	long long n,k,r=1,i=0;
	cin>>n>>k;
	while(r<=n){r*=k;i++;}
	long long count[i],at[i];
	for(long long j=0;j<i;j++){count[j]=0;at[j]=0;}
	i=0;
	r=1;while(r<n){at[i]=r;i++;r*=k;}
	r=i;
	for(i=0;i<=n;i++){
		for(long long j=0;j<r;j++)
			if((i/at[j])%k==1)count[j]++;
		if(i%10000000<1)cout<<i<<'\n';
	}
	i=0;
	for(long long j=0;j<r;j++)i+=count[j];
	cout<<i<<'\n';
	return 0;
}
