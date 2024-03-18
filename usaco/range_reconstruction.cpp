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
	int t;cin>>t;
	// previous value
	int last=0;
	cout<<1;
	// ranges
	pair<int,int> s[n];
	// loop thru rest of values
	for(int i=0;i<n-1;++i){
		// upper and lower possible values
		int up=last+r[i][i],
			down=last-r[i][i];
		// up and down work (?)
		bool upw=1,downw=1;
		// loop thru other constraints
		for(int j=i-1;j>=0;--j){
			// compare with s[j]
			int diff=r[j][i]-s[j].second+s[j].first;
			// within range
			if(diff<1){
				if(up>s[j].second)upw=0;
				if(down<s[j].first)downw=0;
			// out of range
			}else{
				if(up!=s[j].second+diff)upw=0;
				if(down!=s[j].first-diff)downw=0;
			}
		}
		int next=down;
		if(upw)next=up;
		last=next;
		cout<<' '<<next+1;
		// update ranges
		s[i+1]=make_pair(next,next);
		for(int j=0;j<=i;++j){
			if(s[j].second<next)s[j].second=next;
			if(s[j].first>next)s[j].first=next;
		}
	}
	cout<<'\n';
}
