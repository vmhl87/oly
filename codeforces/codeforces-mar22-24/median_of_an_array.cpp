#include <algorithm>
#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int a[n];for(int i=0;i<n;++i)cin>>a[i];
	sort(a,a+n);
	int mid=(n-1)/2;
	cout<<(lower_bound(a,a+n,a[mid]+1)-a)-mid<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
