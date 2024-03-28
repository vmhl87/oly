#include <iostream>
#include <string>
using namespace std;

void test_case(){
	int n;cin>>n;
	string s;cin>>s;
	int best=n+1;
	for(int ii=1;ii*ii<=n;++ii)if(n%ii==0)for(int i=ii,r=0;r<2;r++,i=n/i){
		if(i>best)continue;
		string s1=s.substr(0,i),s2;
		bool ns=1,w=1;
		int c1=1,c2=0;
		for(int j=i;j<n;j+=i){
//			cout<<'.';
			string s3=s.substr(j,i);
			if(s3!=s1){
				if(s3==s2)c2++;
				else if(ns){
					s2=s3;ns=0;c2=1;
				}else{
					w=0;break;
				}
			}else c1++;
		}
//		cout<<i<<','<<s1<<','<<s2<<','<<c1<<','<<c2<<'\n';
		if(w){
			if(c1>1&&c2>1)continue;
			int diff=0;
			if(c2)for(int j=0;j<i;++j)if(s1[j]!=s2[j])diff++;
			if(diff>1)continue;
			if(i<best)best=i;
		}
	}
	cout<<best<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
