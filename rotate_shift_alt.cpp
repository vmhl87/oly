#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n,k,t;
	cin>>n>>k>>t;
	int a[k];
	for(int i=0;i<k;i++)cin>>a[i];
	int cows[n];
	for(int i=0;i<n;i++)cows[i]=i;
	int cycle_len=0;
	vector<int> map;
	bool eql=false;
	while(!eql){
		int tmp=cows[a[0]];
		for(int i=0;i<k;i++){
			int tmp2=cows[a[(i+1)%k]];
			cows[a[(i+1)%k]]=tmp;
			tmp=tmp2;
		}
		for(int i=0;i<k;i++)a[i]=(a[i]+1)%n;
		for(int i=0;i<n;i++)map.push_back(cows[i]);
		cycle_len++;
		eql=true;
		for(int i=0;i<n;i++)if(cows[i]!=i){eql=false;break;}
		if(cycle_len>t)eql=true;
	}
	int tr=((t-1+cycle_len)%cycle_len)*n;
	cout<<map[tr];
	for(int i=1;i<n;i++)cout<<' '<<map[tr+i];
	cout<<'\n';
	return 0;
}
