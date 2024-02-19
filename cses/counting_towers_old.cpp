#include <iostream>
#include <stdio.h>
using namespace std;

#define MOD 1000000007

long long ways[1000001][2];
bool fin[1000001][2];

long long exp(int h){
	if(fin[h][0])return ways[h][0];
	long long ret=1;
	long long p=3,i=0;
	while((1<<i)<=h){
		if((1<<i)&h)ret=(ret*p)%MOD;
		p=(p*p)%MOD;i++;
	}
	fin[h][0]=1;ways[h][0]=ret;
	return ret;
}

long long towerways(int h){
	if(fin[h][1])return ways[h][1];
	for(int i=0;i<h;i++){
		if(!fin[i][1]){
			fin[i][1]=1;
			ways[i][1]=1;
			for(int j=1;j<i;j++){
				ways[i][1]=(ways[i][1]+ways[j][1]*(1+exp(i-j-1)))%MOD;
			}
			ways[i][1]=(ways[i][1]+exp(i-1))%MOD;
		}
	}
	long long ret=1;
	for(int i=1;i<h;i++){
		ret=(ret+ways[h-i][1]*(1+exp(i-1)))%MOD;
	}
	ret=(ret+exp(h-1))%MOD;
	fin[h][1]=1;ways[h][1]=ret;
	return ret;
}

void test_case(){
	int n;//cin>>n;
	scanf("%d",&n);
	cout<<towerways(n)<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
