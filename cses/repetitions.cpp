#include <iostream>
#include <string>
using namespace std;

int main(){
	string s;cin>>s;
	int max=0,buf=0;
	char last='e';
	for(char c:s){
		//cout<<c<<','<<last<<'\n';
		if(c==last)buf++;
		else{if(buf>max)max=buf;buf=0;}
		last=c;
	}
	if(buf>max)max=buf;
	cout<<max+1<<'\n';
}
