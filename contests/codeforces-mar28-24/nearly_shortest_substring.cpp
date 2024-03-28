#include <iostream>
#include <string>
using namespace std;

void test_case(){
	int n;cin>>n;
	string s;cin>>s;
	int best=n+1;
	// find all possible i that divide n
	for(int ii=1;ii*ii<=n;++ii)if(n%ii==0)for(int i=ii,r=0;r<2;r++,i=n/i){
		// if non optimal skip
		if(i>best)continue;
		// if we divide the string s into blocks of i chars, we must see
		// at most 2 different strings - we store these as s1,s2
		string s1=s.substr(0,i),s2;
		// ns = s2 not set, w = works
		bool ns=1,w=1;
		// count of how many times s1 and s2 appear (at least one of them
		// must appear less than 2 times)
		int c1=1,c2=0;
		// for all blocks of i chars besides the first one:
		for(int j=i;j<n;j+=i){
			// find the substring and match it with either s1 or s2
			string s3=s.substr(j,i);
			if(s3!=s1){
				if(s3==s2)c2++;
				else if(ns){
					// if not set we will set s2
					s2=s3;ns=0;c2=1;
				}else{
					// otherwise this i does not work
					w=0;break;
				}
			}else c1++;
		}
		// if this i worked then check if the counts are right - the ending
		// string may only differ from our repeated one by one char
		if(w){
			// if there are too many repetitions of the "differing" substring
			// then it automatically does not work
			if(c1>1&&c2>1)continue;
			// check if difference is > 1
			int diff=0;
			if(c2)for(int j=0;j<i;++j)if(s1[j]!=s2[j])diff++;
			if(diff>1)continue;
			// set best
			if(i<best)best=i;
		}
	}
	cout<<best<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
