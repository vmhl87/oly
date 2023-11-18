#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n;cin>>n;
	int metals[n];
	for(int i=0;i<n;i++)cin>>metals[i];
	int k;cin>>k;
	vector<int> rec[n];
	for(int i=0;i<k;i++){
		int l,m,t;cin>>l>>m;
		while(m-->0){
			cin>>t;rec[l-1].push_back(t-1);
		}
	}
	int r[n];for(int i=1;i<n;i++)r[i-1]=0;
	r[n-1]=1;
	int ret=0;
	for(;;){
		int can=0;bool b=1;
		for(int i=0;i<n;i++)if(r[i]>0){
			int t=metals[i]/r[i];
			if(t<can||b){can=t;b=0;}
		}
		ret+=can;
		for(int i=0;i<n;i++)metals[i]-=can*r[i];
		for(int i=0;i<n;i++)if(r[i]>metals[i]){
			if(rec[i].size()>0){
				for(int h:rec[i])r[h]+=r[i]-metals[i];
				r[i]=metals[i];
			}else goto done;
		}
	}
	done:
	cout<<ret<<'\n';
}
