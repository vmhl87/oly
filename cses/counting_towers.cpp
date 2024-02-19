#include <iostream>
using namespace std;

#define MOD 1000000007

long long ways[1000001][6];
bool fin[1000001][6];

// can go from a to b (ex: can go from 0 0 to 0 1)
bool rel[6][6]={
	{1,1,1,1,1,1},
	{1,1,1,1,0,0},
	{1,1,1,1,0,0},
	{1,1,1,1,0,0},
	{0,0,0,0,1,1},
	{1,1,1,1,1,1}
};

int towerways(int h,int t){
	if(h==1)return 1;
	if(fin[h][t])return ways[h][t];
	int ret=0;
	for(int i=0;i<6;i++)
		// if i can go to t, t can come from i
		if(rel[i][t])
			ret=(ret+towerways(h-1,i))%MOD;
	fin[h][t]=1;ways[h][t]=ret;
//cout<<"height "<<h<<" ending "<<t<<" has "<<ret<<" ways\n";
	return ret;
}

int allways(int h){
	int ret=0;
	ret=(ret+towerways(h,0))%MOD;
	ret=(ret+towerways(h,5))%MOD;
	return ret;
}

void test_case(){
	int n;cin>>n;
	cout<<allways(n)<<'\n';
}

int main(){
	for(int i=0;i<1000001;i++)
		for(int j=0;j<5;j++)
			fin[i][j]=0;
	int t;cin>>t;
	while(t-->0)test_case();
}
