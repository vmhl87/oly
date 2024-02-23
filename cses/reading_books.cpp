#include <algorithm>
#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	int books[n];
	for(int i=0;i<n;++i)
		cin>>books[i];
	sort(books,books+n);
	int r[n+1];r[0]=0;
	for(int i=0;i<n;++i)
		r[i+1]=r[i]+books[i];
	int target=r[n];
	if(target&1)target/=2;
	else target=target/2-1;
	int i=upper_bound(r,r+n+1,target)-r;
	cout<<r[i]<<'\n';
}
