#include <iostream>
#include <string>
#include <set>
using namespace std;

void test_case(){
	string s;cin>>s;
	set<char> l;
	int ret=0;
	for(char c:s){
		if(l.count(c))l.clear();
		else{
			if(l.size())ret++;
			l.insert(c);
		}
	}
	if(l.size())ret++;
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
