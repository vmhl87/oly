#include <iostream>
#include <string>
using namespace std;

int main(){
	short map[26];
	for(int i=0;i<26;i++){
		char c;
		cin>>c;
		map[c-'a']=i;
	}
	string str;
	cin>>str;
	int count=1;
	short last=-1,t;
	for(char tmp:str){
		t=map[tmp-'a'];
		if(t<=last)count++;
		last=t;
	}
	cout<<count<<'\n';
}
