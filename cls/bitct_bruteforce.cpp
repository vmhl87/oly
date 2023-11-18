#include <iostream>
using namespace std;

int main(){
	long long n,k,ret=0;
	short r=0;
	cin>>n>>k;
	for(long long i=1;i<=n;i*=k)r++;
	short val[r];
	bool are_1[r];
	for(short i=0;i<r;i++){val[i]=0;are_1[i]=false;}
	for(long long i=0;i<n;i++){
		val[0]++;short e=0;if(val[0]==1)ret++;
		while(val[e]==k){
			val[e]=0;e++;val[e]++;
			if(val[e]==1)are_1[e]=true;
			else are_1[e]=false;
		}
		for(short j=0;j<r;j++)if(are_1[j])ret++;
		if(i%1000000000<1)cout<<i<<'\n';
	}
	cout<<ret<<'\n';
}
