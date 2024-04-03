#include <iostream>
#include <vector>
using namespace std;

void test_case(){
	int n;cin>>n;
	// off, down
	vector<pair<int,int>> dp[3];
	int off=0,down=0,ldp=-1;
	long long ret=0;
	char last=-1;
	for(int i=0;i<n;++i){
		char c;cin>>c;
		if(c=='-'){
			--off;
			if(last=='-'){
				++down;
				++dp[ldp][dp[ldp].size()-1].second;
			}
		}else ++off;
		last=c;
		if(off%3==0&&off<=0&&off>=-down*3)++ret;
		ldp=(3+(off%3))%3;
		for(pair<int,int> p:dp[ldp]){
			int t=p.first-off;
			if(t>=0&&t<=(down-p.second)*3)++ret;
		}
		dp[ldp].push_back(make_pair(off,down));
	}
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
