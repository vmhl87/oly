#include <iostream>
#include <vector>
using namespace std;

void test_case(){
	int n;cin>>n;
	int a[n];
	for(int i=0;i<n;++i)cin>>a[i];
	vector<pair<int,int>> seg;
	for(int i=0;i<n;++i){
		if(a[i]!=0){
			if(seg.size()){
				if(seg[seg.size()-1].second==i-1)
					++seg[seg.size()-1].second;
				else seg.push_back(make_pair(i,i));
			}else{
				seg.push_back(make_pair(i,i));
			}
		}
	}
	if(!seg.size()){
		cout<<n<<" 0\n";
		return;
	}
	int best=0;pair<int,int> sol=make_pair(0,n);
	for(pair<int,int> p:seg){
		int twos=0,sign=1;
		for(int i=p.first;i<=p.second;++i){
			if(a[i]==2||a[i]==-2)++twos;
			if(a[i]<0)sign^=1;
		}
		if(sign){
			if(twos>best){
				best=twos;
				sol.first=p.first;
				sol.second=n-p.second-1;
				continue;
			}
		}
		int rl=0,rr=0,il,ir;
		for(il=p.first;il<=p.second;++il){
			if(a[il]==2||a[il]==-2)++rl;
			if(a[il]<0)break;
		}
		for(ir=p.second;ir>=p.first;--ir){
			if(a[ir]==2||a[ir]==-2)++rr;
			if(a[ir]<0)break;
		}
		twos-=(rl>rr?rr:rl);
		if(twos>best){
			best=twos;
			if(rl>rr){
				sol.first=p.first;
				sol.second=n-ir;
			}else{
				sol.first=il+1;
				sol.second=n-p.second-1;
			}
		}
	}
	cout<<sol.first<<' '<<sol.second<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
