#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	int r[n-1][n-1];
	for(int i=0;i<n-1;++i){
		int t;cin>>t;
		for(int j=i;j<n-1;++j)
			cin>>r[i][j];
	}
// for(int i=0;i<n-1;++i){
// 	for(int j:r[i])
// 		cout<<j<<' ';
// 	cout<<'\n';
// }
	int t;cin>>t;
	int last=0;
	cout<<0<<' ';
	pair<int,int> s[n];
	for(int i=0;i<n-1;++i){
		int up=last+r[i][i],
			down=last-r[i][i];
		bool upw=1,downw=1;
		for(int j=i-1;j>=0;--j){
			// compare with s[j]
			int diff=r[j][j]-s[j].second+s[j].first;
			if(diff<1){
				if(up>s[j].second)upw=0;
				if(down<s[j].first)downw=0;
			}else{
				if(up!=s[j].second+diff)upw=0;
				if(down!=s[j].first-diff)downw=0;
			}
		}
		int next=down;
		if(upw)next=up;
		last=next;
		cout<<next<<' ';
		// update ranges
		s[i+1]=make_pair(next,next);
		for(int j=0;j<=i;++j){
			if(s[j].second<next)s[j].second=next;
			if(s[j].first>next)s[j].first=next;
		}
	}
	cout<<'\n';
}
