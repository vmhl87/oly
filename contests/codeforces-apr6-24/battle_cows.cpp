#include <iostream>
using namespace std;

int tryswap(int best,int n,int *a,int i,int j){
	int t=a[i];a[i]=a[j];a[j]=t;
	int count=0,max=0;
	for(int x=0;x<n;++x){
		if(x<j){
			max=(a[x]>max?a[x]:max);
		}else if(x==j){
			if(j==0)continue;
			if(a[j]>max)count=1;
			else break;
		}else{
			if(a[x]>a[j])break;
			++count;
		}
	}
	t=a[i];a[i]=a[j];a[j]=t;
	return count>best?count:best;
}

void test_case(){
	int n,k;cin>>n>>k;k--;
	int a[n];for(int i=0;i<n;++i)cin>>a[i];
	int best=0;
	best=tryswap(best,n,a,k,0);
	best=tryswap(best,n,a,k,1);
	for(int i=0;i<k;++i){
		if(a[i]>a[k]){
			best=tryswap(best,n,a,k,i);
			break;
		}
	}
	cout<<best<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
