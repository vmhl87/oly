#include <iostream>
using namespace std;

int main(){
	int n,k;cin>>n>>k;
	int val=1,cit=1;
	int first=-1,second;
	int vis[n];
	for(int i=0;i<n;++i)
		vis[i]=0;
	for(;;){
		if(cit==k){
			if(first+1){
				second=val;
				break;
			}
			first=val;
		}
		cit=(cit+cit)%n;
		val=(val+cit)%(n+1);
		if(vis[cit]>2){
			cout<<"NO\n";
			return 0;
		}
		vis[cit]++;
	}
	second-=first;
	if(second<=0)second+=(n+1);
	if((n+1)%second>0||second==1)
		cout<<"YES\n";
	else cout<<"NO\n";
}
