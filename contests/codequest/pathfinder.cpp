#include <iostream>
using namespace std;

long long fill(bool map[],bool mask[],long long n,long long x,long long y){
	if(x==n-1&&y==n-1)return 1;
	long long ret=0;
	mask[x*n+y]=1;
	if(x>0&&!mask[x*n-n+y]&&map[x*n-n+y])
		ret+=fill(map,mask,n,x-1,y);
	if(y>0&&!mask[x*n+y-1]&&map[x*n+y-1])
		ret+=fill(map,mask,n,x,y-1);
	if(x<n-1&&!mask[x*n+n+y]&&map[x*n+n+y])
		ret+=fill(map,mask,n,x+1,y);
	if(y<n-1&&!mask[x*n+y+1]&&map[x*n+y+1])
		ret+=fill(map,mask,n,x,y+1);
	mask[x*n+y]=0;
	return ret;
}

void test_case(){
	long long n;cin>>n;
	bool map[n*n],mask[n*n];
	for(long long i=0;i<n;++i)
		for(long long j=0;j<n;++j){
			char x;cin>>x;
			map[i*n+j]=(x=='1');
			mask[i*n+j]=0;
		}
	long long ret=fill(map,mask,n,0,0);
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
