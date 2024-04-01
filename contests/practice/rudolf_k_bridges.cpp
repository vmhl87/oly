#include <iostream>
#include <queue>
#include <set>
using namespace std;

void test_case(){
	int n,m,k,d;cin>>n>>m>>k>>d;
	long long best[n];
	for(int x=0;x<n;++x){
		long long h[m];for(int i=0;i<m;++i)cin>>h[i];
		multiset<long long> dp;
		queue<long long> past;
		long long last=-1;
		for(int i=0;i<m;++i){
			long long opt=0;
			if(dp.size())opt=*dp.begin();
			opt+=h[i]+1;
			dp.insert(opt);
			past.push(opt);
			if(dp.size()>d+1){
				dp.erase(dp.find(past.front()));
				past.pop();
			}
			last=opt;
//			cout<<last<<' ';
		}
//		cout<<'\n';
		best[x]=last;
	}
	long long ret=0;bool ns=1;
	long long sum=0;
	for(int i=0;i<n;++i){
		sum+=best[i];
		if(i-k>=0)sum-=best[i-k];
		if(i>=k-1){
			ret=(ns||sum<ret?sum:ret);
			ns=0;
		}
	}
//	for(int i:best)cout<<i<<' ';cout<<'\n';
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
